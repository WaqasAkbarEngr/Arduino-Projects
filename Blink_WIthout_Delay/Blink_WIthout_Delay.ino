#define LED 0
#define timeDelay 500
unsigned long currentTime;
unsigned long previousTime;
bool isLedLit;


void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  currentTime = 0;
  previousTime = 0;
  isLedLit = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  while ((currentTime - previousTime) < timeDelay)
  {
    	isLedLit = !isLedLit;
	previousTime = currentTime;
  }
  if (isLedLit)
  {
    	digitalWrite(LED, HIGH);
  }
  if (!isLedLit)
  {
    	digitalWrite(LED, LOW);
  }
}