#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ledvie 13

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

#define IR A0;
float value,volt,dist;
unsigned long t0,t;
int delta;
void setup() {
 Serial.begin(9600);
  delta=2000;

}

void loop() {
  t=millis();
  if((t-t0)>delta){
t=t0;
 value = analogRead(A0);
 volt = (value*5.0)/1023;
Serial.print(volt);
Serial.print("  distance : ");
dist= 27.0327*pow(volt,-1.198567);

Serial.println(dist);

  }
}
