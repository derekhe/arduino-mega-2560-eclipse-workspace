/*
 * OBDTest.cpp
 *
 *  Created on: 2012-7-10
 *      Author: derek
 */

#include <OBD/OBD.h>
#include <HD7279A/HD7279A.h>

OBD* obd;
HD7279A* led;

void setup()
{
	Serial.begin(115200);
	Serial1.begin(9600);
	obd = new OBD(&Serial1);
	obd->SetDebugPort(&Serial);

	led = new HD7279A(22,24,26);
	led->setNumOfDigits(4);
	led->reset();
	delay(100);
	led->test();
	while(!obd->Init());
	led->reset();
	delay(100);
}

void loop()
{
	led->showNumber(obd->GetRPM());
	//led->showNumber(obd->GetSpeed());
	if(obd->ErrorCount() > 10)
	{
		led->reset();
		delay(100);
		led->test();
		while(!obd->Init());
		led->reset();
		delay(100);
	}
}
