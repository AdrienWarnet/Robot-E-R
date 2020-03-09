#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ledvie 13

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

#define IR A0;
float value,volt,distanceC;
unsigned long t0,t;
int delta;
float ancienC = 0;
void setup() {
 Serial.begin(9600);
  delta=1000;
  lcd.init();       
lcd.backlight();

lcd.print("G=");

}

void loop() {
  t=millis();
  if((t-t0)>delta){
t=t0;
 value = analogRead(A0);
 volt = (value*5.0)/1023;
Serial.print(volt);
Serial.print("  distance : ");
distanceC= 27.0327*pow(volt,-1.198567);
Serial.println(distanceC);
 if((distanceC >= 100) || (distanceC == 0)){ distanceC = 99; }
 
 if( ancienC != distanceC){
     lcd.setCursor(2, 0);
  if(distanceC < 10){ lcd.print(' '); }
  lcd.print(distanceC);
   ancienC = distanceC;
 
    }
  }
}
