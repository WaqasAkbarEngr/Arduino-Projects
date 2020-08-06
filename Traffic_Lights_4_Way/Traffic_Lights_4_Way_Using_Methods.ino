int green[4]={0,0,0,0};
int yellow[4]={0,0,0,0};
int red[4]={0,0,0,0};

void assign_pin_number()
{
    for (int i=0; i<4; i++)
    {
      green[i]=i;
      yellow[i]=i+4;
      red[i]=i+8;
    }
}

void init_LED_pin()
{
    for (int i=0; i<4; i++)
  {
    pinMode(green[i],OUTPUT);
    pinMode(yellow[i],OUTPUT);
    pinMode(red[i],OUTPUT);
    digitalWrite(green[i],LOW);
    digitalWrite(yellow[i],LOW);
    digitalWrite(red[i],HIGH);  
  }
}

void signal_operation()
{
  for (int i=0; i<4; i++)
  {
    delay(5000);
    digitalWrite(yellow[i],HIGH);
    if ((i+1)==4)
    {
    digitalWrite(yellow[0],HIGH);
    }
    else
    {
      digitalWrite(yellow[i+1],HIGH);
    }
    digitalWrite(green[i],LOW);
    delay(1000);
    digitalWrite(red[i],HIGH);
    digitalWrite(yellow[i],LOW);
    if ((i+1)<4)
    {
    digitalWrite(yellow[i+1],LOW);
    digitalWrite(green[i+1],HIGH);
    digitalWrite(red[i+1],LOW);
    }
    else
    {
      digitalWrite(yellow[0],LOW);
      digitalWrite(green[0],HIGH);
      digitalWrite(red[0],LOW);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
assign_pin_number();
init_LED_pin();

digitalWrite(green[0],HIGH);
digitalWrite(red[0],LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
signal_operation();
}
