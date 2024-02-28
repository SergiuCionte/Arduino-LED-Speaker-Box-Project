#include "pitches.h"


int LED1 = 3;
int LED8 =  6;
int buzz = 11;
int in_p = A0;

const int ledfirst=7;
const int ledbot=8;
const int ledmid = 9;
const int ledtop = 10;
int ledState = LOW; 
int ledStateB=LOW;
int ledStateC=LOW;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;    
const int buttonPin = 4;
int buttonState = 0;
boolean outputTone = false;    
int note = 1;
long int goTime, stopTime;
int spooky[] = {
  NOTE_C6, NOTE_AS5, NOTE_C6, NOTE_G5, NOTE_DS5, NOTE_G5, NOTE_C5, 0,
  NOTE_C6, NOTE_AS5, NOTE_C6, NOTE_G5, NOTE_DS5, NOTE_G5, NOTE_C5, 0,
  NOTE_C6, NOTE_D6, NOTE_DS6, NOTE_D6, NOTE_DS6, NOTE_C6, NOTE_D6, NOTE_C6,
  NOTE_D6, NOTE_AS5, NOTE_C6, NOTE_AS5, NOTE_C6, NOTE_G5, NOTE_C6, 0,
  NOTE_C6, NOTE_AS5, NOTE_C6, NOTE_G5, NOTE_DS5, NOTE_G5, NOTE_C5, 0,
  NOTE_C6, NOTE_AS5, NOTE_C6, NOTE_G5, NOTE_DS5, NOTE_G5, NOTE_C5, 0,
  NOTE_C6, NOTE_D6, NOTE_DS6, NOTE_D6, NOTE_DS6, NOTE_C6, NOTE_D6, NOTE_C6,
  NOTE_D6, NOTE_AS5, NOTE_C6, NOTE_AS5, NOTE_C6, NOTE_G5, NOTE_C6,
};

int spookynoteDurations[] = {
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4
};


int nextTime1 = 1000 / spookynoteDurations[note] ;
int nextTime2 = nextTime1 * 1.35;

 
void setup() {
  Serial.begin(57600);
    pinMode(ledfirst, OUTPUT);
  pinMode(ledbot, OUTPUT);
  pinMode(ledtop, OUTPUT);
  pinMode(ledmid, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(8, OUTPUT);
  goTime = millis();
  stopTime = millis();
    for(int i= LED1; i <= LED8; i++)
    {
    pinMode(i, OUTPUT);

  pinMode(in_p, INPUT);
}
};

void loop() {
   
   buttonState = HIGH;   
   if (buttonState == HIGH)   {


      int val = analogRead(in_p);
  int lastLed = map(val, 0, 1023, LED1, LED8);

  for(int i = LED1; i <= lastLed; i+=1)
  {
    digitalWrite(i, HIGH);
    delay(2);
    digitalWrite(i, LOW);

  }

  
    if (millis() >= goTime) {
        tone(2, spooky[note]+val);
    ledState = HIGH;
    ledStateB = LOW;
  goTime = millis() + nextTime1;
    };
    if (millis() >= stopTime) spookyrest();

   digitalWrite(ledfirst, ledState);
     digitalWrite(ledbot, ledStateB);
    digitalWrite(ledmid, ledState);
    digitalWrite(ledtop, ledStateB);
   

  // data

Serial.println(note);
Serial.println(nextTime1);
   }
}

void spookygo() {
 
  tone(2, spooky[note]);
    ledState = HIGH;
    ledStateB = LOW;
  goTime = millis() + nextTime1;
};

void spookyrest() {
        noTone(2); 
        ledState = LOW;
        ledStateB = HIGH;
        note++;
        if (note >= (sizeof(spookynoteDurations)/2)) note = 0; // progresses the note array to move onto the next note
        stopTime = millis() + nextTime2;
        };
