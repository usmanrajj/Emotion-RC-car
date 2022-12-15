/*
Rajj YT 
Video link:
https://youtu.be/X-6Vlneo5Gw

Circuit & Diagram :
https://drive.google.com/drive/u/0/folders/1Mp1IB4cGCv4kvosOSTHlqkJXNuBFiVxO

Servo Library Library :
https://github.com/arduino-libraries/Servo

Led 8x8 Dot Matrix Library :
https://github.com/nfhktwrbq/LedMatrix8x8

Binary conversion librarY Library :
https://github.com/esp8266/Arduino/blob/master/cores/esp8266/binary.h
*/
#include <Servo.h>       // Add servo library
#include "LedControl.h"  // Add Dot matrix library
#include "binary.h"      // Add Binary library

int clk = 4;  // attach pin 4 with CLK
int cs = 3;   // attach pin 3 with CS
int din = 2;  // attach pin 2 with DIN

int left_back = 11;     // attach pin 11 with IN4
int left_forward = 10;  // attach pin 10 with IN3
int right_forward = 9;  // attach pin 9 with IN2
int right_back = 8;     // attach pin 8 with IN1

LedControl mat = LedControl(din, clk, cs, 1);

Servo rajj;             // servo name rajj
char usman;             // data store in usman(variable)

// coding of matrix
byte f[] = { B00011000, B00111100, B01111110, B11111111, B00011000, B00011000, B00011000, B00011000 };
byte b[] = { B00011000, B00011000, B00011000, B00011000, B11111111, B01111110, B00111100, B00011000 };
byte r[] = { B00001000, B00001100, B00001110, B11111111, B11111111, B00001110, B00001100, B00001000 };
byte l[] = { B00010000, B00110000, B01110000, B11111111, B11111111, B01110000, B00110000, B00010000 };
byte off[] = { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 };
byte on[] = { B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111 };
byte smile[] = {B00000000, B01100110, B01100110, B00000000, B10000001, B01000010, B00111100, B00000000 };
byte anger[] = {B00000000,B01000010,B01100110,B00000000,B00000000,B00111100,B01000010,B10000001};
void setup() {

  // motors pin
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // Servo pins
  rajj.attach(5);         // attach servo motor with pin 5
  rajj.write(90);         // initial angle 90'

  // 8x8 matrix pins
  pinMode(clk, OUTPUT);
  pinMode(cs, OUTPUT);
  pinMode(din, OUTPUT);

  // initialize serial monitor
  Serial.begin(9600);

  // clear display of matrix
  mat.shutdown(0, false);  // do not turn off dot matrix
  mat.setIntensity(0, 7);  // 0-15 brightness Between 0 - 15
    for (int i = 0; i < 8; i++)
    mat.setRow(0, i, anger[i]);
  delay(100);
}
void loop() {

  if (Serial.available()) {
    usman = Serial.read();
    Serial.println(usman);
  }

  switch (usman) {
    case 'F':  // Forward
      digitalWrite(right_back, HIGH);
      digitalWrite(left_back, HIGH);

      for (int i = 0; i < 8; i++)
        mat.setRow(0, i, f[i]);

      break;
    case 'B':  //Reverse
      digitalWrite(left_forward, HIGH);
      digitalWrite(right_forward, HIGH);

      for (int i = 0; i < 8; i++)
        mat.setRow(0, i, b[i]);
      break;

    case 'L':  //turn left
      digitalWrite(left_forward, HIGH);
      digitalWrite(right_back, HIGH);

      for (int i = 0; i < 8; i++)
        mat.setRow(0, i, r[i]);
      break;

    case 'R':  //turn Right
      digitalWrite(left_back, HIGH);
      digitalWrite(right_forward, HIGH);

      for (int i = 0; i < 8; i++)
        mat.setRow(0, i, l[i]);
      break;

    case 'S':  // stop
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);

      for (int i = 0; i < 8; i++)
        mat.setRow(0, i, smile[i]);
      break;

    case '0':
      rajj.write(0);
      break;
    case '1':
      rajj.write(20);
      break;
    case '2':
      rajj.write(40);
      break;
    case '3':
      rajj.write(60);
      break;
    case '4':
      rajj.write(80);
      Serial.println("angle = 260");
      break;
    case '5':
      rajj.write(90);
      Serial.println("angle = 90");
      break;
    case '6':
      rajj.write(100);
      Serial.println("angle = 100");
      break;
    case '7':
      rajj.write(120);
      Serial.println("angle = 120");
      break;
    case '8':
      rajj.write(140);
      Serial.println("angle = 140");
      break;
    case '9':
      rajj.write(160);
      break;
    case 'q':
      rajj.write(180);
      break;
  }
}