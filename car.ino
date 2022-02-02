// CARL 6.1 CODE - Sept 2018 codemyrobot@gmail.com
// This code will run the motors, RGB light and buzzer
// new ping ultrasonic is commented out
// teachers upload your student video to the codemyrobotchallenge.com
#include <NewPing.h>
/////////////////////////////////////////////////
// Pin defines
////////////////////////////////////////////////
#define MPIN1B 5 // motor 1 pin B
#define MPIN1A 6 // motor 1 pin A
#define MPIN2A 9 // motor 2 pin A
#define MPIN2B 10 // motor 2 pin B
#define buzzerPin 12
///////////////////////////////////////////////
// SRF04 pin definitions
//////////////////////////////////////////////
#define TRIGGER_PIN 7
#define ECHO_PIN 8
#define MAX_DISTANCE 200
#define REDPIN A2
#define GREENPIN A1
#define BLUEPIN A0
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
////////////////////////////////////////////////////////
// Variables
///////////////////////////////////////////////////////
int rSpeed = 195; // robot's max speed (used in Move()
int TS1 = 75; // turn speed 1
int FS = 75; // forward speed: the speed at which both motors turn
long choose;
///////////////////////////////////////////////////////
// move function - we pass a speed for each wheel m1,m2
// for each motor, one pin is held low, the other pin is toggled
// the other drive method uses two pwm signals,
///////////////////////////////////////////////////////
void Move(int m1, int m2) {
  if (m1 < 0) { // forward
    analogWrite(MPIN1A, rSpeed * abs(m1) / 100);
    analogWrite(MPIN1B, 0);
  } else { // reverse
    analogWrite(MPIN1A, 0);
    analogWrite(MPIN1B, rSpeed * m1 / 100);
  }
  if (m2 < 0) { // forward
    analogWrite(MPIN2A, rSpeed * abs(m2) / 100);
    analogWrite(MPIN2B, 0);
  } else { // reverse
    analogWrite(MPIN2A, 0);
    analogWrite(MPIN2B, rSpeed * m2 / 100);
  }
}



void Sense (int delayms) {
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); //
  Serial.println("cm");

  if (sonar.ping_cm() <= 50) {
    choose = random (0, 3);
    if (choose == 1) {
      Serial.print(choose);
      Move(0, 0); delay(250); // stop
      Move(0, 75); delay(600); Move(0, 0); delay(250); // back to the left 90deg
    }
    if (choose == 2) {
      Serial.print(choose);
      Move(0, 0); delay(250);
      Move(75, 0); delay(600); Move(0, 0); delay(250);
    }
  }

}
////////////////////////////////////////////
// Stop Function
///////////////////////////////////////////
void Stop( int delayms) {
  RGBled(1, 0, 0); //RED
  Move(0, 0);
  delay(delayms);
}
//////////////////////////////////////////
// Forward Function
///////////////////////////////////////
void Forward(int delayms) {
  RGBled(0, 1, 0); //GREEN
  Move(-75, -75);
  delay(delayms);
  Move(0, 0);
}
/////////////////////////////////////
// Reverse Function
////////////////////////////////////
void Reverse(int delayms) {
  RGBled(0, 0, 1); //BLUE
  Move(75, 75);
  delay(delayms);
  Move(0, 0);
}
/////////////////////////////////////
// TurnRight Function
///////////////////////////////////
void TurnRight(int delayms) {
  RGBled(1, 1, 0); //YELLOW
  Move(-75, 75);
  delay(delayms);
  Move(0, 0);
}
///////////////////////////////////
// TurnLeft Function
//////////////////////////////////
void TurnLeft(int delayms) {
  RGBled(0, 1, 1); //CYAN
  Move(75, -75);
  delay(delayms);
  Move(0, 0);
}
///////////////////////////////////////
// Forward Function
//////////////////////////////////////
void RGBled(int redValue, int greenValue, int blueValue) {
  digitalWrite(REDPIN, redValue);
  digitalWrite(GREENPIN, greenValue);
  digitalWrite(BLUEPIN, blueValue);
}
//////////////////////////////////////////////////
// Buzzer Function
////////////////////////////////////////////////
void buzzer(int duration_ms) {
  digitalWrite(buzzerPin, HIGH);
  delay(duration_ms);
  digitalWrite(buzzerPin, LOW);
}
////////////////////////////////////////////
// Setup - runs once
///////////////////////////////////////////
void setup() {
  Serial.begin(115200); // serial for serial port
  pinMode(MPIN1B, OUTPUT); // set motor pin as output
  pinMode(MPIN1A, OUTPUT); // set motor pin as output
  pinMode(MPIN2A, OUTPUT); // set motor pin as output
  pinMode(MPIN2B, OUTPUT); // set motor pin as output
  pinMode(buzzerPin, OUTPUT); // set buzzer pin as output
  pinMode(REDPIN, OUTPUT); // set LED outputs
  pinMode(GREENPIN, OUTPUT); // set LED outputs
  pinMode(BLUEPIN, OUTPUT); // set LED outputs
  Stop(2000);
  buzzer(50);
}
///////////////////////////////////////////////
// main loop - runs infinetly
////////////////////////////////////////////
void loop() {
  Forward(300);
  Sense(1);
}
//Move(75,0);delay(500); // back to the right 90deg
//Move(0,75);delay(500); // back to the left 90deg
//Move(-75,0);delay(500); // fwd to the right 90deg
//Move(0,-75);delay(500); // fwd to the left 90deg

/*
  if(sonar.ping_cm()<= 1){
  Move(0,0);delay(250); // stop
  Move(0,75);delay(600); Move(0,0);delay(250); // back to the left 90deg
  Move(-75,-75);delay(750); Move(0,0);delay(250); // fwd for 250 secs
  Move(75,0);delay(500); Move(0,0);delay(250); // back to the right 90deg
  Move(-75,-75);delay(1000); Move(0,0);delay(250); // fwd for 500 secs
  Move(75,0);delay(600); Move(0,0);delay(250); // back to the right
  Move(-75,-75);delay(700); Move(0,0);delay(250); // fwd for 250 secs
  Move(0,75);delay(750); Move(0,0);delay(250); // back to the left 90deg
  Move(-75,-75);delay(300); Move(0,0);delay(250); // fwd for 500 secs
  Move(0,0);delay(10000);
  }
  Move(-75,-75);
*/
