using namespace std;

#pragma comment(lib, "libcurl_imp.lib")
#pragma warning(disable : 4996)

#include <iostream>
#include <format>
#include <ctime>
#include <chrono>
#include <stdlib.h>
#include <iostream>
#include "json.hpp"
#include "SimpleSerial.h"
#include "Weather.h"

#define LAT 40.899
#define LON 14.3528
#define API_KEY "71f91b67c843fca6b1d591117c0fc73d"


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
