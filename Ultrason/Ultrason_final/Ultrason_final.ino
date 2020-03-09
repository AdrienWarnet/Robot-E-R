#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,20,4);

#define Ledvie 13
#define trigD 8
#define echoD 9
#define trigG 10
#define echoG 11
#define gauche 1
#define droit 0


unsigned long t, t0 = 0 ;
float ancienD = 0;
float nouveauD ;
boolean etatLedvie = true;


float ultrason(boolean direct);


void setup() {
  
 lcd.init();       
 lcd.backlight();
 lcd.setCursor(12,0);
 lcd.print("G=");
 lcd.setCursor(1,0);
 lcd.print("D=");
  
 pinMode(Ledvie,OUTPUT);
 pinMode(trigG,OUTPUT);
 pinMode(trigD,OUTPUT);
// Serial.begin(9600);

}


void loop() {
  
  etatLedvie=!etatLedvie;
  digitalWrite(Ledvie, etatLedvie); 
  
  t = millis();
   if ((t - t0) >= 100)
   {   t0 = t;
  
  int DistanceD = ultrason(droit);
  int DistanceG = ultrason(gauche);
  
  if((DistanceD >= 100) || (DistanceG >= 100)){
    DistanceD = 0;
    DistanceG = 0;
    }
  
  lcd.setCursor(3, 0);
  if(DistanceD < 10){ lcd.print(' '); }
  lcd.print(DistanceD);
  
  lcd.setCursor(14, 0);
  if(DistanceG < 10){ lcd.print(' '); }
  lcd.print(DistanceG);
  }
}

float ultrason(boolean direct)
{ 
  byte trig, echo ;
  
  if (direct == droit){
         trig = trigD ;
         echo = echoD;  
    }
    else 
    {
       if(direct == gauche){
            trig = trigG;
            echo = echoG;
        } 
    }
    
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  t = pulseIn(echo, HIGH,  4250);
  
  nouveauD = (0.034 * t)/2;

  
    if(ancienD != nouveauD){
     
      ancienD = nouveauD ;
   
    }
    return nouveauD;
  }
  
