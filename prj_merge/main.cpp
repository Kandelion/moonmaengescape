#include "ocr.hpp"
#include "translator.hpp"
#include <iostream>
#define MAX_STR 4096
//extern SV sv[4096];
//extern int numsv;
/*typedef struct _str_and_vertex {
	char str[100];
	int x1, y1, x2, y2;
}*/
int main(){
    ocr_vision OCR_;
    translator TR;
    char result_ocr[MAX_STR];
    char result_translation[MAX_STR];

    char img_name[256];
    int numsv = 0;
    SV* psv = (SV*)malloc(sizeof(SV) *4096);

    std::cout<<"Input image name : ";
    std::cin>>img_name;

    std::cout<<std::endl<<"==result=="<<std::endl;

    OCR_.detect_text(result_ocr, MAX_STR, img_name, "ocr");
   // std::cout<<"# Detected text"<<std::endl;
   // std::cout<<result_ocr<<std::endl;

    TR.translate(result_translation, MAX_STR, (const char*)result_ocr, psv, &numsv);
   // std::cout<<"# Translated text"<<std::endl;
   // std::cout<<result_translation<<std::endl;
    for(int i = 0; i <numsv ; i++)
	printf("%s %d %d %d %d\n", psv[i].str, psv[i].x1,  psv[i].y1, psv[i].x2, psv[i].y2);
    return 0;
}
