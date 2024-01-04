using namespace std;
#pragma comment(lib, "libcurl_imp.lib")
#pragma warning(disable : 4996)

#include <iostream>
#include <format>
#include <ctime>
#include <chrono>
#include <stdio.h>
#include "json.h"
#include "curl/curl.h"
#include "SimpleSerial.h"

#define LAT 40.899
#define LON 14.3528
#define API_KEY "71f91b67c843fca6b1d591117c0fc73d"


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

           if (res != CURLE_OK){
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

class Reader {
public:
    void request(string request) {
        if (strcmp(request.c_str(), "weather") == 0) {
            Weather weather;
            weather.getWeather();
        }
    }
};

string getTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    
    tm ltm;
    localtime_s(&ltm, &now);

    char formatTime[256];
    sprintf(formatTime, "%02d/%02d/%i %02d:%02d:%02d\n", ltm.tm_wday, ltm.tm_mon+1, ltm.tm_year+1900, ltm.tm_hour, ltm.tm_min, ltm.tm_sec);
    return formatTime;
}

int main() {

    char com_port[] = "\\\\.\\COM3";
    DWORD COM_BAUD_RATE = CBR_9600;
    SimpleSerial Serial(com_port, COM_BAUD_RATE);

    while (true) {
        string readin = getTime();
        char* to_send = &readin[0];
        Serial.WriteSerialPort(to_send);

        string incoming = Serial.ReadSerialPort(1, "greater_less_than");
        //this_thread::sleep_for(chrono::seconds(1));
        cout << incoming;

        Reader read;
        read.request(incoming);
    }
    return 0;
}
