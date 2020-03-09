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

void cmd_motor(byte, byte, byte);

//chanel
#define chanel1 12
#define chanel2 13

unsigned long t0,t;
int delta,vitesse,maxi,moy,mini;
byte correc1,correc2,correc3,correc;
byte sensD, vitesseD, sensG, vitesseG, x=0,CorG,CorD;
byte vitGcorrec,vitDcorrec;

void setup() {
Serial.begin(9600);
pinMode (MoteurDin1,OUTPUT);   
pinMode (MoteurDin2,OUTPUT); 
pinMode (MoteurDenA,OUTPUT);  
pinMode (MoteurGin1,OUTPUT);  
pinMode (MoteurGin2,OUTPUT);   
pinMode (MoteurGenA,OUTPUT);  
delta=500;
correc1=0;
correc2=50;
correc3=70;
maxi=2000-correc2;
mini=1000+correc3;
moy=1500-correc1;
delta=100;
correc=5;
}

void loop() {
t=millis();

    if((t-t0)>delta){
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
       sensD=Avancer;sensG=Avancer;
       vitesseG=vitesse;
       vitesseD=vitesse;
       }
       if(valeurChanel2>moy){
         vitesse = map(valeurChanel2,moy,maxi,0,100); 
         if(vitesse>=100){vitesse=100;}
          sensD=Reculer;sensG=Reculer;
          vitesseG=vitesse;
          vitesseD=vitesse;
       }
    t0=t;
    }
    
   vitGcorrec=vitesseG+correc+CorG;
   vitDcorrec=vitesseD+CorD;
if (vitGcorrec>=100){vitGcorrec=100-CorD;}
 if (vitDcorrec>=100){vitDcorrec=100-CorG;}
   
   
  cmd_motor(Gauche,sensG,vitGcorrec);
  cmd_motor(Droit,sensD, vitDcorrec);

}

void cmd_motor(byte motor, byte sens, byte vitesse){
byte rapcycle;
  rapcycle=map(vitesse,0,100,0,255); //on map pour avoir les 12 volt en pourcentage et pouvoir gerer le rapport cycle plus clairement
  
  //choix du moteur
  if ( motor == Droit && sens == Avancer) {
    analogWrite(MoteurDenA,rapcycle);
    digitalWrite(MoteurDin1,LOW);
    digitalWrite(MoteurDin2, HIGH);
    
  }
 
if ( motor == Droit && sens == Reculer) {
    analogWrite(MoteurDenA,rapcycle);
    digitalWrite(MoteurDin1,HIGH);
    digitalWrite(MoteurDin2, LOW);
    
  }
  
  if ( motor == Droit && sens == Stop) {
     digitalWrite(MoteurDenA,LOW);
    }


     if ( motor == Gauche && sens == Avancer) {
    analogWrite(MoteurGenA,rapcycle);
    digitalWrite(MoteurGin1,LOW);
    digitalWrite(MoteurGin2, HIGH);
    
  }
 
if ( motor == Gauche && sens == Reculer) {
    analogWrite(MoteurGenA,rapcycle);
    digitalWrite(MoteurGin1,HIGH);
    digitalWrite(MoteurGin2, LOW);
    
  }
  
  if ( motor == Gauche && sens == Stop) {
     digitalWrite(MoteurGenA,LOW);
    }
}
