#pragma once

#include <string>
#include "SimpleSerial.h"

using namespace std;

class Writer {
public:

	bool write(SimpleSerial* serial, string message) {
		char* to_send = &message[0];
		return serial->WriteSerialPort(to_send);
	}
};