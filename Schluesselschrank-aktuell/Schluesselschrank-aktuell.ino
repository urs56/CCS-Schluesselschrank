
// Schlüsselschrank CCS
// Le 7.1.16
// le aut.reset bei Start eingebaut le 12.1.16

/*
     SMS zum öffnen der Türe sowie 
     Alarm via SMS wenn Türre Länger als 1 min. offen 

-  Mob - Bs -IT
-  Für GSM Modem M10 
-  Brücke Pin 2 + 10 bei Mega 2560
-  Brücke Pin 2 + 8 Arduino Leonardo and Arduino Yun 
-  Damit auch ältere Versionen des GSM-Shields automatisch 
   starten muss eine Lötbrücke zwischen dem Pin CTRL und D7 
   auf der Rückseite des Shields erstellt werden.
   
   ACHTUNG: zum Software upload brücke pin 8 > pin reset entfernen
   
*/


#include <GSM.h>

GSM gsmAccess(true);
GSM_SMS sms;


int pin=13;
int pin5=11;
int taster;
              int resetPin = 8;

// char array of the message
char remoteNumber[20]= "+41796406463";
// char remoteNumber[20]= "+41798071080"; 
char txtMsg[200]="CCS-Schluesselschrank-Test-offen";


void setup() 
{
  
            digitalWrite(resetPin, HIGH);
            delay(200);
            pinMode(resetPin, OUTPUT);
  
Serial.begin(9600);

            Serial.println("reset");
            delay(200);
            
            
Serial.print("AT+CMGF=4/n"); 
pinMode(pin,OUTPUT);
digitalWrite(pin,HIGH);
{
   pinMode(taster, OUTPUT);
   pinMode(pin5, INPUT);
}
while (!Serial) {
  ;
} 
Serial.println("SMS Messages Receiver");
boolean notConnected = true;
while(notConnected)
{
if(gsmAccess.begin("")==GSM_READY)
  notConnected = false;
else
{
    Serial.println("Not connected");
    delay(1000);

} 
      Serial.println("GSM initialized");
      Serial.println("Waiting for messages");
  }  
}

  void loop() 
{
 char c;
  int val=3; 
 
   val=digitalRead(pin);
 
  if (val==LOW){
  digitalWrite(pin,LOW); 
  
             Serial.println("resetting");
             delay(10);
             digitalWrite(resetPin, LOW);
             Serial.println("this never happens");
  

 }
 if (sms.available())
 {
   Serial.println("separator");
    Serial.println("numero");
   Serial.println("Message received from:");
  sms.remoteNumber("+41796406463,+41794752707,+41798071080,30092,+41792922690", 20);
  Serial.println("");
{
Serial.println(Serial.read());
}

if(sms.peek()=='#')
{
  Serial.println("Discarded SMS");
  sms.flush();
}
 Serial.println("separator");
    Serial.println("message");
  }
  
  while(c=sms.read())   
  if(c=='3'){
 digitalWrite(pin, LOW); // schaltet 'pin' ein
delay(5000); // Pause für eine Sekunde
digitalWrite(pin, HIGH); // schaltet 'pin' aus
delay(1000);

}
  
sms.flush();
 
  delay(1000);
 
 taster=digitalRead(pin5);
 // Alarm 1 Min. Verzögert und alle 10 Min wiederholt bis Türe geschlossen 
  if (taster == LOW){
        delay(30000);
     digitalWrite(taster, HIGH);
        delay(30000);
 {
 sendSMS(); 

}

Serial.println("pin5");

 }

 }
void sendSMS(){

   Serial.print("Message to mobile number: ");
   Serial.println(remoteNumber);

   // sms text
   Serial.println("SENDING");
   Serial.println();
   Serial.println("Message:");
   Serial.println(txtMsg);

   // send the message
   sms.beginSMS(remoteNumber);
   sms.print(txtMsg);
   sms.endSMS(); 
   delay(1000);
   
   Serial.println("\nCOMPLETE!\n"); 
   
  }
 


