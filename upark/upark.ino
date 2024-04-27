#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int cm0 = 0, cm1 = 0, cm2 = 0, cm3 = 0;
const int triggerPin0 = 12, echoPin0 = 13;   
const int triggerPin1 = 8, echoPin1 = 9;  
const int triggerPin2 = 6, echoPin2 = 7; 
const int triggerPin3 = 3, echoPin3 = 4; 

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

  Serial.print("Distance Sensor 0: ");
  Serial.print(cm0);
  Serial.println(" cm");
  Serial.print("Distance Sensor 1: ");
  Serial.print(cm1);
  Serial.println(" cm");
  Serial.print("Distance Sensor 2: ");
  Serial.print(cm2);
  Serial.println(" cm");
  Serial.print("Distance Sensor 3: ");
  Serial.print(cm3);
  Serial.println(" cm");

  if (cm0 < 10) {
    displayMessage("A1-O");
  } else {
    displayMessage("A1-L");
  }

  if (cm1 < 10) {
    displayMessage("A2-O");
  } else {
    displayMessage("A2-L");
  }

  if (cm2 < 10) {
    displayMessage("A3-O");
  } else {
    displayMessage("A3-L");
  }

  if (cm3 < 10) {
    displayMessage("A4-O");
  } else {
    displayMessage("A4-L");
  }

  delay(100);
}
