// Stepper Acceleration Test
// Joshua Vasquez
// August 19, 2014

#include <math.h>

unsigned int stepperAccel = 200;    // steps per rev per rev
unsigned int totalSteps = 200;

#define FULL_STEP 0
#define HALF_STEP 4
#define QUARTER_STEP 5
#define EIGHTH_STEP 6
#define SIXTEENTH_STEP 7


/* PINOUTS */
const int MS1 = 11;
const int MS2 = 12;
const int MS3 = 13;
const int DIR = 4;
const int STEP = 5;
const int outputPins[5] = {MS1, MS2, MS3, DIR, STEP};


void setUStepFactor( unsigned int ustep)
{
  digitalWrite(MS1, (0x01 & ustep));
  digitalWrite(MS2, ((0x02 & ustep) >> 1));
  digitalWrite(MS3, ((0x04 & ustep) >> 2));
}

void step(boolean clockwise)
{
  if (clockwise)
     digitalWrite(DIR, HIGH);
     
  digitalWrite(STEP, HIGH);
  delayMicroseconds(1);
  digitalWrite(STEP, LOW);
  digitalWrite(DIR, LOW);
  delayMicroseconds(1);
}

unsigned long computeT(unsigned int x, unsigned int accel)
{
  return (unsigned long)(1000000 * sqrt( (2 * x) / ( (float)accel)));
}


void setup()
{
  Serial.begin(9600); // baud rate irrelevant for Leonardo.
  delay(3000);
  Serial.println("Hello, world!");
  
  for (int i = 0; i < 5; ++i)
    pinMode(outputPins[i], OUTPUT);
    
  setUStepFactor(FULL_STEP);
}

void loop()
{

  unsigned long delayTime = 0;
  unsigned long lastDelayTime = 0;
  unsigned int currStep = 0;
  delay(3000);
  

  while (currStep < totalSteps)
  {
    delayTime = computeT(currStep, stepperAccel);
    ++currStep;
    //Serial.println(delayTime - lastDelayTime);
    step(true);
    delayMicroseconds(delayTime - lastDelayTime);
    lastDelayTime = delayTime;
  }  
    while (currStep > 0)
  {
    --currStep;  // avoid overflow by subtracting first
    delayTime = computeT(currStep, stepperAccel);
    Serial.println(lastDelayTime - delayTime);
    step(true);
    delayMicroseconds(lastDelayTime - delayTime);
    lastDelayTime = delayTime;
  }  

/*
  for (int i = 0; i < 100; ++i)
  {
    step(true);
    delayMicroseconds(50);
  }
*/
}
