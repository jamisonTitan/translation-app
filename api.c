#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

char* trans(char* in, char* in_lang, char* out_lang) {
	CURL *curl;
	CURLcode res;
	char* res_string;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if(curl) {
		//formatting the http request
		char url_buffer[256];
		char* url_base = "https://nlp-translation.p.rapidapi.com/v1/translate?text=%s&from=%s&to=%s";
		snprintf(url_buffer, strlen(url_base) + strlen(in) + strlen(in_lang) + strlen(out_lang), url_base, in, in_lang, out_lang);

		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(curl, CURLOPT_URL, url_buffer);

		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "X-RapidAPI-Key: 00e1f7efd8mshc4f9c95376d24f7p143203jsn727a42df44f3");
		headers = curl_slist_append(headers, "X-RapidAPI-Host: nlp-translation.p.rapidapi.com");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		res = curl_easy_perform(curl);
		res_string = (char*) curl_easy_strerror(res);

		if(res != CURLE_OK) {
			fprintf(stderr, "REQUEST FAILED: %s\n", res_string);
		} else {
			printf("%s\n", res_string);
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return res_string;
}
