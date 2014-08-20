/*  
Joshua Vasquez
Rotary Encoder With Interrupts
Augst 19, 2014
*/


// Global Variables. 
volatile unsigned char prevState;  // to deduce rotational direction.
volatile long index = 0;    


long prev_index = 0;
long curr_index = 0;
int displacement;

// Table with interrupt numbers available at:
// http://arduino.cc/en/Reference/attachInterrupt
// interrupt pin numbers below are Leonardo-Specific.
const int int0Pin = 3; 
const int int1Pin = 2;

void setup()
{ 
  Serial.begin(57600);
  delay(3000);
  interrupts();
  
// read interrupts to deduce initial state.
  unsigned int state = (digitalRead(int1Pin) << 1) | digitalRead(int0Pin);  // verify this!
  switch (state)
  {
    case 0:
      prevState = 0;
      attachInterrupt(0,State_1 , RISING);
      attachInterrupt(1,State_3 , RISING);
      break;
    case 1:
      prevState = 1; 
      attachInterrupt(0, State_0 , FALLING);
      attachInterrupt(1, State_2 , RISING);
      break;
    case 2:
      prevState = 2;
      attachInterrupt(0, State_3 , FALLING);
      attachInterrupt(1, State_1 , FALLING);
      break;
    case 3:
      prevState = 3;
      attachInterrupt(0, State_2 , RISING);
      attachInterrupt(1, State_0 , FALLING);
      break;
  }
}

void State_0()
{ 
// detach the existing interrupts and reassign new conditions.
  detachInterrupt(0); detachInterrupt(1); 
  switch (prevState)
  {
    case 3:
      index++;
      // Clockwise = true;
      break;
    case 1:
      index--;
      // Clockwise = false;
      break;
    default:
      Serial.println("Error");
      // should never happen unless we skip indices.
  }
  prevState = 0;
  attachInterrupt(0,State_1 , RISING);
  attachInterrupt(1,State_3 , RISING);
}

void State_1()
{
  detachInterrupt(0); detachInterrupt(1);  
  switch( prevState)
  {
    case 0:
      index++;
      // Clockwise = true;
      break;
    case 2:
      index--;
      // Clockwise = false;
      break;
    default:
      Serial.println("Error");
  }
  prevState = 1;
  attachInterrupt(0, State_0 , FALLING);
  attachInterrupt(1, State_2 , RISING);

}

void State_2()
{
  detachInterrupt(0); detachInterrupt(1);  
  switch (prevState)
  {
    case 1:
      index++;
      // Clockwise = true;
      break;
    case 3:
      index--;
      // Clockwise = false;
      break;
    default:
      Serial.println("Error");
  }
  prevState = 2;
  attachInterrupt(0, State_3 , FALLING);
  attachInterrupt(1, State_1 , FALLING);

}

void State_3()
{
  detachInterrupt(0); detachInterrupt(1);  
  switch (prevState)
  {
    case 2:
      index++;
      // Clockwise = true;
      break;
    case 0:
      index--;
      // Clockwise = false;
      break;
    default:
      Serial.println("Error");  
  }
  prevState = 3;
  attachInterrupt(0, State_2 , RISING);
  attachInterrupt(1, State_0 , FALLING);
}




void loop()
{
  // Prints the index at the specified interval. 
  delay(10);
  Serial.println(index);
}

