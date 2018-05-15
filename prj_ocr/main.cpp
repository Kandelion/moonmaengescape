#include "ocr.hpp"
#include <iostream>

int main(){
    ocr_vision OCR_;
    char *result;

    result = OCR_.detect_text("test3.jpg", "ocr");

    std::cout<<result<<std::endl;

    return 0;
}