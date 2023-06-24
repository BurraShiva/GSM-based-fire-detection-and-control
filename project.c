#include <SoftwareSerial.h>
SoftwareSerial SIM900(2, 3);
String textForSMS;

int pirsensor = 10;
int buzzer = 9;
int red = 7;
int green = 8;

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  SIM900.begin(9600); // original 19200. while enter 9600 for sim900A
  Serial.println(" logging time completed!");
  pinMode(pirsensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(buzzer, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);

  delay(100);

}

void loop() {


  if ( digitalRead(pirsensor) == LOW) //
  {
    textForSMS =  "\ ALERT!! FIRE IN THE INDUSTRY . ";

    digitalWrite(buzzer, HIGH);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("message sent.");
    delay(1000);
  }
  if ( digitalRead(pirsensor) == HIGH) //
  {
    digitalWrite(buzzer, LOW);
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    delay(500);
  }

}


void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(500);
  SIM900.println("AT + CMGS = \"+919347088923\"");  // recipient's mobile number, in international format

  delay(500);
  SIM900.println(message);                         // message to send

  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(500);
  SIM900.println();
  // give module time to send SMS

}
