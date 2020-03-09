//bibli
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//def des pin 
#define Ledvie 13
#define trigD 8
#define echoD 9
#define trigG 10
#define echoG 11
#define MoteurDin1 4  //pin de commande moteur DroitIN3
#define MoteurDin2 7  //pin de commande moteur DroitIN4
#define MoteurDenA 5  //pin PWM moteur Droit
#define MoteurGin1 2  //pin de commande moteur Gauche 
#define MoteurGin2 3 //pin de commande moteur Gauche 
#define MoteurGenA 6 //pin PWM moteur Gauche

//variable de commande
#define Droit 0
#define Gauche 1
#define Avancer 1
#define Reculer 2
#define Stop 0

//def variable
unsigned long t, t0 = 0 ;
float ancienD = 0, ancienG = 0;
int delta;
byte  correc,sensD, vitesseD, sensG, vitesseG, x=0;
boolean etatLedvie = true;

//def fonction
void cmd_motor(byte, byte, byte);
int ultrason(boolean direct);

//init lcd
LiquidCrystal_I2C lcd(0x27,20,4);


void setup() { 
lcd.init();       
lcd.backlight();

lcd.print("G=");
lcd.setCursor(12,0);
lcd.print("D=");

sensG=Reculer;
sensD=Reculer;
 
pinMode(Ledvie,OUTPUT);
pinMode(trigG,OUTPUT);
pinMode(trigD,OUTPUT);
pinMode (MoteurDin1,OUTPUT);   
pinMode (MoteurDin2,OUTPUT); 
pinMode (MoteurDenA,OUTPUT);  
pinMode (MoteurGin1,OUTPUT);  
pinMode (MoteurGin2,OUTPUT);   
pinMode (MoteurGenA,OUTPUT);  

delta=1000;
correc=6;
}

void loop() {
t = millis();
  //led de vie 
etatLedvie=!etatLedvie;
digitalWrite(Ledvie, etatLedvie); 
//lecture des ultrasons
   if ((t - t0) >= 100)
   {   t0 = t;
  
  int DistanceD = ultrason(Droit);
  int DistanceG = ultrason(Gauche);
  int distanceC = Infra();
  
   if((DistanceD >= 100) || (DistanceD == 0)){ DistanceD = 99; }
   if((DistanceG >= 100) || (DistanceG == 0)){ DistanceG = 99; }
 
 if( ancienG != DistanceG){
     lcd.setCursor(2, 0);
  if(DistanceG < 10){ lcd.print(' '); }
  lcd.print(DistanceG);
   ancienG = DistanceG;
}
if(ancienD != DistanceD){
  
  lcd.setCursor(14, 0);
  if(DistanceD < 10){ lcd.print(' '); }
  lcd.print(DistanceD);
  ancienD = DistanceD;
}
  


if ((DistanceD<20) && (DistanceD<DistanceG)){
sensD=Avancer;vitesseG=25;
sensG=Avancer;vitesseD=45;
} 
else {
        if ((DistanceG<20)&&(DistanceG<DistanceD)){
        sensD=Avancer;vitesseG=45;
        sensG=Avancer;vitesseD=25;
        }
        else {
                    if ((DistanceG>=25)&& (DistanceD>=25)){
                      sensD=Avancer;vitesseG=40;
                      sensG=Avancer;vitesseD=40;
                      }
              }
     }
  cmd_motor(Gauche,sensG,vitesseG+correc);
  cmd_motor(Droit,sensD,vitesseD);  
}
}
 

//fonctions
int ultrason(boolean direct)
{ 
  byte trig, echo ;
  float distance,ancien=0;
  
  if (direct == Droit){
         trig = trigD ;
         echo = echoD;  
    }
    else 
    {
       if(direct == Gauche){
            trig = trigG;
            echo = echoG;
        } 
    }
    
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  t = pulseIn(echo, HIGH,  4250);
  
 distance = (0.034 * t)/2;
 
 if(ancien !=distance ){
     
      ancien =distance ;
   
    }
    
    
    
    return distance;
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







