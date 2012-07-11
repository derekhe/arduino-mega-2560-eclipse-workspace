/*
 * OBDTest.cpp
 *
 *  Created on: 2012-7-10
 *      Author: derek
 */

#include <OBD/OBD.h>

OBD* obd;

void setup()
{
	Serial.begin(115200);
	Serial1.begin(9600);
	obd = new OBD(&Serial1);
	obd->SetDebugPort(&Serial);
	while(!obd->Init());
}

void loop()
{
	Serial.print("\r\nRPM:");
	Serial.print(obd->GetRPM(), DEC);
	Serial.print("\r\nSpeed:");
	Serial.print(obd->GetSpeed(), DEC);
	Serial.print("\r\nErrorCount");
	Serial.print(obd->ErrorCount(), DEC);
	if(obd->ErrorCount() > 10)
	{
		while(!obd->Init());
	}
}
