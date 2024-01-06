using namespace std;

#include "curl/curl.h"
#include <string>

class Weather {
public:
    int getWeather() {
        CURL* curl;
        CURLcode res;

        curl_global_init(CURL_GLOBAL_DEFAULT);

        curl = curl_easy_init();
        if (curl) {

            char weatherAPI[256];
            sprintf(weatherAPI, "http://api.openweathermap.org/data/2.5/weather?lat=%f&lon=%f&appid=%s", LAT, LON, API_KEY);
            curl_easy_setopt(curl, CURLOPT_URL, weatherAPI);

            //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
            //curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);
            curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_3);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
                curl_easy_cleanup(curl);

                return 1;
            }

            if (res == CURLE_OK) {
                //printf("%s", res);
                getK(to_string(res));
            }

            curl_easy_cleanup(curl);
        }
    }

    const int getK(string json) {
        string tempKey = "\"temp\":";
        const int K = json.find(tempKey);
        return K;
    }

private:
    const double absoluteZero = 273.15;
    int KtoC(int kelvin) {
        return kelvin - absoluteZero;
    }
};