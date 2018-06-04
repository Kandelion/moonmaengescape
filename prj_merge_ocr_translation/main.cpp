#include "ocr.hpp"
#include "translator.hpp"
#include <iostream>

#define MAX_STR 4096

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
    std::cout<<"# Detected text"<<std::endl;
    std::cout<<result_ocr<<std::endl;

    TR.translate(result_translation, MAX_STR, (const char*)result_ocr);
    std::cout<<"# Translated text"<<std::endl;
    std::cout<<result_translation<<std::endl;

    return 0;
}