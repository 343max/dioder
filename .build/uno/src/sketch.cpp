#include <Arduino.h>
void setup();
void loop();
#line 1 "src/sketch.ino"
const int LED = 13;

const int LED1red = 2;
const int LED1blue = 3;
const int LED1green = 4;

const int LED2red = 5;
const int LED2blue = 6;
const int LED2green = 7;

const int pins[7] = {LED, LED2red, LED1red, LED2green, LED1green, LED2blue, LED1blue};

int value = 0;

void setup() {
	for (int i = 0; i < 7; ++i)
	{
		pinMode(pins[i], OUTPUT);
	}
}

void loop() {
	value += 2;

	if (value >= 255)
	{
		value = 0;
	}

	for (int i = 0; i < 7; ++i)
	{
		int pin = pins[i];
		analogWrite(pin, value);
	}
	delay(10);
}
