#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ledvie 13

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

#define TRIGGERG 10
#define ECHOG 11
#define TRIGGERD 8
#define ECHOD 9
boolean etatledvie=LOW;
unsigned long t,t0=0;
byte delta=500;
int distanceD=0,distanceG=0;



void setup() {
  Serial.begin(9600);

pinMode(TRIGGERG, OUTPUT);
pinMode(TRIGGERD, OUTPUT);
lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("G:");
  lcd.setCursor(12,0);
  lcd.print("D:");
  pinMode(ledvie, OUTPUT);
  digitalWrite(ledvie,etatledvie);
  
}

void loop() {
etatledvie = !etatledvie;
digitalWrite(ledvie,etatledvie);
t=millis();

if((t-t0)>=delta){
  t0=t;
distanceD=TLU(TRIGGERD,ECHOD);
distanceG=TLU(TRIGGERG,ECHOG);

if((distanceD >= 100) || (distanceG >= 100)){
    distanceD = 0;
    distanceG = 0;
    }
}
affich();
}

int TLU (byte TRIGGER,byte ECHO){
  unsigned long temps=0;
  int distance;
  //on créer une impulsion de 10µs sur le trigger
digitalWrite(TRIGGER,HIGH);
delayMicroseconds(10);
digitalWrite(TRIGGER , LOW);
//mesure de la distance de l'obstacle
temps = pulseIn(ECHO, HIGH,4250); 
distance = (temps*0.034)/2;

return distance;
}

void affich(void){
  int distanceDp=0,distanceGp=0;
  
  if(distanceDp!= distanceD){
  Serial.println(distanceD);
  
lcd.setCursor(14,0);

lcd.print(distanceD);
  distanceDp= distanceD;
  if(distanceGp!= distanceG){
  Serial.println(distanceG);
lcd.setCursor(2,0);
lcd.print(distanceG);
  distanceGp= distanceG;
}
}
  }
