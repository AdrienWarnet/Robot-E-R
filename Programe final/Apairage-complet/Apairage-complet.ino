#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//chanel
#define chanel1 12
#define chanel2 13
#define chanel3 A2

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
lcd.print("ch1:");
lcd.setCursor(0,1);
lcd.print("ch2:");
lcd.setCursor(10,0);
lcd.print("ch3:");
}

void loop() {
t=millis();

    if((t-t0)>delta){
     int valeurChanel2=pulseIn(chanel2,HIGH);
     int valeurChanel1=pulseIn(chanel1,HIGH);
     int valeurChanel3=pulseIn(chanel3,HIGH);
     t0=t;
     lcd.setCursor(5,1);
     lcd.print(valeurChanel2);
     
     
     lcd.setCursor(5,0);
     lcd.print(valeurChanel1);
     
     lcd.setCursor(12,1);
     lcd.print(valeurChanel3);
     Serial.println(valeurChanel3);
           
    }

}
