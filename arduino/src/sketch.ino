const int Led1RedPin = 3;
const int Led1BluePin = 5;
const int Led1GreenPin = 6;

const int Led2RedPin = 9;
const int Led2BluePin = 10;
const int Led2GreenPin = 11;

const int pins[6] = {Led1RedPin, Led1GreenPin, Led1BluePin, Led2RedPin, Led2GreenPin, Led2BluePin};

volatile bool autoMode = true;

volatile int color[6];

void setup() {
    Serial.begin(57600);
    Serial.println("go!");
	for (int i = 0; i < 6; ++i)
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
		float value = millis() / 500.0;
		color[0] = sinToPin(value);
		color[1] = sinToPin(value + 1.5);
		color[2] = sinToPin(value + 3.0);

		color[3] = color[1];
		color[4] = color[2];
		color[5] = color[0];
	}

	for (int i = 0; i < 6; ++i)
	{
		analogWrite(pins[i], color[i]);
	}

	// delay(20);
}

void serialEvent() {
	if (Serial.available() >= 4)
	{
		autoMode = false;
		int dioderIndex = Serial.read();
		dioderIndex = (dioderIndex == 0 ? 0 : 1);

		color[dioderIndex * 3 + 0] = Serial.read();
		color[dioderIndex * 3 + 1] = Serial.read();
		color[dioderIndex * 3 + 2] = Serial.read();

		Serial.println("ok");
	}
	
}