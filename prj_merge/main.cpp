#include "ocr.hpp"
#include "translator.hpp"
#include <iostream>

int main(){
    ocr_vision OCR_;
    translator TR;
    char result_ocr[4096];
    char *result_translation;

    char img_name[256];

    std::cout<<"Input image name : ";
    std::cin>>img_name;

    std::cout<<std::endl<<"==result=="<<std::endl;

    OCR_.detect_text(result_ocr, 4096, img_name, "ocr");
    std::cout<<"# Detected text"<<std::endl;
    std::cout<<result_ocr<<std::endl;

    result_translation = TR.translate((const char*)result_ocr);
    std::cout<<"# Translated text"<<std::endl;
    std::cout<<result_translation<<std::endl;

    return 0;
}