using namespace std;
#include "Weather.h"
#include "Time.h"
#include <string>

class Reader {
public:
    string request(string request) 
    {
        if (strcmp(request.c_str(), "weather") == 0) {
            Weather weather;
            return weather.getWeather();
        }

        if (strcmp(request.c_str(), "time") == 0) {
            Time time;
            return time.getTime();
        }

        return "";
    }
};