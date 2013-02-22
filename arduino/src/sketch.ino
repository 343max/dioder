const int LED = 13;

const int LED1red = 3;
const int LED1blue = 5;
const int LED1green = 6;

const int LED2red = 9;
const int LED2blue = 10;
const int LED2green = 11;

const int pins[7] = {LED, LED2red, LED1red, LED2green, LED1green, LED2blue, LED1blue};

bool autoMode = true;

float value = 0;

int red = 0;
int blue = 0;
int green = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("Hello!");
	for (int i = 0; i < 7; ++i)
	{
		pinMode(pins[i], OUTPUT);
	}
}

int sinToPin(float value) {
	return sin(value) * 128 + 127; 
}

void loop() {
	if (autoMode)
	{
		value += 0.04;
		red = sinToPin(value);
		green = sinToPin(value + 1.5);
		blue = sinToPin(value + 3.0);
	}


	Serial.println(red);

	analogWrite(LED, red);
	analogWrite(LED1red, red);
	analogWrite(LED2red, green);
	analogWrite(LED1green, green);
	analogWrite(LED2green, blue);
	analogWrite(LED1blue, blue);
	analogWrite(LED2blue, red);
	// for (int i = 0; i < 7; ++i)
	// {
	// 	int pin = pins[i];
	// 	analogWrite(pin, value);
	// }
	delay(20);
}

void serialEvent() {
	if (Serial.available())
	{
		autoMode = false;
		red = Serial.read();
		green = Serial.read();
		blue = Serial.read();
	}
	
}