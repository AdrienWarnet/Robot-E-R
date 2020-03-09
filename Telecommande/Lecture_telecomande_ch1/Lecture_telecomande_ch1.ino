//chanel
#define chanel1 12
#define chanel2 13

unsigned long t0,t;
int delta,vitesse,maxi,moy,mini;
byte correc1,correc2,correc3;

void setup() {
Serial.begin(9600);
delta=500;
correc1=30;
correc2=32;
correc3=21;
maxi=2000-correc2;
mini=1000+correc3;
moy=1500-correc1;
}

void loop() {
t=millis();

    if((t-t0)>delta){
     int valeurChanel1=pulseIn(chanel1,HIGH);
     Serial.print("valeur :"); 
     Serial.print(valeurChanel1);
       if(valeurChanel1<moy){
       vitesse = map(valeurChanel1,moy,mini,0,100);
       Serial.print("   vitesse :");
       Serial.print(vitesse);
       Serial.println("droite");
       }
       if(valeurChanel1>moy){
         vitesse = map(valeurChanel1,moy,maxi,0,100); 
          Serial.print("  la vitesse :");
          Serial.print(vitesse);
          Serial.println("  gauche");
       }
    t0=t;
    }

}
