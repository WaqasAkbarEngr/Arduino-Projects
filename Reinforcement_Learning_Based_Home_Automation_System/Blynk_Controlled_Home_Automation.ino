#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <BlynkSimpleEsp8266.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

IPAddress server_addr(192,168,1,100);  // IP of the MySQL *server* here
char user[] = "MySQL username";                 // MySQL user login username
char password[] = "MySQL password";             // MySQL user login password
char ssid[]="Network SSID";
char pass[]="WiFi Network Password";
char authToken[]="Blynk Authentication Token";

byte switches[6] = {12,5,4,0,2,14};
byte devices[6] = {16,3,15,13,10,9};
char INSERT[] = "INSERT INTO mockdatabase.appliances (Device, DevStatus, triggerTime) VALUES ('%s','%s',%d)";
char query[128];
int onOffTime[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
int currTime = 0;
int prevTime = 0;
bool buttonPressed[6]={false,false,false,false,false,false};

WiFiClient client;
MySQL_Connection conn((Client *)&client);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pk.pool.ntp.org",18000);

void settingTime(){
    row_values *row = NULL;
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    cur_mem->execute("SELECT onOffTime,Sr from mockdatabase.learneddata");
    column_names * columns = cur_mem->get_columns();
    do{
      row = cur_mem->get_next_row();
      if (row != NULL)
      {
        onOffTime[(atol(row->values[1])-1)] = atol(row->values[0]);
        Serial.print("OnOffTime is: ");
        Serial.println(onOffTime[(atol(row->values[1])-1)]);
      }
      delay(100);
    }while (row != NULL);
    Serial.println("Loop ended");
    delete cur_mem;
}

void deviceOnOff(byte device, char devName[],int currentTime)
{
  
    if ( digitalRead(device) == LOW )
    {
      digitalWrite(device,HIGH);
      sprintf(query,INSERT,devName,"OFF",currentTime);
    }
    else if ( digitalRead(device) == HIGH )
    {
      digitalWrite(device,LOW);
      sprintf(query,INSERT,devName,"ON",currentTime);
    }
   MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
   cur_mem->execute(query);
   delete cur_mem;
}

void autoOn(byte setTime, byte currentTime, byte device)
{
  if ( setTime == currentTime)
    {
      digitalWrite(device,LOW);
      Serial.println("Automatic ON");
    }
}

void autoOff(byte setTime, byte currentTime, byte device)
{
  if ( setTime == currentTime)
    {
      digitalWrite(device,HIGH);
      Serial.println("Automatic OFF");
    }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(authToken,ssid,pass);
  timeClient.begin();
  while (!Serial);
  WiFi.begin(ssid,pass);
  Serial.println("Connecting to Wifi");
  while (WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Successful Connection to WiFi network\n");
  Serial.println("Connecting to Database");
  conn.connect(server_addr, 3306, user, password);
  if (conn.connect(server_addr, 3306, user, password,"mockdatabase")) {
    delay(1000);
  }
  else
    {Serial.println("Connection failed.");}

  Serial.println();
    
    Serial.println("\nFetching On/Off time of all 6 devices from learnedData table\n");
    settingTime();
    delay(1000);

    pinMode(devices[5],FUNCTION_3);
    
    for (int i=0; i<6; i++)
    {
      digitalWrite(devices[i],HIGH);
      pinMode(devices[i],OUTPUT);
    }

    Serial.println("\nInitializing Interrupts\n");
    attachInterrupt(digitalPinToInterrupt(switches[0]),light1,RISING);
    attachInterrupt(digitalPinToInterrupt(switches[1]),light2,RISING);
    attachInterrupt(digitalPinToInterrupt(switches[2]),light3,RISING);
    attachInterrupt(digitalPinToInterrupt(switches[3]),light4,RISING);
    attachInterrupt(digitalPinToInterrupt(switches[4]),fan1,RISING);
    attachInterrupt(digitalPinToInterrupt(switches[5]),fan2,RISING);
    delay(1000);
    Serial.println("\nSystem Operational\n");
    
}


void loop() {
  Blynk.run();
  timeClient.update();

  currTime = ( (100*timeClient.getHours()) + (timeClient.getMinutes()) );

  if (currTime!=prevTime)
  {
    autoOn(onOffTime[0],currTime,devices[0]);
    autoOn(onOffTime[1],currTime,devices[1]);
    autoOn(onOffTime[2],currTime,devices[2]);
    autoOn(onOffTime[3],currTime,devices[3]);
    autoOn(onOffTime[4],currTime,devices[4]);
    autoOn(onOffTime[5],currTime,devices[5]);
    autoOff(onOffTime[6],currTime,devices[6]);
    autoOff(onOffTime[7],currTime,devices[7]);
    autoOff(onOffTime[8],currTime,devices[8]);
    autoOff(onOffTime[9],currTime,devices[9]);
    autoOff(onOffTime[10],currTime,devices[10]);
    autoOff(onOffTime[11],currTime,devices[11]);

    prevTime = currTime;
  }

    if (buttonPressed[0])
    {
      deviceOnOff(devices[0],"L1",currTime);
      buttonPressed[0]=false;
    }
    else if (buttonPressed[1])
    {
      deviceOnOff(devices[1],"L2",currTime);
      buttonPressed[1]=false;
    }
    else if (buttonPressed[2])
    {
      deviceOnOff(devices[2],"L3",currTime);
      buttonPressed[2]=false;
    }
    else if (buttonPressed[3])
    {
      deviceOnOff(devices[3],"L4",currTime);
      buttonPressed[3]=false;
    }
    else if (buttonPressed[4])
    {
      deviceOnOff(devices[4],"F1",currTime);
      buttonPressed[4]=false;
    }
    else if (buttonPressed[5])
    {
      deviceOnOff(devices[5],"F2",currTime);
      buttonPressed[5]=false;
    }
 
}

ICACHE_RAM_ATTR void light1(){
  delay(500);
  Serial.println("Light 1 is triggered");
  buttonPressed[0]=true;
}

ICACHE_RAM_ATTR void light2(){
  delay(500);
  Serial.println("Light 2 is triggered");
  buttonPressed[1]=true;  
}
ICACHE_RAM_ATTR void light3(){
  delay(500);
  Serial.println("Light 3 is triggered");
  buttonPressed[2]=true;
}
ICACHE_RAM_ATTR void light4(){
  delay(500);
  Serial.println("Light 4 is triggered");
  buttonPressed[3]=true;
}
ICACHE_RAM_ATTR void fan1(){
  delay(500);
  Serial.println("Fan 1 is triggered");
  buttonPressed[4]=true;
}
ICACHE_RAM_ATTR void fan2(){
  delay(500);
  Serial.println("Fan 2 is triggered");
  buttonPressed[5]=true;
}
