/*
JDeck.ino
By Jaden Keener, 1/19/23
Written for the Pro Micro (ATMega32U4)

Control software for my DIY streamdeck rip off.
Primary use is as a Voicemeeter Banana control surface.

Features:
* Six customizable macro buttons
* 3 volume control knobs
* Togglable LED button lighting

*/


#include <Keyboard.h>

// Push button pins
int buttonPin1 = 7;
int buttonPin2 = 8;
int buttonPin3 = 9;
int buttonPin4 = 14;
int buttonPin5 = 16;
int buttonPin6 = 10;
int buttonPins[6] = {buttonPin1,buttonPin2,buttonPin3,buttonPin4,buttonPin5,
					 buttonPin6};
int buttonReads[6] = {0};

// Pot pins
int knobPin1 = A3;
int knobPin2 = A2;
int knobPin3 = A1;
int knobPins[3] = {knobPin1,knobPin2,knobPin3};
int knobReads[3] = {0};


// LED Pins
int ledPin1 = 3;
int ledPin2 = 4;
int ledPin3 = 5;
int ledPin4 = 6;
int ledPin5 = 18;
int ledPin6 = 15;
int ledPins[6] = {ledPin1,ledPin2,ledPin3,ledPin4,ledPin5,ledPin6};
bool ledStates[6] = {0}; // not sure if you can assign arrays like this

// Debouncing and falling edge detection
unsigned long bounceTimes[6] = {0}; // don't change, used for storage
unsigned long bounceDelay = 20; // debounce grace period (ms)
bool fallingEdge[6] = {false}; // used to detect falling edges


// Initialize
void setup() {
	
	// init serial
	Serial.begin(9600);
	
	
	// set DDRs
	for (int i : buttonPins) {
		pinMode(i, INPUT_PULLUP);
	}
	
	for (int i : knobPins) {
		pinMode(i, INPUT);
	}
	
	for (int i : ledPins) {
		pinMode(i, OUTPUT);
	}
	
	
	// // set DDRs
	// pinMode(buttonPin1, INPUT_PULLUP);
	// pinMode(buttonPin2, INPUT_PULLUP);
	// pinMode(buttonPin3, INPUT_PULLUP);
	// pinMode(buttonPin4, INPUT_PULLUP);
	// pinMode(buttonPin5, INPUT_PULLUP);
	// pinMode(buttonPin6, INPUT_PULLUP);
	
	// pinMode(knobPin1, INPUT);
	// pinMode(knobPin2, INPUT);
	// pinMode(knobPin3, INPUT);
	
	// pinMode(ledPin1, OUTPUT);
	// pinMode(ledPin2, OUTPUT);
	// pinMode(ledPin3, OUTPUT);
	// pinMode(ledPin4, OUTPUT);
	// pinMode(ledPin5, OUTPUT);
	// pinMode(ledPin6, OUTPUT);
}



// loop
void loop() {
	
	// read buttons
	for (int i = 0; i < 6; i++) {
		buttonReads[i] = digitalRead(buttonPins[i]);
	}
	
	// read pots
	for (int i = 0; i <3; i++) {
		knobReads[i] = analogRead(knobPins[i]);
	}

	// toggle LEDs on falling edge of buttons
	updateButtons(buttonReads);
	
}



/* 	updateButtons()

	Toggle button/LED states based on buttonReads
	Button states are only updated on the falling edge (buttons normally high).
	
	Also includes debouncing. Change debounce grace time in header.
	
 */ 
void updateButtons(int buttonReads[6]) {
	
	for (int i = 0; i < 6; i++) {
		// if the button is being pressed
		if (buttonReads[i] == 0 && fallingEdge[i]) {
			// Update ledStates and write to LEDs
			ledStates[i] = !ledStates[i];
			digitalWrite(ledPins[i], ledStates[i]);
			
			// Play the macro
			sendStrokes(i, ledStates[i]);
			
			// Debouncing. We won't re-enter this statement until after
			// debounce period.
			bounceTimes[i] = millis();
			fallingEdge[i] = false;
		}
		// only re-enable falling edge detection after debounce period
		else if (buttonReads[i] && (millis() - bounceTimes[i]) > bounceDelay) {
			fallingEdge[i] = true;
		}
	}
}

/* sendStrokes()
	
	Send keystrokes/macros to computer based on button states.
	This is also where you should come to reassign macro buttons.

*/
void sendStrokes(int button, int state) {
	if (button == 0) {
		if (state) {
			Serial.println("Button 1 HIGH!");
		}
		else {
			Serial.println("Button 1 LOW!");
		}
	}
	else if (button == 1) {
		if (state) {
			Serial.println("Button 2 HIGH!");
		}
		else {
			Serial.println("Button 2 LOW!");
		}	
	}
	else if (button == 2) {
		if (state) {
			Serial.println("Button 3 HIGH!");
		}
		else {
			Serial.println("Button 3 LOW!");
		}	
	}
	else if (button == 3) {
		if (state) {
			Serial.println("Button 4 HIGH!");
		}
		else {
			Serial.println("Button 4 LOW!");
		}	
	}
	else if (button == 4) {
		if (state) {
			Serial.println("Button 5 HIGH!");
		}
		else {
			Serial.println("Button 5 LOW!");
		}	
	}
	else if (button == 5) {
		if (state) {
			Serial.println("Button 6 HIGH!");
		}
		else {
			Serial.println("Button 6 LOW!");
		}	
	}
	
}
	