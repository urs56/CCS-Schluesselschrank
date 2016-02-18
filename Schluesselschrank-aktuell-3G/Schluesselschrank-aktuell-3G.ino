
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


   int8_t answer;
   int onModulePin = 2;
   
int button = 12;
char aux_str[30];


int pin=13;
int pin5=11;
int taster;
              int resetPin = 8;



        char pin[] = "";
        char phone_number[] = "+41796406463";   // ********* is the number to call
// char array of the message

// char remoteNumber[20]= "+41798071080"; 
char txtMsg[200]="CCS-Schluesselschrank-Test-offen";


void setup() 
{
  
            digitalWrite(resetPin, HIGH);
            delay(200);
            pinMode(resetPin, OUTPUT);
            
            
        pinMode(onModulePin, OUTPUT);
        pinMode(button, INPUT);
  
Serial.begin(9600);

            Serial.println("reset");
            delay(200);
  
 
pinMode(pin,OUTPUT);
digitalWrite(pin,HIGH);
{
   pinMode(taster, OUTPUT);
   pinMode(pin5, INPUT);
}

 pinMode(onModulePin, OUTPUT);
  pinMode(button, INPUT);


  Serial.println("Starting...");
  power_on();

  delay(3000);

  //sets the PIN code
  sprintf(aux_str, "AT+CPIN=%s", pin);
  sendATcommand(aux_str, "OK", 2000);

  delay(3000);

  Serial.println("Connecting to the network...");

  //Enables the use of command ATH
  sendATcommand("AT+CVHU=0", "OK", 10000);

  while ( (sendATcommand("AT+CREG?", "+CREG: 0,1", 500) ||
           sendATcommand("AT+CREG?", "+CREG: 0,5", 500)) == 0 );
  
  Serial.print("Calling to ");
  Serial.print(phone_number);
  Serial.println("...Press button to hang");

  
  //Make the phone call
  sprintf(aux_str, "ATD%s;", phone_number);
  sendATcommand(aux_str, "OK", 10000);

  // press the button for hang the call
  while (digitalRead(button) == 1);
  
  // disconnects the existing call
  Serial.println("ATH");            
  Serial.println("Call disconnected");

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

 oid power_on() {

  uint8_t answer = 0;

  // checks if the module is started
  answer = sendATcommand("AT", "OK", 2000);
  if (answer == 0)
  {
    // power on pulse
    digitalWrite(onModulePin, HIGH);
    delay(3000);
    digitalWrite(onModulePin, LOW);

    // waits for an answer from the module
    while (answer == 0) {   // Send AT every two seconds and wait for the answer
      answer = sendATcommand("AT", "OK", 2000);
    }
  }

}

int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout) {

  uint8_t x = 0,  answer = 0;
  char response[100];
  unsigned long previous;

  memset(response, '\0', 100);    // Initialize the string

  delay(100);

  while ( Serial.available() > 0) Serial.read();   // Clean the input buffer

  Serial.println(ATcommand);    // Send the AT command


  x = 0;
  previous = millis();

  // this loop waits for the answer
  do {
    if (Serial.available() != 0) {
      // if there are data in the UART input buffer, reads it and checks for the answer
      response[x] = Serial.read();
      x++;
      // check if the desired answer  is in the response of the module
      if (strstr(response, expected_answer) != NULL)
      {
        answer = 1;
      }
    }
    // Waits for the answer with time out
  } while ((answer == 0) && ((millis() - previous) < timeout));

  return answer;
}
 
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
 


