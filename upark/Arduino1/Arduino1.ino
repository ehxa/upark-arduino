#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int cm0 = 0, cm1 = 0, cm2 = 0, cm3 = 0;
const int triggerPin0 = 11, echoPin0 = 12;   
const int triggerPin1 = 5, echoPin1 = 6;  
const int triggerPin2 = 3, echoPin2 = 4; 
const int triggerPin3 = 1, echoPin3 = 2; 

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin0, OUTPUT);
  pinMode(echoPin0, INPUT);
  pinMode(triggerPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(triggerPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  matrix.begin();
  matrix.textScrollSpeed(50);
  matrix.textFont(Font_5x7);
}

long readUltrasonicDistance(int triggerpin, int echopin) {
  digitalWrite(triggerpin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin, LOW);
  return pulseIn(echopin, HIGH);
}

void displayMessage(const char* text) {
  matrix.beginDraw();
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
}

void loop() {
  cm0 = 0.01715 * readUltrasonicDistance(triggerPin0, echoPin0);
  cm1 = 0.01715 * readUltrasonicDistance(triggerPin1, echoPin1);
  cm2 = 0.01715 * readUltrasonicDistance(triggerPin2, echoPin2);
  cm3 = 0.01715 * readUltrasonicDistance(triggerPin3, echoPin3);

  String a1 = "A1-";
  String a2 = "A2-";
  String a3 = "A3-";
  String a4 = "A4-";

  if (cm0 < 10) {
    displayMessage((a1 + "O").c_str());
    Serial.println(a1 + "O");
  } else {
    displayMessage((a1 + "L").c_str());
    Serial.println(a1 + "L");
  }

  if (cm1 < 10) {
    displayMessage((a2 + "O").c_str());
    Serial.println(a2 + "O");
  } else {
    displayMessage((a2 + "L").c_str());
    Serial.println(a2 + "L");
  }

  if (cm2 < 10) {
    displayMessage((a3 + "O").c_str());
    Serial.println(a3 + "O");
  } else {
    displayMessage((a3 + "L").c_str());
    Serial.println(a3 + "L");
  }

  if (cm3 < 10) {
    displayMessage((a4 + "O").c_str());
    Serial.println(a4 + "O");
  } else {
    displayMessage((a4 + "L").c_str());
    Serial.println(a4 + "L");
  }

  delay(100);
}