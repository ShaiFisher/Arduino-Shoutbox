// Include Libraries
#include "Arduino.h"
#include "LDR.h"
#include "LED.h"
#include "Switchable.h"
#include "Button.h"


// Pin Definitions
#define LDR_PIN_SIG	A3
#define LED_PIN  3
#define PUSHBUTTON_PIN  4
#define RECORD_PIN  11
#define PLAY_PIN  13



// Global variables and defines
#define THRESHOLD_ldr   100
#define DURATION 5000
//int ldrAverageLight;
int wasDark = 0;
// object initialization
LDR ldr(LDR_PIN_SIG);
LED led(LED_PIN);
Button pushButton(PUSHBUTTON_PIN);


// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    //ldrAverageLight = ldr.readAverage();
    pinMode(LED_PIN, OUTPUT);
	  pinMode(RECORD_PIN, OUTPUT);
	  pinMode(PLAY_PIN, OUTPUT);
    pushButton.init();
    wasDark = 0;
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
	// check button
	if (pushButton.onPress()) {
        Serial.println("call record");
        record();
    }
	// read ldr
    int ldrSample = ldr.read();
    Serial.print(F("Light Sample: "));
    Serial.println(ldrSample);
	
    if (ldrSample > 180) {
      // light
      if (wasDark) {
        Serial.println("light");
		// light led
        led.on();
		play();
        led.off();
		// wait until box is closed
        wasDark = 0;
      }
    } else {
      // dark
      Serial.println("dark");
      //digitalWrite(LED_PIN, LOW);
      //digitalWrite(PLAY_PIN, LOW);
      wasDark = 1;
      delay(1000);
    }
    
}

void record() {
	digitalWrite(RECORD_PIN, HIGH);
	delay(DURATION);
	digitalWrite(RECORD_PIN, LOW);
}

void play() {
	// play
	digitalWrite(PLAY_PIN, HIGH);
	// shut play pin (but continue play)
	delay(100);
	digitalWrite(PLAY_PIN, LOW);
	// wait until play is over
	delay(DURATION);
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/
