#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ledvie 13
#define Ir A1

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display
#define Droit 0
#define Gauche 1
#define Avancer 1
#define Reculer 2
#define Stop 0

//def variable
#define MoteurDin1 4  //pin de commande moteur DroitIN3
#define MoteurDin2 7  //pin de commande moteur DroitIN4
#define MoteurDenA 5  //pin PWM moteur Droit
#define MoteurGin1 2  //pin de commande moteur Gauche 
#define MoteurGin2 3 //pin de commande moteur Gauche 
#define MoteurGenA 6 //pin PWM moteur Gauche

//float Infra(void);

byte correc;
byte sensD, vitesseD, sensG, vitesseG, x=0;
float volt,vlt;
int distC,distanceC;
unsigned long t0=0,t;
int value, delta=1000;
float ancienC = 0;


void setup() {
 Serial.begin(9600);
lcd.init();       
lcd.backlight();
lcd.print("C=");

}

void loop() {
  t=millis();
  if((t-t0)>delta){
t0=t;


distanceC = Infra();

//Serial.print(value); Serial.print('\t');
//Serial.print(volt); Serial.print('\t');
Serial.println(distanceC);
 
 
 if( ancienC != distanceC){
     lcd.setCursor(2, 0);
  if(distanceC < 10){ lcd.print(' '); }
  lcd.print(distanceC);
   ancienC = distanceC;
    }
  
}
}



float Infra(){
 value = analogRead(Ir);
 vlt = (value*5.0)/1023;
 distC= 27.0327*pow(vlt,-1.198567);
 return distC; 
  }

