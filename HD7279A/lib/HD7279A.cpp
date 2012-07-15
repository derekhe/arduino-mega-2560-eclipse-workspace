/*
 * HD7279A.cpp
 *
 *  Created on: 2012-7-14
 *      Author: derek
 */
#include <arduino.h>
#include "HD7279A.h"

unsigned int DIGIT[8] = {
		1,
		10,
		100,
		1000,
};

HD7279A::HD7279A(int CS_PIN, int CLK_PIN, int DATA_PIN) :
		csPin(CS_PIN), clkPin(CLK_PIN), dataPin(DATA_PIN), numOfDigit(8) {
	setPinMode();
}

void HD7279A::setPin(int CS_PIN, int CLK_PIN, int DATA_PIN) {
	csPin = CS_PIN;
	clkPin = CLK_PIN;
	dataPin = DATA_PIN;
	setPinMode();
}

HD7279A::~HD7279A() {

}

void HD7279A::reset() {
	digitalWrite(csPin, 0);
	sendCmd(0xa4);
}

void HD7279A::test() {
	sendCmd(0xbf);
}

void HD7279A::showNumber(int number) {
	bool isLeadingZero = true;
	for(int i=numOfDigit-1;i>=0;i--)
	{
		int digit = number / DIGIT[i] % 10;
		Serial.print(digit,DEC);
		if((digit == 0) && isLeadingZero)
		{
			sendCmdAndData(0x80+i, 0xf);
		}
		else
		{
			sendCmdAndData(0xc8 + i, digit);
			isLeadingZero = false;
		}
	}
}

void HD7279A::setNumOfDigits(int num) {
	numOfDigit = num;
}

void HD7279A::sendRawData(unsigned char cmd) {
	for (int i = 0; i < 8; i++) {
		if (cmd & 0x80) {
			digitalWrite(dataPin, 1);
		} else {
			digitalWrite(dataPin, 0);
		}
		digitalWrite(clkPin, 1);
		delayMicroseconds(5);
		digitalWrite(clkPin, 0);
		delayMicroseconds(5);
		cmd = cmd << 1;
	}

	digitalWrite(dataPin, 0);
}

void HD7279A::sendCmd(unsigned char cmd) {
	digitalWrite(clkPin, 0);
	delayMicroseconds(50);
	sendRawData(cmd);
}

void HD7279A::sendCmdAndData(unsigned char cmd, unsigned char data) {
	delayMicroseconds(50);
	sendRawData(cmd);
	delayMicroseconds(20);
	sendRawData(data);
}

void HD7279A::setPinMode() {
	pinMode(csPin, OUTPUT);
	pinMode(clkPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
}
