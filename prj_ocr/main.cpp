#include "ocr.hpp"
#include <iostream>

int main(){
    ocr_vision OCR_;
    char result[1024];
    char img_name[256];

    std::cout<<"img name : ";
    std::cin>>img_name;

    OCR_.detect_text(result, 1024, img_name, "ocr");

    std::cout<<result<<std::endl;

    return 0;
}