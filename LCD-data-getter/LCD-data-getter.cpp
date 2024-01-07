using namespace std;

#pragma warning(disable : 4996)

#include <format>
#include <ctime>
#include <chrono>
#include <stdlib.h>
#include <iostream>
#include "SimpleSerial.h"
#include "Weather.h"
#include "Reader.h"
#include "Writer.h"

int main() {

    char com_port[] = "\\\\.\\COM3";
    DWORD COM_BAUD_RATE = CBR_9600;
    SimpleSerial Serial(com_port, COM_BAUD_RATE);
    Reader read;
    Writer write;

    string readin, incoming, response;
    char* to_send = NULL;

    while (true)
    {
        incoming = Serial.ReadSerialPort(1, "greater_less_than");

        if (!incoming.empty()) {
            cout << incoming << endl;

            string response = read.request(incoming);
            write.write(&Serial, response);
        }
    }
    return 0;
}
