#include<Servo.h>

#define leftETS A0
#define leftSXTS A1
#define leftSYTS A2
#define rightETS A3
#define rightSXTS A4
#define rightSYTS A5

#define elbowLServoDefault 180
#define elbowRServoDefault 0
#define shXLServoDefault 180
#define shYLServoDefault 0
#define shXRServoDefault 0
#define shYRServoDefault 180 

int elbowLSpeed,elbowRSpeed,shoulderLXSpeed,shoulderRXSpeed,shoulderLYSpeed,shoulderRYSpeed;
int eLDrive,eRDrive,sXLDrive,sYLDrive,sXRDrive,sYRDrive;


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

void speedMapping(int speeed,int thumbstick,int tsmin,int tsmax,int speedmin,int speedmax)
{
  speeed=map(analogRead(thumbstick),tsmin,tsmax,speedmin,speedmax);
}

void servoSpeed(int speedy, int drive, int servoDefault)
{
  if(speedy!=0)
  {
    drive = drive + speedy;
  }
  else
  {
    drive = servoDefault;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  speedMapping(elbowLSpeed,leftETS,0,1023,-10,10);
  speedMapping(elbowRSpeed,rightETS,0,1023,-10,10);
  speedMapping(shoulderLXSpeed,leftSXTS,0,1023,-10,10);
  speedMapping(shoulderRXSpeed,rightSXTS,0,1023,-10,10);
  speedMapping(shoulderLYSpeed,leftSYTS,0,1023,-10,10);
  speedMapping(shoulderRYSpeed,rightSYTS,0,1023,-10,10);

  servoSpeed(elbowLSpeed, eLDrive, elbowLServoDefault);
  servoSpeed(elbowRSpeed, eRDrive, elbowRServoDefault);
  servoSpeed(shoulderLXSpeed, sXLDrive, shXLServoDefault);
  servoSpeed(shoulderLYSpeed, sYLDrive, shYLServoDefault);
  servoSpeed(shoulderRXSpeed, sXRDrive, shXRServoDefault);
  servoSpeed(shoulderRYSpeed, sYRDrive, shYRServoDefault);
  
  EServoL.write(eLDrive);
  SXServoL.write(sXLDrive);
  SYServoL.write(sYLDrive);
  EServoR.write(eRDrive);
  SXServoR.write(sXRDrive);
  SYServoR.write(sYRDrive);
  
delay(100);
}
