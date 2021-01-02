// Assigning names to pins
#define buzzer 7
#define trig 2
#define echo 4

// Declaring variables
int response=0;
int distance = 0;
int wait=1000;  // this is the value being used for different types of delays by dividing it with some number based on distance value

// Declaring constant variable for speed of sound
const float SPEED_OF_SOUND = 0.0343;

void setup() {
  // put your setup code here, to run once:

  // Setting pins to input and output modes
  pinMode(buzzer  , OUTPUT);
  pinMode(trig  , OUTPUT);
  pinMode(echo  , INPUT);

  // Starting Serial Communication at baud rate 9600
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // setting trigger pin to LOW in case it was already HIGH and then sending a pulse for 10 microseconds by
  // setting trigger pin HIGH and then setting it to LOW again
  digitalWrite(trig , LOW);
  delayMicroseconds(2);
  digitalWrite(trig , HIGH);
  delayMicroseconds(10);
  digitalWrite(trig  ,  LOW);

  // storing the response time of ultrasonic sensor using pulseIn function and storing it in response variable
  // meaning that the time sound took to be released from trigger and be collected at echo in microseconds
  response  = ( pulseIn(echo  , HIGH) ) / 1000000; //  response is divided by 10^6 to convert time in seconds
  
  // Calculating distance by using formula: S = v x t. Distance is converted in cm by multiplying with 100
  distance  = ( (response / 2)  * SPEED_OF_SOUND )  * 100;
// NOTE: response is divided by 2 because response is the time it took sound to be transmitted from trigger,
//       go in forward direction, hit any surface, come back and be collected at echo. But we only need time
//       it takes sound to travel from trigger to the surface so we divided response it in half.

  // Displaying on Serial Monitor as:  x cm. where x is value of distance
  Serial.print(distance);
  Serial.print(" cm");
  delay(100);

  // Triggering buzzer for certain time based on value of distance
  // Buzzer sounds for half second if distance is between 50cm and 60cm
  if ((distance<60) && (distance>50))
  {digitalWrite(buzzer  , HIGH);
  delay(wait  / 2);
  digitalWrite(buzzer , LOW);
  delay(wait  / 2);
  }

  // Buzzer sounds for one-third of a second if distance is between 40cm and 50cm
  if ((distance<50) && (distance>40))
  {digitalWrite(buzzer   ,  HIGH);
  delay(wait  / 3);
  digitalWrite(buzzer , LOW);
  delay(wait  / 3);
  }

  // Buzzer sounds for quater of a second if distance is between 30cm and 40cm
  if ((distance<40) && (distance>30))
  {digitalWrite(buzzer  , HIGH);
  delay(wait  / 4);
  digitalWrite(buzzer , LOW);
  delay(wait  / 4);
  }

  // Buzzer sounds for fifth of a second if distance is between 20cm and 30cm
  if ((distance<30) && (distance>20))
  {digitalWrite(buzzer  , HIGH);
  delay(wait  / 5);
  digitalWrite(buzzer , LOW);
  delay(wait  / 5);
  }

  // Buzzer sounds for sixth of a second if distance is between 10cm and 20cm
  if ((distance<20) && (distance>10))
  {digitalWrite(buzzer  , HIGH);
  delay(wait  / 6);
  digitalWrite(buzzer , LOW);
  delay(wait  / 6);
  }

  // Buzzer sounds for seventh of a second if distance is less than 10cm
  if (distance<10)
  {
  digitalWrite(buzzer , HIGH);
  delay(wait  / 7);
  digitalWrite(buzzer , LOW);
  delay(wait  / 7);
  }
}
