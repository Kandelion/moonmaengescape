#ifndef __TRANSLATOR__
#define __TRANSLATOR__

#include "curl/curl.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include <malloc.h>

#define MAX_URL 1024
#define DEBUG 0

using namespace rapidjson;
using namespace std;

class translator{
private:
    static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp);
    CURLcode curl_read(const string& url, ostream& os, long timeout = 30);
    char *URL_Encode(const char *str);
    void getURL(char *URL, const char *str);

public:
    const char* translate(const char *src_str);
};

#endif