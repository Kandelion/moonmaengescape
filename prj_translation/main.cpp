#include "curl/curl.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include <malloc.h>

#define MAX_URL 1024

// callback function writes data to a std::ostream
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
	if(userp)
	{
		std::ostream& os = *static_cast<std::ostream*>(userp);
		std::streamsize len = size * nmemb;
		if(os.write(static_cast<char*>(buf), len))
			return len;
	}

	return 0;
}

/**
 * timeout is in seconds
 **/
CURLcode curl_read(const std::string& url, std::ostream& os, long timeout = 30)
{
	CURLcode code(CURLE_FAILED_INIT);
	CURL* curl = curl_easy_init();

	if(curl)
	{
		if(CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write))
				&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
				&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
				&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os))
				&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
				&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str())))
		{
			code = curl_easy_perform(curl);
		}
		curl_easy_cleanup(curl);
	}
	return code;
}

char *URL_Encode(const char *str) 
{
        char *encstr, buf[2+1];
        unsigned char c;
        int i, j;

        if(str == NULL) return NULL;
        if((encstr = (char *)malloc((strlen(str) * 3) + 1)) == NULL) 
                return NULL;

        for(i = j = 0; str[i]; i++) 
        {
                c = (unsigned char)str[i];
                if((c >= '0') && (c <= '9')) encstr[j++] = c;
                else if((c >= 'A') && (c <= 'Z')) encstr[j++] = c;
                else if((c >= 'a') && (c <= 'z')) encstr[j++] = c;
                else if((c == '@') || (c == '.') || (c == '/') || (c == '\\')
                        || (c == '-') || (c == '_') || (c == ':') ) 
                        encstr[j++] = c;
                else 
                {
                        sprintf(buf, "%02x", c);
                        encstr[j++] = '%';
                        encstr[j++] = buf[0];
                        encstr[j++] = buf[1];
                }
        }
        encstr[j] = 0;

        return encstr;
}

void getURL(char *URL, const char *str){
	int len = strlen(str);
	char* str_cpy;

	str_cpy = NULL;
	str_cpy = URL_Encode(str);

	URL[0] = 0;
	strcat(URL, "https://translation.googleapis.com/language/translate/v2?q=");
	strcat(URL, str_cpy);
	strcat(URL, "&target=ko&format=text&key=AIzaSyC27Cydynq2Q7_r8PiwyP4l1hJNSk7Db4Q");

	if(str_cpy != NULL)
		free(str_cpy);
}

int main()
{
	curl_global_init(CURL_GLOBAL_ALL);

	char URL[MAX_URL] ;
	
	getURL(URL, "Capstone PRJ is really awesome.");

	/*std::ofstream ofs("output.html");
	if(CURLE_OK == curl_read(URL, ofs))
	{
		// Web page successfully written to file
	}

	std::ostringstream oss;
	if(CURLE_OK == curl_read(URL, oss))
	{
		// Web page successfully written to string
		std::string html = oss.str();
	}*/

	std::cout<<"==Standard Output=="<<std::endl;
	std::cout<<"URL : "<<URL<<std::endl;
	if(CURLE_OK == curl_read(URL, std::cout))
	{
		// Web page successfully written to standard output (console?)
	}

	curl_global_cleanup();
}
