#include <Keyboard.h>

int pushPin = 9;
int potPin = A8;
int ledPin = 7;
bool fallingDetect = false;
bool toggle = false;

unsigned long bounceTime = 0;
unsigned long bounceDelay = 20;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	pinMode(pushPin, INPUT_PULLUP);
	pinMode(potPin, INPUT);
	pinMode(ledPin, OUTPUT);
}

void loop() {
	// put your main code here, to run repeatedly:
	int buttonState = digitalRead(pushPin);
	int potState = analogRead(potPin);

	Serial.println(potState);

	if (!buttonState && !fallingDetect) {
		fallingDetect = true;
		toggle = !toggle;
		digitalWrite(ledPin, toggle);
		bounceTime = millis();
	}
	else if (buttonState && (millis()-bounceTime) > bounceDelay) {
		fallingDetect = false;
	}		
  
  delay(30);
}
