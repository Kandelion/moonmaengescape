#include "ocr.hpp"
#include "translator.hpp"
#include <iostream>
#define MAX_STR 4096
extern SV sv[4096];
extern int numsv;
int main(){
    ocr_vision OCR_;
    translator TR;
    char result_ocr[MAX_STR];
    char result_translation[MAX_STR];

    char img_name[256];

    std::cout<<"Input image name : ";
    std::cin>>img_name;

    std::cout<<std::endl<<"==result=="<<std::endl;

    OCR_.detect_text(result_ocr, MAX_STR, img_name, "ocr");
   // std::cout<<"# Detected text"<<std::endl;
   // std::cout<<result_ocr<<std::endl;

    TR.translate(result_translation, MAX_STR, (const char*)result_ocr);
   // std::cout<<"# Translated text"<<std::endl;
   // std::cout<<result_translation<<std::endl;
    for(int i = 0; i <numsv ; i++)
	printf("%s %d %d %d %d\n", sv[i].str, sv[i].x1,  sv[i].y1, sv[i].x2, sv[i].y2);
    return 0;
}
