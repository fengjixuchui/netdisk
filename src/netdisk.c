#include <stdio.h>
#include <string.h>

#include <curl/curl.h>
#include <curl/easy.h>


int netdisk();
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);

int main(int argc, char *argv[])
{
	netdisk();
	return 0;
}

int netdisk()
{
  CURL *curl_load;
  CURL *curl_login;
  CURL *curl_list;
  CURLcode res;

  struct curl_slist *headerlist=NULL;
  const char buf[] = "Expect:";

  const char *headerfilename = "baidu_header.html";
  FILE *headerfile;

  const char *bodyfilename = "baidu_body.html";
  FILE *bodyfile;
 
  headerfile = fopen(headerfilename,"w");
  bodyfile = fopen(bodyfilename,"w");
  
  curl_global_init(CURL_GLOBAL_ALL);

  headerlist = curl_slist_append(headerlist, buf);

  curl_load = curl_easy_init();
  curl_login = curl_easy_init();
  curl_list = curl_easy_init();

  if(curl_load && curl_login && curl_list) 
  {
      //step1:
      curl_easy_setopt(curl_load, CURLOPT_URL, "https://passport.baidu.com/V2/?login");
      curl_easy_setopt(curl_load, CURLOPT_HTTPHEADER, headerlist);
      curl_easy_setopt(curl_load, CURLOPT_COOKIEJAR,"cookie_open.txt");

      res = curl_easy_perform(curl_load);

      //step2:
      curl_easy_setopt(curl_login, CURLOPT_URL, "https://passport.baidu.com/v2/?login");
      curl_easy_setopt(curl_login, CURLOPT_HTTPHEADER, headerlist);
      curl_easy_setopt(curl_login, CURLOPT_POSTFIELDS, "username=xprotocol@google.com&password=123456");
      curl_easy_setopt(curl_login, CURLOPT_COOKIEFILE, "cookie_open.txt");
      curl_easy_setopt(curl_login, CURLOPT_COOKIEJAR, "cookie_login.txt");
      
      res = curl_easy_perform(curl_login);

      //step3:
      curl_easy_setopt(curl_list, CURLOPT_URL, "http://pan.mb.baidu.com/pan/manage.php?d=%2F");
      curl_easy_setopt(curl_list, CURLOPT_CUSTOMREQUEST,"GET");
      curl_easy_setopt(curl_list, CURLOPT_HTTPHEADER, headerlist);
      curl_easy_setopt(curl_list, CURLOPT_WRITEFUNCTION, write_data);
      curl_easy_setopt(curl_list, CURLOPT_WRITEHEADER,headerfile);
      curl_easy_setopt(curl_list, CURLOPT_WRITEDATA,bodyfile);
      curl_easy_setopt(curl_list, CURLOPT_COOKIEFILE,"cookie_login.txt");
      
      res = curl_easy_perform(curl_list);

      curl_easy_cleanup(curl_load);
      curl_easy_cleanup(curl_login);
      curl_easy_cleanup(curl_list);
  }

  curl_slist_free_all(headerlist);
  curl_global_cleanup();

  return 0;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
   int written = fwrite(ptr, size, nmemb, (FILE *)stream);
   return written;
}

