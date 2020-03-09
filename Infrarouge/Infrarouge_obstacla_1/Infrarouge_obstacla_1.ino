#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ledvie 13
#define IR A0;

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

byte correc;
byte sensD, vitesseD, sensG, vitesseG, x=0;


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
    if (distanceC<20){sensD = Stop;sensG= Stop ; vitesseD = 0; vitesseG = 0;}
    else{ sensD = Avancer;vitesseD=50;sensG = Avancer;vitesseG=50;}
}
 cmd_motor(Gauche,sensG,vitesseG);
  cmd_motor(Droit,sensD,vitesseD);
}

void cmd_motor(byte motor, byte sens, byte vitesse){
byte rapcycle;
  
  rapcycle=map(vitesse,0,100,0,255); //on map pour avoir les 12 volt en pourcentage et pouvoir gerer le rapport cycle plus clairement
  
  //choix du moteur
  if ( motor == Droit && sens == Avancer) {
    analogWrite(MoteurDenA,rapcycle);
    digitalWrite(MoteurDin1,HIGH);
    digitalWrite(MoteurDin2, LOW);
    
  }
 
if ( motor == Droit && sens == Reculer) {
    analogWrite(MoteurDenA,rapcycle);
    digitalWrite(MoteurDin1,LOW);
    digitalWrite(MoteurDin2, HIGH);
    
  }
  
  if ( motor == Droit && sens == Stop) {
     digitalWrite(MoteurDenA,LOW);
    }


     if ( motor == Gauche && sens == Avancer) {
    analogWrite(MoteurGenA,rapcycle);
    digitalWrite(MoteurGin1,HIGH);
    digitalWrite(MoteurGin2, LOW);
    
  }
 
if ( motor == Gauche && sens == Reculer) {
    analogWrite(MoteurGenA,rapcycle);
    digitalWrite(MoteurGin1,LOW);
    digitalWrite(MoteurGin2, HIGH);
    
  }
  
  if ( motor == Gauche && sens == Stop) {
     digitalWrite(MoteurGenA,LOW);
    }
}
