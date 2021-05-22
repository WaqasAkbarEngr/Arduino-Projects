#include<Servo.h>

#define leftETS A0
#define leftSXTS A1
#define leftSYTS A2
#define rightETS A3
#define rightSXTS A4
#define rightSYTS A5

Servo EServoL,SXServoL,SYServoL,EServoR,SXServoR,SYServoR;

void setup() {
  // put your setup code here, to run once:
pinMode(leftETS,INPUT);
pinMode(leftSXTS,INPUT);
pinMode(leftSYTS,INPUT);
pinMode(rightETS,INPUT);
pinMode(rightSXTS,INPUT);
pinMode(rightSYTS,INPUT);

EServoL.attach(3);
SXServoL.attach(5);
SYServoL.attach(6);
EServoR.attach(9);
SXServoR.attach(10);
SYServoR.attach(11);
}

void loop() {
  // put your main code here, to run repeatedly:
EServoL.write(map(analogRead(leftETS),0,1023,180,0));
SXServoL.write(map(analogRead(leftSXTS),0,1023,180,0));
SYServoL.write(map(analogRead(leftSYTS),0,1023,0,180));
EServoR.write(map(analogRead(rightETS),0,1023,0,180));
SXServoR.write(map(analogRead(rightSXTS),0,1023,0,180));
SYServoR.write(map(analogRead(rightSYTS),0,1023,180,0));
delay(100);
}
