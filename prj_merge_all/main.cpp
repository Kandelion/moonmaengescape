#include "ocr.hpp"
#include "translator.hpp"
#include "output.hpp"
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <thread>


#define MAX_STR 4096
#define IMG_TERM 60


void get_filepath(char *str, int count);
int API();

int main(){
    output OPT;
    thread THR(&API);

    OPT.output_init();
    THR.join();

    return 0;
}


int API(){
    ocr_vision OCR_;
    translator TR;
    char result_ocr[MAX_STR];
    char result_translation[MAX_STR];

    char *home_dir;
    int img_cnt=1;
    int prev_cnt=1;
    char file_cnt[10]="";
    char img_name[256] = "";
    char prev_path[256];

    clock_t start, end;
    int count=3;
    char continues=0;

    int fd=0;

    img_cnt = 1;
    prev_cnt = 1;

    get_filepath(img_name, img_cnt);

    int numsv = 0;
    SV* psv = (SV*)malloc(sizeof(SV) *4096);

    while(count>0){
        while(access(img_name, F_OK)==0){
            if(img_cnt > prev_cnt + IMG_TERM){
                get_filepath(prev_path, prev_cnt);
                remove(prev_path);
                std::cout<<"file "<<prev_path<<" has deleted."<<endl;
                prev_cnt += IMG_TERM;
            }
            img_cnt += IMG_TERM;
            get_filepath(img_name, img_cnt);
        }

        img_cnt -= IMG_TERM;// * 2;

        if(img_cnt < prev_cnt){
            img_cnt = prev_cnt;
            continue;
        }

        get_filepath(img_name, img_cnt);

        std::cout<<"cur file : "<<img_name<<endl;
        //std::cout<<"prev_cnt : "<<prev_cnt<<endl;
        
        ifstream in(img_name);

        if(in.good() == true){
            prev_cnt = img_cnt;
            count--;
            start = clock();
            std::cout<<"\033[2J";
            OCR_.detect_text(result_ocr, MAX_STR, img_name, "ocr");
            std::cout<<"# Detected text"<<std::endl;
            std::cout<<result_ocr<<std::endl;

            numsv = 0;
            TR.translate(result_translation, MAX_STR, (const char*)result_ocr, psv, &numsv);
            std::cout<<"# Translated text"<<std::endl;
            //std::cout<<result_translation<<std::endl;

            for(int i = 0; i <numsv ; i++)
	            printf("%s %d %d %d %d\n", psv[i].str, psv[i].x1,  psv[i].y1, psv[i].x2, psv[i].y2);
                
            end = clock();

            std::cout<<"delay : "<<(1000.0)*(double)(end-start)/CLOCKS_PER_SEC<<endl;
            std::cout<<"frame "<<count<<endl;

            //sleep(3.0-(1.0)*(double)(end-start)/CLOCKS_PER_SEC);
            if(count == 0){
                std::cout<<"count is 0. C to continue, E to exit : ";
                std::cin>>continues;
                if(continues == 'c' || continues == 'C'){
                    count = 10;
                }
                else if(continues == 'e' || continues == 'E'){
                    in.close();
                    break;
                }
            }
        }
        in.close();
    }
    return 0;
}

void get_filepath(char *str, int count){
    char *home_dir;
    char file_cnt[10]="";

    home_dir = getenv("HOME");
    strcpy(str, home_dir);
    sprintf(file_cnt, "%05d", count);
    strncat(str, "/Pictures/snap", 256);
    strncat(str, file_cnt, 256);
    strncat(str, ".jpg", 256);
}