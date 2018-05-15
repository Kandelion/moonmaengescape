#include "translator.hpp"

int main(){
    translator TR;
    char str[512];
    char result[1024];

    cout<<"Input text : ";
    cin.getline(str, 512);

    TR.translate(result, 1024, (const char*)str);

    cout<<"RESULT : "<<result<<endl;

    return 0;
}