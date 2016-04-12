#include "Capteur_ultrason.h"

int dirPinDroite = 8;
int stepperPinDroite = 9;
int dirPinGauche = 6;
int stepperPinGauche = 7;
int sleepPin = 5;
int selCotePin = 4;
int startPin = 3;

Capteur_ultrason captGauche(12, 13);
Capteur_ultrason captDroite (14, 15);

void setup() {
 pinMode(dirPinGauche, OUTPUT);
 pinMode(stepperPinGauche, OUTPUT);
 pinMode(stepperPinDroite, OUTPUT);
 pinMode(dirPinDroite, OUTPUT);
 pinMode(sleepPin, OUTPUT);
 pinMode(selDirPin, INPUT);
 pinMode(startPin, INPUT);

 captGauche.set_capteur();
 captDroite.set_capteur();

 bool start = digitalRead (startPin);
 digitalWrite (sleepPin, LOW);

 while(!start){
  start = digitalRead (startPin);
 }

 digitalWrite (sleepPin, HIGH);
 
 int cote digitalRead (selCotePin);
 if (cote == 0){ //cote gauche
  ligneDroite(96, true);
  quartDeTour(true);
  ligneDroite(456, true);
  ligneDroiteSansCapteur(300, true);
  ligneDroiteSansCapteur(91, false);
  quartDeTour(false);
  ligneDroite(273, true);
  quartDeTour(true);
  ligneDroite(125, true);
  ligneDroiteSansCapteur(300, true);
  ligneDroiteSansCapteur(90, false);
  
 }

 if (cote == 1){ //cote droit
  ligneDroite(96, true);
  quartDeTour(false);
  ligneDroite(456, true);
  ligneDroiteSansCapteur(300, true);
  ligneDroiteSansCapteur(91, false);
  quartDeTour(true);
  ligneDroite(273, false);
  quartDeTour(true);
  ligneDroite(125, true);
  ligneDroiteSansCapteur(300, true);
  ligneDroiteSansCapteur(90, false);
  
 }


 digitalWrite (sleepPin, LOW);
}


void ligneDroite(int nbrSteps, bool dir){ //dir=true => on avance
 digitalWrite(dirPinDroite,dir);
 digitalWrite(dirPinGauche, not dir);
 delay(50);
 for(int i=0;i<nbrSteps;i++){
   digitalWrite(stepperPinDroite, HIGH);
   digitalWrite(stepperPinGauche, HIGH);
   delayMicroseconds(2000);
   digitalWrite(stepperPinDroite, LOW);
   digitalWrite(stepperPinGauche, LOW);
   delayMicroseconds(1000);
   while ( (captGauche.get_distance() < 10) && (captDroite.get_distance() < 10)){
    1+1;
   }
}

void ligneDroiteSansCapteur(int nbrSteps, bool dir){ //dir=true => on avance
 digitalWrite(dirPinDroite,dir);
 digitalWrite(dirPinGauche, not dir);
 delay(50);
 for(int i=0;i<nbrSteps;i++){
   digitalWrite(stepperPinDroite, HIGH);
   digitalWrite(stepperPinGauche, HIGH);
   delayMicroseconds(2000);
   digitalWrite(stepperPinDroite, LOW);
   digitalWrite(stepperPinGauche, LOW);
   delayMicroseconds(2000);
}

void quartDeTour(bool sensTrigo){
 digitalWrite(dirPinDroite, sensTrigo);
 digitalWrite(dirPinGauche, sensTrigo);
 delay(50);
 for(int i=0; i<125; i++){
   digitalWrite(stepperPinDroite, HIGH);
   digitalWrite(stepperPinGauche, HIGH);
   delayMicroseconds(2000);
   digitalWrite(stepperPinDroite, LOW);
   digitalWrite(stepperPinGauche, LOW);
   delayMicroseconds(2000);
 }
}



