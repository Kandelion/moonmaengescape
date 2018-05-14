#include "translator.hpp"

int main(){
    translator TR;
    char str[512];

    cout<<"Input text : ";
    cin.getline(str, 512);

    cout<<"RESULT : "<<TR.translate((const char*)str)<<endl;

    return 0;
}