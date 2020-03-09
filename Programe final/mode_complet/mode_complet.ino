//bibli
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//variable de commande
#define Droit 0
#define Gauche 1
#define Avancer 1
#define Reculer 2
#define Stop 0

//def des pin 
#define Ir A1
#define Ledvie A0
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

//chanel
#define chanel1 12
#define chanel2 13
#define chanel3 A2

//def fonction
void cmd_motor(byte, byte, byte);
int ultrason(boolean direct);
float Infra(void);

//def variable
unsigned long t, t0 = 0 ;
int delta,distC,distanceC,vitesse,maxi,moy,mini;
float ancienD = 0, ancienG = 0, ancienC = 0, value=0,volt=0,vlt;
byte  correc,sensD, vitesseD, sensG, vitesseG, x=0,CorG,CorD,correc1,correc2,correc3,vitGcorrec,vitDcorrec;

//init lcd
LiquidCrystal_I2C lcd(0x27,20,4);

boolean etatLedvie = true;

void setup() {
  //affichage
Serial.begin(9600);
lcd.init();       
lcd.backlight();
Serial.begin(9600);
lcd.print("G=");
lcd.setCursor(12,0);
lcd.print("D=");
lcd.setCursor(7,1);
lcd.print("C=");
//utl
pinMode(trigG,OUTPUT);
pinMode(trigD,OUTPUT);
//mot
pinMode (MoteurDin1,OUTPUT);   
pinMode (MoteurDin2,OUTPUT); 
pinMode (MoteurDenA,OUTPUT);  
pinMode (MoteurGin1,OUTPUT);  
pinMode (MoteurGin2,OUTPUT);   
pinMode (MoteurGenA,OUTPUT);  
correc1=0;
correc2=50;
correc3=70;
maxi=2000-correc2;
mini=1000+correc3;
moy=1500-correc1;
delta=300;
correc=5;

}

void loop() {
t=millis();
 //led de vie 
etatLedvie=!etatLedvie;
digitalWrite(Ledvie, etatLedvie); 

  if((t-t0)>delta){
     t0=t;
      int valeurChanel3=pulseIn(chanel3,HIGH);
      if(valeurChanel3<1500){
        int valeurChanel2=pulseIn(chanel2,HIGH);
     int valeurChanel1=pulseIn(chanel1,HIGH);
     
     if(valeurChanel1>moy){
         CorD = map(valeurChanel1,moy,maxi,0,20); 
         
       }
       
       if(valeurChanel1<moy){
         CorG = map(valeurChanel1,moy,mini,0,20); 
         
       }
         
       if(valeurChanel2<moy){
       vitesse = map(valeurChanel2,moy,mini,0,100);
       if(vitesse>=100){vitesse=100;}
       sensD=Reculer;sensG=Reculer;
       vitesseG=vitesse;
       vitesseD=vitesse;
       }
       if(valeurChanel2>moy){
         vitesse = map(valeurChanel2,moy,maxi,0,100); 
         if(vitesse>=100){vitesse=100;}
          sensD=Avancer;sensG=Avancer;
          vitesseG=vitesse;
          vitesseD=vitesse;
       }
   
    
    
   vitGcorrec=vitesseG+correc+CorG;
   vitDcorrec=vitesseD+CorD;
if (vitGcorrec>=100){vitGcorrec=100-CorD;}
 if (vitDcorrec>=100){vitDcorrec=100-CorG;}
   
   
  cmd_motor(Gauche,sensG,vitGcorrec);
  cmd_motor(Droit,sensD, vitDcorrec);

}
else {
  int DistanceD = ultrason(Droit);
  int DistanceG = ultrason(Gauche);
      distanceC = Infra();
  
   if((DistanceD >= 100) || (DistanceD == 0)){ DistanceD = 99; }
   if((DistanceG >= 100) || (DistanceG == 0)){ DistanceG = 99; }
if(distanceC >= 100){ distanceC = 99; }
 
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

Serial.println(distanceC);
 if( ancienC != distanceC){
     lcd.setCursor(9, 1);
  if(distanceC < 10){ lcd.print(' '); }
  lcd.print(distanceC);
   ancienC = distanceC;
    }
    


if ((DistanceD<25) && (DistanceD<DistanceG)){
sensD=Avancer;vitesseG=15;
sensG=Avancer;vitesseD=30;
} 
else {
        if ((DistanceG<25)&&(DistanceG<DistanceD)){
        sensD=Avancer;vitesseG=30;
        sensG=Avancer;vitesseD=15;
        }
        else {
                    if ((DistanceG>=30)&& (DistanceD>=30)){
                      sensD=Avancer;vitesseG=36;
                      sensG=Avancer;vitesseD=36;
                      }
              }
     }  
     
     if ((distanceC<20)&&(distanceC>15)){
     vitesseG=vitesseG-5;
     vitesseD=vitesseD-5;  
     }
     
     else{
  
       if((distanceC<15)&&(distanceC>10)){
         vitesseG=vitesseG-10;
         vitesseD=vitesseD-10; 
       }
     else{  
     if((distanceC<10)&&(distanceC>1)){
       sensD=Reculer;vitesseG=60;
       sensG=Reculer;vitesseD=60;
         }
        } 
     }  
       
  cmd_motor(Gauche,sensG,vitesseG);
  cmd_motor(Droit,sensD,vitesseD+correc);  
}
        
      }
  
  }





//fonction
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

float Infra(){
 value = analogRead(Ir);
 vlt = (value*5.0)/1023;
 distC= 27.0327*pow(vlt,-1.198567);
 return distC; 
  }





