using namespace std;
#include "Weather.h"
#include <string>

class Reader {
public:
    void request(string request) {
        if (strcmp(request.c_str(), "weather") == 0) {
            Weather weather;
            weather.getWeather();
        }
    }
};