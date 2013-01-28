/*  
Joshua Vasquez
Rotary Encoder With Interrupts
May 26 to 28, 2012
*/


// Global Variables. 
byte Values;
byte prev_state = 1;  // to deduce rotational direction.
long index = 0;    
boolean Clockwise = true;  // currently not used.
int print_time = 100;  // time between prints to the screen in [ms].
unsigned long past_time;


long prev_index = 0;
long curr_index = 0;
int displacement;

//To output the (int)displacement to the serial line byte by byte.
byte MSB;
byte LSB;


void setup()
{ 
  Serial.begin(57600);
  Serial.flush();
  Serial.print("\r I'm ready for action! \r");
  delay(100);
  
// do nothing until we enter State_1 (Pins 2 and 3 both low).      Naturally, there's a better way to enter the FSM in any state by reading the ports, but this will do for now.
// Then attach default interrupts.
  while( (Values = PIND & B00001100) != B00000000 );
  attachInterrupt(0,State_2 , RISING);
  attachInterrupt(1,State_4 , RISING);
//
past_time = millis();
}

void State_1()
{ 
  switch (prev_state)
  {
    case 2:
      index++;
      // Clockwise = true;
      prev_state = 1;
      break;
    case 4:
      index--;
      // Clockwise = false;
      prev_state = 1;
      break;
    default:
      Serial.println("Error");
      // should never happen unless we skip indices.
  }
  // detach the existing interrupts and reassign new conditions.
  detachInterrupt(0); detachInterrupt(1); 
  attachInterrupt(0, State_2, RISING);
  attachInterrupt(1, State_4, RISING);
}

void State_2()
{
  switch( prev_state)
  {
    case 1:
      index++;
      // Clockwise = true;
      prev_state = 2;
      break;
    case 3:
      index--;
      // Clockwise = false;
      prev_state = 2;
      break;
    default:
      Serial.println("Error");
  }
  detachInterrupt(0); detachInterrupt(1);  
  attachInterrupt(0, State_1, FALLING);
  attachInterrupt(1, State_3, RISING);

}

void State_3()
{
  switch (prev_state)
  {
    case 2:
      index++;
      // Clockwise = true;
      prev_state = 3;
      break;
    case 4:
      index--;
      // Clockwise = false;
      prev_state = 3;
      break;
    default:
      Serial.println("Error");
  }
  detachInterrupt(0); detachInterrupt(1);  
  attachInterrupt(0, State_4, FALLING);
  attachInterrupt(1, State_2, FALLING);

}

void State_4()
{
  switch (prev_state)
  {
    case 3:
      index++;
      // Clockwise = true;
      prev_state = 4;
      break;
    case 1:
      index--;
      // Clockwise = false;
      prev_state = 4;
      break;
    default:
      Serial.println("Error");  
  }
  detachInterrupt(0); detachInterrupt(1);  
  attachInterrupt(0, State_3, RISING);
  attachInterrupt(1, State_1, FALLING);
}

void loop()
{
  // Prints the index at the specified interval. 
  if (millis() >= (past_time + print_time) )
  // we can't say "==" because the loop might not fall on that precise moment.
  {
    past_time = millis();
    // print current displacement
    displacement = (int)index;
    
    // Two output options: binary and ascii
    
    // Here's ASCII
    Serial.println(displacement); 
    
    /* // Here's Binary
    // displacement is two bytes large.  Send both accross the serial.
    MSB = (displacement >> 8) & 0xff; // grab the MSB
    LSB = (displacement & 0xff);      // grab te LSB
    Serial.write(MSB);
    Serial.write(LSB);
    */

    /*
    Note: this code can only handle displacements within 
          the range of an int.  If we want to increase the range of 
          displacements that we want to observe, we need to 
          make displacement a 4-byte long intead and Serial.write 
          all four bytes over.  Right now, the code should handle 
          about 32.768/4 rotations.  Furthermore, we could just have
          the Arduino serially print the difference between the last
          two times it send over the data, which would be the difference
          in displacement, rather than the displacement.
    */
  }

}
