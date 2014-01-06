/*
 * OBDII.h
 *
 *  Created on: 2012-7-10
 *      Author: derek
 */

#ifndef OBD_H_
#define OBD_H_
#include <Arduino.h>

class OBD {
public:
	OBD(HardwareSerial* serailport){
		this->serialPort = serailport;
		debugPort = NULL;
		errorCount = 0;
	}

	void SetDebugPort(HardwareSerial* debugPort)
	{
		this->debugPort = debugPort;
	}

	bool Init();
	int ErrorCount();
	String GetRawValue(String pidCode);
	int GetRPM();
	int GetSpeed();
private:
	String sendCmd(String cmd);

	HardwareSerial* serialPort;
	HardwareSerial* debugPort;
	int errorCount;
};

#endif /* OBDII_H_ */
