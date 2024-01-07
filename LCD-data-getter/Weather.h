using namespace std;
#pragma once
#pragma comment(lib, "libcurl_imp.lib")
#pragma warning(disable : 4996)

#include "curl/curl.h"
#include <string>
#include <iostream>
#include "Writer.h"
#include "json.hpp"

#define LAT 40.899
#define LON 14.3528
#define API_KEY "71f91b67c843fca6b1d591117c0fc73d"

class Weather {
public:

    static size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    string getWeather() {
        CURL* curl;
        CURLcode res;
        Writer write;

        std::string weather;
        
        curl_global_init(CURL_GLOBAL_DEFAULT);

        curl = curl_easy_init();
        if (curl) {

            char weatherAPI[256];

            std::string response;

            sprintf(weatherAPI, "http://api.openweathermap.org/data/2.5/weather?lang=it&lat=%f&lon=%f&appid=%s", LAT, LON, API_KEY);
            curl_easy_setopt(curl, CURLOPT_URL, weatherAPI);
            //curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            //curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_3);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                curl_easy_cleanup(curl);

                return "";
            }

            if (res == CURLE_OK) {
                using json = nlohmann::json;

                json j = json::parse(response);

                cout << response << endl;
                const double K = j["main"]["temp"];
                string condition = j["weather"][0]["main"];

                const int C = KtoC(K);
                cout << to_string(C) + "C " + condition << endl;
                return weather = to_string(C) + "C " + translate(condition);
            }

            curl_easy_cleanup(curl);
        }
    }

    string translate(string condition) {
        if (condition == "Rain") {
            return "pioggia";
        }

        if (condition == "Clear") {
            return "soleggiato";
        }

        if (condition == "Clouds") {
            return "nuvoloso";
        }

        if (condition == "Snow") {
            return "neve";
        }

        if(condition == "Thunderstorm") {
            return "tempesta";
        }

        return condition;
    }

private:
    const double absoluteZero = 273.15;

    int KtoC(double kelvin) {
        return kelvin - absoluteZero;
    }
};