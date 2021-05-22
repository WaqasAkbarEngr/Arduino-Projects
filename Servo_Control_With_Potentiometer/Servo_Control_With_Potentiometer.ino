#include<Servo.h>

#define pot A0
#define servomotor 11

int potential_value;
int servo_input;

Servo servo;
void setup() {
  // put your setup code here, to run once:
servo.attach(servomotor);
pinMode(pot,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
potential_value=analogRead(pot);
servo_input=map(potential_value,0,1023,0,180);
delay(100);
Serial.print("Value of potentiometer: ");
Serial.print(potential_value);
Serial.print("        Input to servo motor: ");
Serial.println(servo_input);
servo.write(servo_input);
}
