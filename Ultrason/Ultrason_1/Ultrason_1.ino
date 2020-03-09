#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ledvie 13

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

#define TRIGGER 10
#define ECHO 11
boolean etatledvie=LOW;
unsigned long t,t0=0,temps=0;
float distanceA=0,distanceD=0;
byte delta=500;


void setup() {
  Serial.begin(9600);

pinMode(TRIGGER, OUTPUT);
lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("distance : ");
 pinMode(ledvie, OUTPUT);
  digitalWrite(ledvie,etatledvie);
  
}

void loop() {
etatledvie = !etatledvie;
digitalWrite(ledvie,etatledvie);
t=millis();

if((t-t0)>=delta){
  t0=t;
TLU();
}


}

void TLU (void){
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
