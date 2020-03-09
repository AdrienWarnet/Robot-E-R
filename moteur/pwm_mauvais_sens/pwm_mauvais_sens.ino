

//def variable
#define MoteurDin1 2  //pin de commande moteur Droit
#define MoteurDin2 3  //pin de commande moteur Droit
#define MoteurDenA 6  //pin PWM moteur Droit
#define MoteurGin1 4  //pin de commande moteur Gauche
#define MoteurGin2 7 //pin de commande moteur Gauche
#define MoteurGenA 5 //pin PWM moteur Gauche

//variable de réglage
float correc=9.5;

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
    analogWrite(MoteurDenA,128);
    digitalWrite(MoteurDin1,LOW);
    digitalWrite(MoteurDin2, HIGH);
    analogWrite(MoteurGenA,128+correc);
    digitalWrite(MoteurGin1,LOW);
    digitalWrite(MoteurGin2, HIGH);
    delay (1000);
  }
digitalWrite(MoteurDenA,LOW);
    digitalWrite(MoteurGenA,LOW);
}
