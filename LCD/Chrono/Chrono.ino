#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ledvie 13

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display
unsigned long t,t0=0;
byte delta=100;
int ds=0,s=0,m=0;
boolean etatledvie=LOW;
void setup()
{
  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("m:");
  lcd.setCursor(5,0);
  lcd.print("s:");
  lcd.setCursor(10,0);
  lcd.print("ds:");
  
  pinMode(ledvie, OUTPUT);
  digitalWrite(ledvie,etatledvie);
  

}

void loop()
{
  etatledvie = !etatledvie;
  digitalWrite(ledvie,etatledvie);
  
  
t=millis();

if((t-t0)>=delta)
  {
    t0=t;
    ds++;
  
    if(ds==10){
      ds=0;
      s++;
 
      if(s==60){
        s=0;
        m++;
         lcd.setCursor(2,0);
         lcd.print(m);
        }
       lcd.setCursor(7,0);
       if(s<10){ lcd.print(' '); }
       lcd.print(s); 
    }
    lcd.setCursor(13,0);
    lcd.print(ds);
    
    }
    
  
  
 
}
  
