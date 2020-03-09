#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//chanel
#define chanel1 12
#define chanel2 13

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display
unsigned long t0,t;
int delta,vitesse;
byte correc1,correc2;


void setup() {
Serial.begin(9600);
delta=500;
correc1=30;
correc2=32;
lcd.init();                      
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("apairage:");
lcd.setCursor(0,1);
lcd.print("valeur:");
}

void loop() {
t=millis();

    if((t-t0)>delta){
     int valeurChanel1=pulseIn(chanel1,HIGH);
     t0=t;
     vitesse = map(valeurChanel1,1500-correc1,2000-correc2,0,100);
     Serial.print("valeur :");
     Serial.print(valeurChanel1); 
     Serial.print("   vitesse :");
     Serial.println(vitesse);
     lcd.setCursor(9,1);
     lcd.print(valeurChanel1);
     if (valeurChanel1>900){
      lcd.setCursor(11,0);
      lcd.print("ok");
       
     }         
    }

}
