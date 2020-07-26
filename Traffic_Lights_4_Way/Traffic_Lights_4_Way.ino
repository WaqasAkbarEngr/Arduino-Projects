// First of all, variable are initialized with respective GPIO
int greenLED1=0;
int greenLED2=3;
int greenLED3=9;
int greenLED4=6;
int yellowLED1=1;
int yellowLED2=4;
int yellowLED3=10;
int yellowLED4=7;
int redLED1=2;
int redLED2=5;
int redLED3=11;
int redLED4=8;

void setup() {
  // put your setup code here, to run once:
pinMode(greenLED1,OUTPUT);
pinMode(greenLED2,OUTPUT);
pinMode(greenLED3,OUTPUT);
pinMode(greenLED4,OUTPUT);
pinMode(yellowLED1,OUTPUT);
pinMode(yellowLED2,OUTPUT);
pinMode(yellowLED3,OUTPUT);
pinMode(yellowLED4,OUTPUT);
pinMode(redLED1,OUTPUT);
pinMode(redLED2,OUTPUT);
pinMode(redLED3,OUTPUT);
pinMode(redLED4,OUTPUT);

//Initially, Lights of First signal are turned on i.e. Red&Yellow light of signal 1 is off while Green light of signal 1 is on
digitalWrite(greenLED1,HIGH);
digitalWrite(greenLED2,LOW);
digitalWrite(greenLED3,LOW);
digitalWrite(greenLED4,LOW);
digitalWrite(yellowLED1,LOW);
digitalWrite(yellowLED2,LOW);
digitalWrite(yellowLED3,LOW);
digitalWrite(yellowLED4,LOW);
digitalWrite(redLED1,LOW);
digitalWrite(redLED2,HIGH);
digitalWrite(redLED3,HIGH);
digitalWrite(redLED4,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
delay(5000);
// After delay of 5 sec, Green light of current traffic signal turns off and yellow light of current and next traffic signal turn on. After that wait for 1 sec delay 
digitalWrite(greenLED1,LOW);
digitalWrite(yellowLED1,HIGH);
digitalWrite(yellowLED2,HIGH);
delay(1000);
// After delay of 1 sec, yellow light of both current and next traffic signal turn off. After that red light of current traffic and green light of next traffic signal turn on.
digitalWrite(yellowLED1,LOW);
digitalWrite(redLED1,HIGH);
digitalWrite(yellowLED2,LOW);
digitalWrite(redLED2,LOW);
digitalWrite(greenLED2,HIGH);
// The above process is repeated again for all traffic signals
delay(5000);
digitalWrite(greenLED2,LOW);
digitalWrite(yellowLED2,HIGH);
digitalWrite(yellowLED3,HIGH);
delay(1000);
digitalWrite(yellowLED2,LOW);
digitalWrite(yellowLED3,LOW);
digitalWrite(redLED2,HIGH);
digitalWrite(redLED3,LOW);
digitalWrite(greenLED3,HIGH);
delay(5000);
digitalWrite(greenLED3,LOW);
digitalWrite(yellowLED3,HIGH);
digitalWrite(yellowLED4,HIGH);
delay(1000);
digitalWrite(yellowLED3,LOW);
digitalWrite(yellowLED4,LOW);
digitalWrite(redLED3,HIGH);
digitalWrite(redLED4,LOW);
digitalWrite(greenLED4,HIGH);
delay(5000);
digitalWrite(greenLED4,LOW);
digitalWrite(yellowLED4,HIGH);
digitalWrite(yellowLED1,HIGH);
delay(1000);
digitalWrite(yellowLED4,LOW);
digitalWrite(yellowLED1,LOW);
digitalWrite(redLED4,HIGH);
digitalWrite(redLED1,LOW);
digitalWrite(greenLED1,HIGH);
}
