/*
 * OBDII.cpp
 *
 *  Created on: 2012-7-10
 *      Author: derek
 */

#include "OBD.h"

bool OBD::Init() {
	serialPort->setTimeout(2000);
	sendCmd("ATZ");
	sendCmd("ATZ");
	sendCmd("ATZ");

	delay(1000);

	sendCmd("ATE0");
	sendCmd("ATH0");
	sendCmd("ATS0");
	sendCmd("ATL0");
	sendCmd("ATSP0");
	serialPort->setTimeout(10000); //Waiting for SEARCHING
	if (-1 == sendCmd("0100").indexOf("4100")) {
		return false;
	}

	serialPort->setTimeout(1000);
	errorCount = 0;
	return true;
}

int OBD::ErrorCount() {
	return errorCount;
}

String OBD::GetRawValue(String pidCode) {
	return sendCmd("01" + pidCode);
}

int OBD::GetRPM() {
	delay(350);
	String value = GetRawValue("0C");
	if (value.indexOf("410C") == -1) {
		errorCount++;
		return -2;
	}

	char c[4] = { value[4], value[5], value[6], value[7] };
	char* p = NULL;
	long n = strtol(c, &p, 16);

	return n / 4;
}

int OBD::GetSpeed() {
	delay(350);
	String value = GetRawValue("0D");
	if (value.indexOf("410D") == -1) {
		errorCount++;
		return -2;
	}

	char c[2] = { value[4], value[5] };
	char* p = NULL;
	long n = strtol(c, &p, 16);

	return n;
}

String OBD::sendCmd(String cmd) {
	while (serialPort->read() != -1) {
		;
	}

	serialPort->print(cmd);
	serialPort->print('\r');
	String response = serialPort->readStringUntil('>');

	if (debugPort != NULL) {
		debugPort->print(cmd);
		debugPort->print("\r\n");
		debugPort->print('[');
		debugPort->print(response);
		debugPort->print("]\r\n");
		debugPort->flush();
	}
	return response;
}
