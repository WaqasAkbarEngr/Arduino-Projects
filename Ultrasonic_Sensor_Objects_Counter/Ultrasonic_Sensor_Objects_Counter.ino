// defining pins of ultrasonic sensor
#define trigger 13
#define echo 12

// defining variables used in this project
#define SPEED_OF_SOUND 340
int counter = 0;

void setup() {
  // put your setup code here, to run once:

  // Starting serial communication at baud rate 9600
  Serial.begin(9600);

  // Setting trigger and echo pin to input/output
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Setting trigger pin to LOW in case it was already HIGH
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);

  // Sending ultrasounds from trigger for 10 microseconds and checking their receipt time at echo
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);

  float timeTaken = pulseIn(echo,HIGH) / 2; // timeTaken is divided by two because it is the time of ultrasound from transmission to reception after striking with object

  // calculating distance by using formula S = v x t

  float distance = timeTaken * SPEED_OF_SOUND;  // the distance is in micrometer as time is in microsecond

  // changing distance into millimeter
  distance = distance / 1000;

  // checking whether any object comes in the way of ultrasound
  if (distance < 300)
  {
    counter++;
    Serial.print("The number of count is = ";
    Serial.println(counter);

    while(distance<300){
      // this while loop is making sure that counter does not go up in case of large or slow moving object
      // The counter will only go up in case one object has passed and other object comes in the way of ultrasound
    }
  }

}
