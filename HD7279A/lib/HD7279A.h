/*
 * HD7279A.h
 *
 *  Created on: 2012-7-14
 *      Author: derek
 */

#ifndef HD7279A_H_
#define HD7279A_H_

class HD7279A {
public:
	HD7279A(int CS_PIN ,int CLK_PIN , int DATA_PIN);
	void setPin(int CS_PIN ,int CLK_PIN , int DATA_PIN);
	void setNumOfDigits(int num);
	virtual ~HD7279A();
	void reset();
	void test();
	void showNumber(int number);
private:
	void sendCmd(unsigned char outByte);
	void sendCmdAndData(unsigned char cmd, unsigned char data);
	void setPinMode();
	void sendRawData(unsigned char cmd);

	int csPin;
	int clkPin;
	int dataPin;

	int numOfDigit;
};

#endif /* HD7279A_H_ */
