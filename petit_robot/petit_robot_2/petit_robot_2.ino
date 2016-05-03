#include "Capteur_ultrason.h"

int dirPinDroite = 14;
int stepperPinDroite = 15;
int dirPinGauche = 19;
int stepperPinGauche = 20;
int sleepPinGauche = 16;
int sleepPinDroite = 21;
int selCotePin = 18;
int startPin = 17;

int distSeuil = 5;

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

  captGauche.set_capteur();
  captDroite.set_capteur();

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
    while ( ((captGauche.get_distance() < distSeuil) || (captDroite.get_distance() < distSeuil)) && dir) {
      digitalWrite (sleepPinGauche, LOW);
      digitalWrite (sleepPinDroite, LOW);
    }
    digitalWrite (sleepPinGauche, HIGH);
    digitalWrite (sleepPinDroite, HIGH);
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
  for (int i = 0; i < 120; i++) {
    digitalWrite(stepperPinDroite, HIGH);
    digitalWrite(stepperPinGauche, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepperPinDroite, LOW);
    digitalWrite(stepperPinGauche, LOW);
    delayMicroseconds(2000);
  }
}



