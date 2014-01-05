#include <Arduino.h>
#include "hd7279a.h"

HD7279A* hd7279a;

void setup() {
	Serial.begin(115200);
	hd7279a = new HD7279A(22,24,26);
	hd7279a->setNumOfDigits(4);
	hd7279a->reset();
	delay(100);

}

void loop() {
	for(int i=100;i<9999;i++)
	{
		hd7279a->showNumber(i);
		delay(100);
	}
}
