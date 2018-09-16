// Include Libraries
#include "Arduino.h"
#include "LDR.h"
#include "Switchable.h"
#include "Button.h"

// Pin Definitions
// https://www.circuito.io/static/reply/index.html?solutionId=5a3d4c6bfb33e200225be712&solutionPath=storage.circuito.io
// https://www.elabpeers.com/isd1820-voice-recording-module.html
#define LDR_PIN	A1      // with 10k ohm resistor
#define LED_PIN  0          // with 330 ohm resistor
#define PUSHBUTTON_PIN  3   // with 10k ohm resistor
#define RECORD_PIN  1      // to ISD1820 
#define PLAY_PIN  4        // to ISD1820 

// Global variables and defines
#define MAX_DURATION 5000
#define LIGHT_LIMIT 250
#define CYCLE_DURATION 100

int duration;
int wasDark;

// object initialization
LDR ldr(LDR_PIN);
Button pushButton(PUSHBUTTON_PIN);


// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    //Serial.begin(9600);
    //while (!Serial) ; // wait for serial port to connect. Needed for native USB
    //Serial.println("start");
    
    //ldrAverageLight = ldr.readAverage();
    pinMode(LDR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
	  pinMode(RECORD_PIN, OUTPUT);
	  pinMode(PLAY_PIN, OUTPUT);
    pushButton.init();
    wasDark = 0;

    flash(LED_PIN, 3, 3);
}

void loop() 
{
	// check button
	if (pushButton.onPress()) {
      //Serial.println("call record");
      flash(LED_PIN, 4, 1);
      waitUntillOpened();
      record();
  } 
  
	// read ldr
    if (isLight()) {
      digitalWrite(LED_PIN, HIGH);
      if (wasDark) {
        //Serial.println("light");
		    play();
		    // wait until box is closed
        waitUntillClosed(false);
        wasDark = 0;
      }
    } else {
      // dark
      digitalWrite(LED_PIN, LOW);
      //Serial.println("dark");
      wasDark = 1;
      //delay(1000);
    }
    delay(CYCLE_DURATION);
    
}

int isDark() {
  int ldrSample = ldr.read();
  //Serial.print(F("Light Sample: "));
  //Serial.println(ldrSample);
  return (ldrSample < LIGHT_LIMIT);
}

int isLight() {
  return !isDark();
}

void waitUntillOpened() {
  //log("waitUntillOpened: start");
  while (isDark()) {
    //log("waitUntillOpened: wait");
    delay(CYCLE_DURATION);
  }
  //log("waitUntillOpened: end");
}

int waitUntillClosed(bool isRecording) {
  //log('waitUntillClosed: start');
  int duration = 0;
  while (isLight()) {
    //log('waitUntillClosed: wait');
    if (isRecording) {
      duration += flash(LED_PIN, 1, 5);
    } else {
      delay(CYCLE_DURATION);
      duration += CYCLE_DURATION;
    }
  }
  //log('waitUntillClosed: end');
  return duration;
}

void record() {
  //log("record");
	digitalWrite(RECORD_PIN, HIGH);
  duration = waitUntillClosed(true);
  //log("duration", duration);
	//delay(MAX_DURATION);
	digitalWrite(RECORD_PIN, LOW);
}

void play() {
	digitalWrite(PLAY_PIN, HIGH);
	// shut play pin (but continue play)
	delay(100);
	digitalWrite(PLAY_PIN, LOW);
	// wait until play is over
	delay(duration);
}

int flash(int pin, int times, int delay1) {
  delay1 *= 50;
  for(int i=0; i<times; i++) {
    digitalWrite(pin, HIGH);
    delay(delay1);
    digitalWrite(pin, LOW);
    delay(delay1);
  }
  return times * 2 * delay1 * 50;
}

void log(String str) {
  //Serial.println(str);
}

void log(String desc, int num) {
  //Serial.print(desc);
  //Serial.print(": ");
  //Serial.println(num);
}

void log(String str1, int num, String str2) {
  //Serial.print(str1);
  //Serial.print(num);
  //Serial.println(str2);
}

