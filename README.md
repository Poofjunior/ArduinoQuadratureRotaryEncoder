Arduino-Based Quadrature-Rotary-Encoder Decryption
==============================================

Overview
--------

  Joshua Vasquez
  May 26-28, 2012
  Rotary Encoder Example V2:
  
      This code uses the FULL capabilities of the Arduino's 
      hardware to effectively QUADRUPLE the resolution of the encoder.
      
      At the heart of the code is a finite state machine with
      four states.  Rises and Falls in the pulses on both channels
      govern which state to enter and when to increment or 
      decrement the index counter.  
      
      The Arduino's two dedicated interrupts can detect both rises
      and falls in a signal pulse.  For this reason, we can quadruple 
      the resolution by detecting the beginning and end of the
      individual slits on the encoder wheel (i.e: by detecting the 
      edges of the two channels from the quadrature encoder waveform.) 

      Note: The Arduino operates at 16 MHz.  Suppose the Optical
      Encoder rotated at 30,000 RPM, which is 500 rotations
      per second, or 2000 * 500 = 1,000,000 triggers of the interrupt 
      per second.
      
      My guess is that the Arduino can still handle this and still
      appear to function normally for some other rudimentary 
      application like printing data to the serial port.
      
      I assume this behavior because I am assuming that the ISR consumes
      less than 16 clock cycles to complete, and the Arduino is operating 
      at 16 [MHz].  Thus, the Arduino is ready to detect the next encoder
      interrupt within the next millionth of a second.

      Luckily, these encoders aren't meant to be run faster than 
      30,000 RPM.
      
      Nevertheless, the Arduino really can't do much more than read
      the encoder and Serially output the value. 
    
    
    Optical Encoder Model:
      HEDS-9140
    Encoder wheel model
      1"-500-9140-A00 REVB
      (500 CPR, counts per revolution)
    Settings:
      Channels A and B are pulled up to Vcc with 2.7[kOhm] resistors.
   

    Note the pinouts to the Encoder: they're different from before!!
    Connecting Elements: 
     Encoder:            Arduino:  
      Channel A            Digital pin 2 ---> interrupt 0
      Channel B            Digital pin 3 ---> interrupt 1  


      
