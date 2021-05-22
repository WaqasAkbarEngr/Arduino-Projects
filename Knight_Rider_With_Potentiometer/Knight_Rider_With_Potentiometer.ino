int led1=3;
int led2=4;
int led3=5;
int led4=6;
int led5=7;
int led6=8;
int led7=9;
int led8=10;
int led9=12;
int led10=13;
int led11=11;

int potent=A0;
float dly=200;
float corner=dly/100;

//void led_on_off(int);

void setup() {
  // put your setup code here, to run once:
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
pinMode(led4,OUTPUT);
pinMode(led5,OUTPUT);
pinMode(led6,OUTPUT);
pinMode(led7,OUTPUT);
pinMode(led8,OUTPUT);
pinMode(led9,OUTPUT);
pinMode(led10,OUTPUT);
pinMode(led11,OUTPUT);
pinMode(potent,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 int potent_value=analogRead(potent);

 Serial.print("Potnetiometer value:   ");
 Serial.print(potent_value);

int led_speed=(potent_value*5)/1023;

 Serial.print("   Speed=   ");
 Serial.println(led_speed);

corner=led_speed;
dly=corner/2;
 
for (int i=0; i<255; i++){
  analogWrite(led1,i);
  delay(corner);
  }
  analogWrite(led1,0);

  digitalWrite(led2,HIGH);
  delay(dly);
  digitalWrite(led2,LOW);
  delay(dly);
  digitalWrite(led3,HIGH);
  delay(dly);
  digitalWrite(led3,LOW);
  delay(dly);
  digitalWrite(led4,HIGH);
  delay(dly);
  digitalWrite(led4,LOW);
  delay(dly);
  digitalWrite(led5,HIGH);
  delay(dly);
  digitalWrite(led5,LOW);
  delay(dly);
  digitalWrite(led6,HIGH);
  delay(dly);
  digitalWrite(led6,LOW);
  delay(dly);
  digitalWrite(led7,HIGH);
  delay(dly);
  digitalWrite(led7,LOW);
  delay(dly);
  digitalWrite(led8,HIGH);
  delay(dly);
  digitalWrite(led8,LOW);
  delay(dly);
  digitalWrite(led9,HIGH);
  delay(dly);
  digitalWrite(led9,LOW);
  delay(dly);
  digitalWrite(led10,HIGH);
  delay(dly);
  digitalWrite(led10,LOW);
  delay(dly);
  digitalWrite(led11,HIGH);
  delay(dly);
  digitalWrite(led11,LOW);
  delay(dly);

  for (int i=0; i<255; i++){
  analogWrite(led11,i);
  delay(corner);
  }
  analogWrite(led11,0);

  digitalWrite(led10,HIGH);
  delay(dly);
  digitalWrite(led10,LOW);
  delay(dly);
  digitalWrite(led9,HIGH);
  delay(dly);
  digitalWrite(led9,LOW);
  delay(dly);
  digitalWrite(led8,HIGH);
  delay(dly);
  digitalWrite(led8,LOW);
  delay(dly);
  digitalWrite(led7,HIGH);
  delay(dly);
  digitalWrite(led7,LOW);
  delay(dly);
  digitalWrite(led6,HIGH);
  delay(dly);
  digitalWrite(led6,LOW);
  delay(dly);
  digitalWrite(led5,HIGH);
  delay(dly);
  digitalWrite(led5,LOW);
  delay(dly);
  digitalWrite(led4,HIGH);
  delay(dly);
  digitalWrite(led4,LOW);
  delay(dly);
  digitalWrite(led3,HIGH);
  delay(dly);
  digitalWrite(led3,LOW);
  delay(dly);
  digitalWrite(led2,HIGH);
  delay(dly);
  digitalWrite(led2,LOW);
  delay(dly);
  digitalWrite(led1,HIGH);
  delay(dly);
  digitalWrite(led1,LOW);
  delay(dly);
}
