#include "ocr.hpp"
#include "translator.hpp"
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <thread>
#include <sys/ipc.h>
#include <sys/msg.h>


#define MAX_STR 4096
#define IMG_TERM 60
#define SV_SIZE 20

void get_filepath(char *str, int count);
void init_Msg();
void sendMsg(SV *target_data, int numsv_);
void receiveMsg(SV *receive_data, int *numsv_);
int API();

struct my_msgbuf
{
    long msgtype;
    SV data[SV_SIZE];
    int numsv;
    int dummy[2];
};

SV* psv = NULL;
int numsv = 0;
key_t key_id;
struct my_msgbuf mybuf;


int main(){
    psv = (SV*)malloc(sizeof(SV) * SV_SIZE);
    numsv = 0;

    init_Msg();

    thread THR(&API);

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
    int count=1;
    char continues=0;

    int fd=0;

    img_cnt = 1;
    prev_cnt = 1;

    get_filepath(img_name, img_cnt);

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

            sendMsg(psv, numsv);
                
            end = clock();

            std::cout<<"delay : "<<(1000.0)*(double)(end-start)/CLOCKS_PER_SEC<<endl;
            std::cout<<"frame "<<count<<endl;

            //sleep(3.0-(1.0)*(double)(end-start)/CLOCKS_PER_SEC);
            if(count == 0){
                std::cout<<"count is 0. C to continue, E to exit : ";
                std::cin>>continues;
                if(continues == 'c' || continues == 'C'){
                    count = 100;
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


//////////////// Init MSG queue /////////////////
void init_Msg(){
    key_id = msgget((key_t)1234, IPC_CREAT|0666);
    if (key_id == -1)
    {
        perror("msgget error : ");
        exit(0);
    }
}
//////////////// Init MSG queue /////////////////


//////////////// Send MSG queue /////////////////
void sendMsg(SV *target_data, int numsv_){
    memcpy(mybuf.data, target_data, sizeof(SV) * SV_SIZE);
    mybuf.msgtype = 1;
    mybuf.numsv = numsv_;
    struct my_msgbuf temp_buf;
    char d;

    std::cout<<"Try to send!"<<std::endl;

    while (msgsnd( key_id, (void *)&mybuf, sizeof(struct my_msgbuf), IPC_NOWAIT) == -1)
    {
        std::cout<<"Queue is full!"<<std::endl;
        if(msgrcv( key_id, (void *)&temp_buf, sizeof(struct my_msgbuf) - 8, 1, IPC_NOWAIT | MSG_NOERROR) == -1)
            std::cout<<"Error receive!"<<std::endl;
    }
    std::cout<<"send : "<<mybuf.data[0].str<<", "<<mybuf.numsv<<std::endl;
}
//////////////// Send MSG queue /////////////////


//////////////// Receive MSG queue /////////////////
void receiveMsg(SV *receive_data, int *numsv_){
    struct my_msgbuf temp_buf;
    int flag=0, rcv_result=0;

    //get latest data in queue.
    do
    {
        rcv_result = msgrcv( key_id, (void *)&temp_buf, sizeof(struct my_msgbuf) - 8, 1, IPC_NOWAIT | MSG_NOERROR);
        flag = 1;
    }while ( (rcv_result == -1 && flag == 0) || rcv_result == 0 );

    memcpy(receive_data, temp_buf.data, sizeof(SV) * SV_SIZE);
    (*numsv_) = temp_buf.numsv;
}
//////////////// Receive MSG queue /////////////////