#include "Capteur_ultrason.h"
#include <Servo.h>



//Declaration des pins de commande
int dirPinDroite = 14;
int stepperPinDroite = 15;
int dirPinGauche = 19;
int stepperPinGauche = 20;
int sleepPinGauche = 16;
int sleepPinDroite = 21;
int selCotePin = 18;
int startPin = 17;

int distSeuil = 10; //distance min avant l'aret de robot

//variables pour le declanchement du parasol
bool parasolFerme;
double tempsZero;

//Declaration des capteur ultrason
Capteur_ultrason captGauche(2, 3);
Capteur_ultrason captDroite (4, 5);

//Declaration du servo moteur du parasol
Servo servoParasol;

void setup() {

  //Initialisation des pins de commande du moteur
  pinMode(dirPinGauche, OUTPUT);
  pinMode(stepperPinGauche, OUTPUT);
  pinMode(stepperPinDroite, OUTPUT);
  pinMode(dirPinDroite, OUTPUT);
  pinMode(sleepPinGauche, OUTPUT);
  pinMode(sleepPinDroite, OUTPUT);

  //Initialisation des pins de selection du cote et de demarrage
  pinMode(selCotePin, INPUT);
  pinMode(startPin, INPUT);

  //Initialisation des capteurs ultrason
  captGauche.set_capteur();
  captDroite.set_capteur();

  //Attente du signal de demarrage
  bool start = digitalRead (startPin);
  digitalWrite (sleepPinGauche, LOW);
  digitalWrite (sleepPinDroite, LOW);

  while (not start) {
    start = digitalRead (startPin);
  }

  //Initialisation des variables commandant le parasol
  tempsZero = millis();
  parasolFerme = true;

  //Mise en route des moteurs
  digitalWrite (sleepPinGauche, HIGH);
  digitalWrite (sleepPinDroite, HIGH);


  //Lancement du deplacemnt pour aller fermer les portes
  int cote = digitalRead (selCotePin);
  if (cote == 0) { //cote gauche
    ligneDroite(96, true);
    quartDeTour(false);
    ligneDroite(756, false);
    ligneDroite(91, true);
    quartDeTour(true);
    ligneDroite(273, true);
    quartDeTour(false);
    ligneDroite(425, false);
    ligneDroite(90, true);

  }

  else { //cote droit
    ligneDroite(96, true);
    quartDeTour(true);
    ligneDroite(756, false);
    ligneDroite(91, true);
    quartDeTour(false);
    ligneDroite(273, true);
    quartDeTour(true);
    ligneDroite(425, false);
    ligneDroite(90, true);

  }

  //Une fois que le robot a ferme les portes on attend la fin des 90 secondes

  //On coupe les moteurs
  digitalWrite (sleepPinGauche, LOW);
  digitalWrite (sleepPinDroite, LOW);



  while (millis() - tempsZero <  90000) {
    digitalWrite (sleepPinGauche, LOW);
    digitalWrite (sleepPinDroite, LOW);
  }

  //Declaration de la pin du servo du parasol
  servoParasol.attach(7);
  ouvertureDuParasol();
}



void loop () {

}






void ligneDroite(int nbrSteps, bool dir) { //dir=true => on avance
  digitalWrite(dirPinDroite, dir);
  digitalWrite(dirPinGauche, not dir);
  delay(50);
  int stepCapt = 0;
  double decomptCapteur = millis();
  for (int i = 0; i < nbrSteps; i++) {
    digitalWrite(stepperPinDroite, HIGH);
    digitalWrite(stepperPinGauche, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepperPinDroite, LOW);
    digitalWrite(stepperPinGauche, LOW);
    delayMicroseconds(2000);

    if (millis() - decomptCapteur > 100) {
      if (dir) {
        while ((captGauche.get_distance() < 10 || captDroite.get_distance() < 10)) {
          digitalWrite (sleepPinGauche, LOW);
          digitalWrite (sleepPinDroite, LOW);
        }
      }
      decomptCapteur = millis();
    }
    digitalWrite (sleepPinGauche, HIGH);
    digitalWrite (sleepPinDroite, HIGH);
  }
}



void quartDeTour(bool sensTrigo) {
  digitalWrite(dirPinDroite, sensTrigo);
  digitalWrite(dirPinGauche, sensTrigo);
  delay(50);
  for (int i = 0; i < 120; i++) {
    digitalWrite(stepperPinDroite, HIGH);
    digitalWrite(stepperPinGauche, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepperPinDroite, LOW);
    digitalWrite(stepperPinGauche, LOW);
    delayMicroseconds(2000);
  }
}




void ouvertureDuParasol() {
  servoParasol.writeMicroseconds(800);
  delay (2000);
  servoParasol.writeMicroseconds(2400);
  delay (2000);

}


void pingUltrason() {
  if ((captGauche.get_distance() < 10 || captDroite.get_distance() < 10)) {
    while ((captGauche.get_distance() < 10 || captDroite.get_distance() < 10)) {
      digitalWrite (sleepPinGauche, LOW);
      digitalWrite (sleepPinDroite, LOW);
    }
  }
  digitalWrite (sleepPinGauche, HIGH);
  digitalWrite (sleepPinDroite, HIGH);
}

