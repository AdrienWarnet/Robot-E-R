#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ledvie 13

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display
#define Droit 0
#define Gauche 1
#define TRIGGERG 10
#define ECHOG 11
#define TRIGGERD 8
#define ECHOD 9
boolean etatledvie=LOW;
unsigned long t,t0=0,temps=0;
float distanceA=0,distanceD=0,distanceG=0,distance=0;
byte delta=500;


void setup() {
  Serial.begin(9600);


 lcd.init();       
 lcd.backlight();
 lcd.setCursor(12,0);
 lcd.print("G=");
 lcd.setCursor(1,0);
 lcd.print("D=");
 
 pinMode(TRIGGERD, OUTPUT);
 pinMode(TRIGGERG, OUTPUT);
 pinMode(ledvie, OUTPUT);
 digitalWrite(ledvie,etatledvie);
  
}

void loop() {
etatledvie = !etatledvie;
digitalWrite(ledvie,etatledvie);
t=millis();

if((t-t0)>=delta){
  t0=t;
  

distanceD=TLU(Droit);
distanceG=TLU(Gauche);
}

if(( distanceD >= 100) || (distanceG >= 100)){
    distanceD = 0;
    distanceG = 0;
    }
  
  lcd.setCursor(3, 0);
  if(distanceD < 10){ lcd.print(' '); }
  lcd.print(distanceD);
  
  lcd.setCursor(14, 0);
  if(distanceG < 10){ lcd.print(' '); }
  lcd.print(distanceG);

}

float TLU (boolean direct){
  byte TRIGGER,ECHO;
  
  if(direct=Droit)
  {
    TRIGGER=TRIGGERD;
    ECHO=ECHOD;
   }
   else if (direct=Gauche){
    TRIGGER=TRIGGERD;
    ECHO=ECHOD; 
     }
     
 //on créer une impulsion de 10µs sur le trigger
digitalWrite(TRIGGER,HIGH);
delayMicroseconds(10);
digitalWrite(TRIGGER , LOW);
//mesure de la distance de l'obstacle
temps = pulseIn(ECHO, HIGH,4250); 
distanceD = (temps*0.034)/2;
if(distanceA!= distanceD){
  Serial.println(distanceD);
lcd.setCursor(12,0);
lcd.print(distanceD);
  distanceA= distanceD;
  
  
  
}
}
