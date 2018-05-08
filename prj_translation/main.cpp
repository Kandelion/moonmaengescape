#include "curl/curl.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>

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

void getURL(char *URL, const char *str){
	int len = strlen(str);
	char temp[MAX_URL+10] = {0};
	char str_cpy[MAX_URL]={0};

	strncpy(str_cpy, str, MAX_URL);

	for(int i=0; i<len; i++){
		switch(str_cpy[i]){
			case ' ':
				strcpy(temp, &str_cpy[i+1]);
				strncpy(&str_cpy[i], "%20", 4);
				strcat(str_cpy, temp);
				i+=2;
				len+=2;
				break;
			/*case '.':
				strcpy(temp, &str_cpy[i+1]);
				strncpy(&str_cpy[i], "&#46;", 6);
				strcat(str_cpy, temp);
				i+=4;
				len+=4;
				break;*/
			default:
				if(isalpha(str_cpy[i]) == false){
					if(str_cpy[i]<'0' || str_cpy[i]>'9'){
						strcpy(temp, &str_cpy[i+1]);
						strncpy(&str_cpy[i], "%20", 4);
						strcat(str_cpy, temp);
						len+=2;
						i+=2;
					}
				}

				break;
		}
	}

	URL[0] = 0;
	strcat(URL, "https://translation.googleapis.com/language/translate/v2?q=");
	strcat(URL, str_cpy);
	strcat(URL, "&target=ko&format=text&key=AIzaSyC27Cydynq2Q7_r8PiwyP4l1hJNSk7Db4Q");
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
