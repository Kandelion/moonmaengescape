#include "curl/curl.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include <malloc.h>

#define MAX_URL 1024

using namespace rapidjson;
using namespace std;

const char *JsonField[] = {"translatedText", "detectedSourceLanguage"};
enum FIELD_NAME { RESULT, SRC_LANG };

// callback function writes data to a ostream
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
	if(userp)
	{
		ostream& os = *static_cast<ostream*>(userp);
		streamsize len = size * nmemb;
		if(os.write(static_cast<char*>(buf), len))
			return len;
	}

	return 0;
}

/**
 * timeout is in seconds
 **/
CURLcode curl_read(const string& url, ostream& os, long timeout = 30)
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
	char src_str[] = "Capstone PRJ is really awesome.";
	
	getURL(URL, src_str);

	/*ofstream ofs("output.html");
	if(CURLE_OK == curl_read(URL, ofs))
	{
		// Web page successfully written to file
	}*/

	ostringstream oss;
	string result;
	cout<<"==String Output=="<<endl;
	cout<<"#source string"<<endl;
	cout<<src_str<<endl;

	if(CURLE_OK == curl_read(URL, oss))
	{
		// Web page successfully written to string
		result = oss.str();
		//cout<<"#origin"<<endl;
		//cout<<result<<endl;
		cout<<"#translated string"<<endl;
		
		Document doc;
		doc.Parse(result.c_str());

		assert(doc.IsObject());
		assert(doc["data"].HasMember("translations"));

		Value& t1 = doc["data"];
		assert(t1.IsObject());
		Value::MemberIterator it1;
		//cout<<"IsArray? "<<(bool)t1["translations"].IsArray()<<endl;
		//cout<<t1["translations"][0].IsObject()<<endl;
		//t1 = t1["translations"];


		it1 = t1["translations"][0].FindMember(JsonField[RESULT]);

		for(int i=0; i<t1["translations"].Size(); i++){
			if(it1 == t1.MemberEnd())
				break;
			else if(strcmp(it1[i].name.GetString(), JsonField[RESULT]) == 0){
				cout<<it1[i].value.GetString()<<endl;
			}
		}

		//cout<<doc<<endl;
		//cout<<doc["data"].GetString()<<endl;
		//cout<<"SRC LANG : "<<doc["detectedSourceLanguage"].GetString()<<endl;
	}

	/*cout<<"==Standard Output=="<<endl;
	if(CURLE_OK == curl_read(URL, cout))
	{
		// Web page successfully written to standard output (console?)
	}*/

	curl_global_cleanup();
}
