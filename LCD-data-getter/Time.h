#pragma once
using namespace std;

#include <format>
#include <ctime>
#include <iostream>

class Time {
public: 
    string getTime() {
        time_t now = time(0);
        char* dt = ctime(&now);

        tm ltm;
        localtime_s(&ltm, &now);

        char formatTime[256];
        sprintf(formatTime, "%02d/%02d/%i %02d:%02d:%02d\n", ltm.tm_mday, ltm.tm_mon + 1, ltm.tm_year + 1900, ltm.tm_hour, ltm.tm_min, ltm.tm_sec);
        cout << formatTime << endl;
        return formatTime;
    }
};