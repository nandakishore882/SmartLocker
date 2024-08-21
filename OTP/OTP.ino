#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
char pass[5]={'0','0','0','0','0'};
int i=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
    if(Serial.available()>0)
    {
      pass[i]=Serial.read();
      Serial.println(pass[i]);
      i++;
      digitalWrite(7,HIGH);
      if(i==3)
      break;
      
    }
  }
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1 second
  mySerial.println("AT+CMGS=\"+917659898992\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println(pass);// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
  delay(1000);
}
