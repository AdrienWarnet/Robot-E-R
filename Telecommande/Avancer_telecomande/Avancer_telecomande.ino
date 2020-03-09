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
byte sensD, vitesseD, sensG, vitesseG, x=0;

void setup() {
Serial.begin(9600);
pinMode (MoteurDin1,OUTPUT);   
pinMode (MoteurDin2,OUTPUT); 
pinMode (MoteurDenA,OUTPUT);  
pinMode (MoteurGin1,OUTPUT);  
pinMode (MoteurGin2,OUTPUT);   
pinMode (MoteurGenA,OUTPUT);  
delta=500;
correc1=30;
correc2=32;
correc3=21;
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
     Serial.print("valeur :"); 
     Serial.print(valeurChanel2);
       if(valeurChanel2<moy){
       vitesse = map(valeurChanel2,moy,mini,0,100);
       Serial.print("   vitesse :");
       Serial.print(vitesse);
       Serial.println("avance");
       sensD=Avancer;sensG=Avancer;
       vitesseG=vitesseD=vitesse;
       }
       if(valeurChanel2>moy){
         vitesse = map(valeurChanel2,moy,maxi,0,100); 
          Serial.print("  la vitesse :");
          Serial.print(vitesse);
          Serial.println("  recule");
          sensD=Reculer;sensG=Reculer;
          vitesseG=vitesseD=vitesse;
       }
    t0=t;
    }
  cmd_motor(Gauche,sensG,vitesseG+correc);
  cmd_motor(Droit,sensD,vitesseD);

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
