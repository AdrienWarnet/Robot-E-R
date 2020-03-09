 

//def variable
#define MoteurDin1 4  //pin de commande moteur DroitIN3
#define MoteurDin2 7  //pin de commande moteur DroitIN4
#define MoteurDenA 5  //pin PWM moteur Droit
#define MoteurGin1 2  //pin de commande moteur Gauche 
#define MoteurGin2 3 //pin de commande moteur Gauche 
#define MoteurGenA 6 //pin PWM moteur Gauche

//variable de réglage
float correc=5;

void setup() {
pinMode (MoteurDin1,OUTPUT);   
pinMode (MoteurDin2,OUTPUT); 
pinMode (MoteurDenA,OUTPUT);  
pinMode (MoteurGin1,OUTPUT);  
pinMode (MoteurGin2,OUTPUT);   
pinMode (MoteurGenA,OUTPUT);   

}

void loop() {
 int x;
  while(x<4){
    x=x+1;
     digitalWrite(MoteurDenA,LOW);
    digitalWrite(MoteurGenA,LOW);
    delay (1000);
    analogWrite(MoteurDenA,128+correc);
    digitalWrite(MoteurDin1,HIGH);
    digitalWrite(MoteurDin2, LOW);
    analogWrite(MoteurGenA,128);
    digitalWrite(MoteurGin1,HIGH);
    digitalWrite(MoteurGin2, LOW);
    delay (5000);
  }
digitalWrite(MoteurDenA,LOW);
    digitalWrite(MoteurGenA,LOW);
}
