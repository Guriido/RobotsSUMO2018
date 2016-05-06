#ifndef MotorBlock_h
#define MotorBlock_h

#define OFFSET 60
      
class MotorBlock
{
  public:
    MotorBlock(int dir,int brake,int pwm, int encoderA, int encoderB);
    void init();
    void run();
    void coderInterrupt();
    void setSpeed(double targetSpeedRequired);
    
    volatile long encoderPos;
    volatile long nbTopsDone;
    
    int pinA;
    int pinB;
    
    double currSpeed;
    double targetSpeed;
    
    float cmdDEBUG;
    
  private:
    int D;
    int B;
    int P;
};

       
#endif
