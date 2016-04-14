#include "Capteur_ultrason.h"

int dirPinDroite = 14;
int stepperPinDroite = 15;
int dirPinGauche = 19;
int stepperPinGauche = 20;
int sleepPinGauche = 16;
int sleepPinDroite = 21;
int selCotePin = 18;
int startPin = 17;

Capteur_ultrason captGauche(2, 3);
Capteur_ultrason captDroite (4, 5);

void setup() {
  pinMode(dirPinGauche, OUTPUT);
  pinMode(stepperPinGauche, OUTPUT);
  pinMode(stepperPinDroite, OUTPUT);
  pinMode(dirPinDroite, OUTPUT);
  pinMode(sleepPinGauche, OUTPUT);
  pinMode(sleepPinDroite, OUTPUT);
  pinMode(selCotePin, INPUT);
  pinMode(startPin, INPUT);

  /*captGauche.set_capteur();
  captDroite.set_capteur();*/

  bool start = digitalRead (startPin);
  digitalWrite (sleepPinGauche, LOW);
  digitalWrite (sleepPinDroite, LOW);

  while (not start) {
    start = digitalRead (startPin);
  }

  digitalWrite (sleepPinGauche, HIGH);
  digitalWrite (sleepPinDroite, HIGH);

  int cote = digitalRead (selCotePin);
  if (cote == 0) { //cote gauche
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

  else { //cote droit
    ligneDroite(96, true);
    quartDeTour(false);
    ligneDroite(456, true);
    ligneDroiteSansCapteur(300, true);
    ligneDroiteSansCapteur(91, false);
    quartDeTour(true);
    ligneDroite(273, true);
    quartDeTour(false);
    ligneDroite(125, true);
    ligneDroiteSansCapteur(300, true);
    ligneDroiteSansCapteur(90, false);

  }
}

void loop () {
  digitalWrite (sleepPinGauche, LOW);
  digitalWrite (sleepPinDroite, LOW);
}

void ligneDroite(int nbrSteps, bool dir) { //dir=true => on avance
  digitalWrite(dirPinDroite, dir);
  digitalWrite(dirPinGauche, not dir);
  delay(50);
  for (int i = 0; i < nbrSteps; i++) {
    digitalWrite(stepperPinDroite, HIGH);
    digitalWrite(stepperPinGauche, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepperPinDroite, LOW);
    digitalWrite(stepperPinGauche, LOW);
    delayMicroseconds(1000);
    while ( (captGauche.get_distance() < 100) && (captDroite.get_distance() < 100)) {
      1 + 1;
    }
  }
}

void ligneDroiteSansCapteur(int nbrSteps, bool dir) { //dir=true => on avance
  digitalWrite(dirPinDroite, dir);
  digitalWrite(dirPinGauche, not dir);
  delay(50);
  for (int i = 0; i < nbrSteps; i++) {
    digitalWrite(stepperPinDroite, HIGH);
    digitalWrite(stepperPinGauche, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepperPinDroite, LOW);
    digitalWrite(stepperPinGauche, LOW);
    delayMicroseconds(2000);
  }
}

void quartDeTour(bool sensTrigo) {
  digitalWrite(dirPinDroite, sensTrigo);
  digitalWrite(dirPinGauche, sensTrigo);
  delay(50);
  for (int i = 0; i < 125; i++) {
    digitalWrite(stepperPinDroite, HIGH);
    digitalWrite(stepperPinGauche, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepperPinDroite, LOW);
    digitalWrite(stepperPinGauche, LOW);
    delayMicroseconds(2000);
  }
}



