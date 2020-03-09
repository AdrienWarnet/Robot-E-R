#define Droit 0
#define Gauche 1
#define Avancer 1
#define Reculer 2
#define Stop 0


#define MoteurDin1 2  //pin de commande moteur Droit
#define MoteurDin2 3  //pin de commande moteur Droit
#define MoteurDenA 6  //pin PWM moteur Droit
#define MoteurGin1 4  //pin de commande moteur Gauche
#define MoteurGin2 7 //pin de commande moteur Gauche
#define MoteurGenA 5 //pin PWM moteur Gauche

void cmd_motor(byte, byte, byte);

void setup() {

Serial.begin(9600);
pinMode (MoteurDin1,OUTPUT);   
pinMode (MoteurDin2,OUTPUT); 
pinMode (MoteurDenA,OUTPUT);  
pinMode (MoteurGin1,OUTPUT);  
pinMode (MoteurGin2,OUTPUT);   
pinMode (MoteurGenA,OUTPUT);   

}

void loop() {
  cmd_motor(Gauche,Reculer,50);
  cmd_motor(Droit,Reculer,50);
  delay(1000);
  cmd_motor(Gauche,Avancer,50);
  cmd_motor(Droit,Reculer,50);
  delay(1000);
  
  }
void cmd_motor(byte motor, byte sens, byte power){
byte rapcycle;
  
  rapcycle=map(power,0,100,0,255); //on map pour avoir les 12 volt en pourcentage et pouvoir gerer le rapport cycle plus clairement
  
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
