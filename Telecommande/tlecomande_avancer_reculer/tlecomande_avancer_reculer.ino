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

//chanel
#define chanel1 12
#define chanel2 13

void cmd_motor(byte, byte, byte);

unsigned long t0,t;
int delta,vitesse;
byte correc;
byte sensD, vitesseD, sensG, vitesseG, x=0;


void setup() {

Serial.begin(9600);
pinMode (MoteurDin1,OUTPUT);   
pinMode (MoteurDin2,OUTPUT); 
pinMode (MoteurDenA,OUTPUT);  
pinMode (MoteurGin1,OUTPUT);  
pinMode (MoteurGin2,OUTPUT);   
pinMode (MoteurGenA,OUTPUT);  

delta=2000;
correc=10;

}

void loop() {
t=millis();
 if((t-t0)>delta)
 {
 int valeurChanel2=pulseIn(chanel2,HIGH);

 t0=t;
 
 if(valeurChanel2>1500){
   
  vitesse = map(valeurChanel2,0,100,1511,1030);
   sensD=Avancer;
   sensG=Avancer; 
   Serial.print(valeurChanel2);
   Serial.print("la vitesse :");
   Serial.print(vitesse);
   Serial.println("avance");
 }
 if(valeurChanel2<1500){
 vitesse = map(valeurChanel2,0,100,1511,1978); 
   sensD=Avancer;
   sensG=Avancer;
   Serial.print(valeurChanel2);
   Serial.print("la vitesse :");
   Serial.print(vitesse);
   Serial.println("recule");
 }
  }
  
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
  
  
  

