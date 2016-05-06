#include "MotorBlock.h"
#include "command.h"

extern MotorBlock M_L;
extern MotorBlock M_R;
extern int asserMode;

extern int rotDir;
extern long rotTarget;

extern int linDir;
extern long linTarget;

extern float distAtAvoid;


boolean rotCommand() {

  float dst = abs( (M_L.encoderPos + M_R.encoderPos)) / 2.0;

  if(40 < abs(rotTarget - dst)) {

    float d_rot = M_L.encoderPos - M_R.encoderPos;

    if(dst >= rotTarget * (3.0/5.0)) {
      float vit = max(rotTarget - dst, 0.0) * (5.0 / 2.0) * 0.4 / rotTarget; // Commande en trapèze FTW
      M_L.setSpeed(vit * (rotDir - d_rot/200.0));
      M_R.setSpeed(vit * (rotDir + d_rot/200.0));
    } 
    else {
      M_L.setSpeed(0.4 * (rotDir - d_rot/200.0));
      M_R.setSpeed(0.4 * (rotDir + d_rot/200.0));
    }
    return false;
  } 
  else {
    M_L.setSpeed(0);
    M_R.setSpeed(0);
    delay(100);
    
    return true;
  }

}


boolean linCommand() {
  
  float dst = abs( (M_R.encoderPos - M_L.encoderPos)) / 2.0;

  if(40 < abs(linTarget - dst)) {

    float d_lin = M_R.encoderPos + M_L.encoderPos;

    if(dst >= linTarget * (3.0/5.0)) {
      float vit = max(linTarget - dst, 0.0) * (5.0 / 2.0) * 0.6 / linTarget; // Commande en trapèze FTW
      M_L.setSpeed(-vit * (linDir + d_lin/200.0));
      M_R.setSpeed(vit * (linDir - d_lin/200.0));
    } 
    else {
      M_L.setSpeed(-0.6 * (linDir + d_lin/200.0));
      M_R.setSpeed(0.6 * (linDir - d_lin/200.0));
    }
    return false;
  } 
  else {
    M_L.setSpeed(0);
    M_R.setSpeed(0);
    delay(100);
    
    return true;
  }
}


boolean avoidCommand() {
  
  float dst = abs( (M_R.encoderPos - M_L.encoderPos)) / 2.0;

  if(dst > 50) {
    float d_lin = M_R.encoderPos + M_L.encoderPos;
    M_L.setSpeed(0.4 * linDir - d_lin/250.0);
    M_R.setSpeed(-0.4 * linDir - d_lin/250.0);
    
    return false;
  } 
  else {
    M_L.setSpeed(0);
    M_R.setSpeed(0);
    delay(100);
    
    return true;
  }
}

