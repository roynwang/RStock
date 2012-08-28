#include <stdio.h>
#include <curl/curl.h>
size_t my_write_func(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	    return fwrite(ptr, size, nmemb, stream);
}

int main(void)
{
	CURL *curl;
	CURLcode res;
	FILE *outfile;

	curl = curl_easy_init();
	if(curl)
	{
		outfile = fopen("xxx", "w");
		char *url = "http://finance.yahoo.com/d/quotes.csv?s=msft&f=npl1";

		curl_easy_setopt(curl, CURLOPT_URL, "http://ichart.finance.yahoo.com/table.csv?s=DAI.DE&a=NaN&b=02&c=pr-2&g=d&ignore=.csv");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); 
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write_func);

		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(outfile);
	}
}
