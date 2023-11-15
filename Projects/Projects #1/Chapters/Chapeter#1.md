## So officially starting with the first project! YAY

**For this project I needed:**
- breadboard
- female-male jumper wires
- male-male jumper wires
- motor
- optical encoder sensors
- encoder
- soldering gun
- controller (recommended Arduino, or Pico, don't know about ESP32)
- potentiometer (optional)
- H-bridge
- hot glue gun (you don't want stuff to be flying around)

## Code

-
-
-
Sorry this is my early code and I did not include many comments. I will review this code and my results. (scroll down for an explanation)

```cpp

/*
Defining pins, to be used as outputs or inputs
*/

#define encoderPinA 15
#define encoderPinB 14
#define motorPinA 10
#define motorPinB 11



boolean A_set = false;
boolean B_set = false;

/*
Defining variables to be used
*/


volatile int old_encoder_pos = 0; // old encoder position, will be used to create a "new" encoder position
volatile int encoder_pos = 0; //"current" encoder position
volatile int REF_position = 10000;





void setup() {
  pinMode(encoderPinA, INPUT); //define these pins as inputs
  pinMode(encoderPinB, INPUT); //same
  pinMode(motorPinA, OUTPUT); //motor pin
  pinMode(motorPinB, OUTPUT); //motor pin


  attachInterrupt(digitalPinToInterrupt(encoderPinA), Counter_triggerA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), Counter_triggerB, CHANGE);

  Serial.begin(300);
  

}

void loop() 
{





  if (old_encoder_pos != encoder_pos){ //This code is responsible for pinout of the changing position count
    Serial.print("Position in steps:");
    Serial.print(encoder_pos);
    Serial.println();
    old_encoder_pos = encoder_pos;
  }





    if(encoder_pos > REF_position){
      digitalWrite(motorPinA, HIGH);// Deactivate H bidge 
      digitalWrite(motorPinB, HIGH);
      digitalWrite(motorPinA, LOW);// CCW rotation
      digitalWrite(motorPinB, HIGH);

    }else if(encoder_pos < REF_position){
      digitalWrite(motorPinA, HIGH);// Deactivate H bidge 
      digitalWrite(motorPinB, HIGH);

      digitalWrite(motorPinA, HIGH);// CW rotation
      digitalWrite(motorPinB,LOW);
    }

}
  




void Counter_triggerA()
{
  A_set = digitalRead(encoderPinA) == HIGH; // A |````|____|            |````|____|      
  encoder_pos += (A_set != B_set) ? +1 : -1;//  ___|````|__       ___|````|____|`````
}

// Interrupt on B changing state
void Counter_triggerB() 
{
  B_set = digitalRead(encoderPinB) == HIGH;// B    ___|````|__       ___|````|____|````  
  encoder_pos += (B_set == A_set) ? +1 : -1;//      |````|____|            |````|____|  

}

```
-
-
-
I started the code by defining the pins.
I should include that my h-bridge has two inputs, when both inputs are HIGH or LOW, the h-bridge does nothing, but if one of the inputs is HIGH and another one is LOW, the motor spins one way, let's change pins, the first one is now LOW and another one is HIGH motor spins another way. For those who have not yet tasted the programming, HIGH means the controller output is high means its pin right now gives max output voltage, usually 3.3v, for some controllers it is 5v, and HIGH and LOW can also be defined as 1 and 0. 
> [!NOTE]
> #define (came from C programming language) we tell the controller that pin 15 is a value of our variable encoder pins.

  ```cpp
#define encoderPinA 15 //encoderA pin, (remember our encoder is made out of two sensors)
#define encoderPinB 14 //encoderB pin
#define motorPinA 8 //my h bridge pin1
#define motorPinB 9 //my h bridge pin2
```
-
-
-
These variables will hold value, boolean (true, or, false), C++ likes to declare global variables at first so I have to tell C++ that these are my variables and they are going to hold booleans. This is a simple declaration, also in the declaration line you can also add value to the variable, without writing any extra code, otherwise it is a null - empty variable.
```cpp
boolean A_set = false; //This boolean will tell me if a current signal that is coming from encoder A is high or low, later function we will assign value to A_set variable, true-if sensor  signalA is high, false if not
boolean B_set = false; //Same thing here but for the different sensor on the encoder
```
-
-
-
Here we declare more variables, variable for the encoder position, variable will hold the position in steps from 0, so if you start moving the encoder it will start counting steps, therefore, we get a relative position; another variable called old_encoder_pos is just extra variable that will be used to update the serial output. The last one (REF_position) is important, this variable will store the number of steps as a setpoint for the motor position. It will be compared to the live value from the encoder_pos variable and based on error we will control the direction of the motor to achieve the setpoint.
```cpp
volatile int old_encoder_pos = 0; // old encoder position, will be used to create "new" encoder position
volatile int encoder_pos = 0; //"current" encoder position
volatile int REF_position = 10000;
```
-
-
-
Our first loop, from Arduino IDE, is called the void setup loop, this loop is only run once at the start, you can put anything there but it will be run only once. Usually, it is used to declare pin functions like telling Arduino or any other controller if this pin is input or output.

The next 2 lines are more interesting, these are special functions that will interrupt any controller process when it sees the change on specified pins, so if you have a fast-moving encoder and you don't want the counter function to miss the step and have an inaccurate positioning, this function is very useful, basically, this line is activated when on the specified pin it see a change in signal,(falling + rising = change) this means that for each black line on the encoder you get two-step signals!! you get twice as many steps from the encoder and it makes the system more accurate, I don't know the precision, but it is not recommended, just use two interrupts on RISING, but in this program we will use the full potential of the encoder, late we will change it to less accurate stepping for more stable control.
```cpp
void setup() {
  pinMode(encoderPinA, INPUT); //define these pins as inputs
  pinMode(encoderPinB, INPUT); //same
  pinMode(motorPinA, OUTPUT); //motor pin, it will turn on the h-bridge
  pinMode(motorPinB, OUTPUT); //same but for pinB


  attachInterrupt(digitalPinToInterrupt(encoderPinA), Counter_triggerA, CHANGE);//InterruptA, for one pin of encoder(Really important stuff)

  attachInterrupt(digitalPinToInterrupt(encoderPinB), Counter_triggerB, CHANGE); //InterruptB, for another pin of encoder

  Serial.begin(9600); //tells serial to begin, procedure to get to using the serial
  

}
```
-
-
-
Now controlling the motors this is a real loop, it will run until you turn off the controller, and it will loop infinitely, running and updating your code.  The first statement you see here compares the two variables encoder and old_encoder, this was initially made to reduce the number of printed values going to serial because you may have already noticed there are no delays in this loop so the controller will be running this couple thousand of times per second (depends on the work it doing) you don't want you serial to junk up with repeated positions. This function cleans up your serial and updates it only when the motor has changed its position. Also, an important note, the Serial.println(); plays a great role in organizing the serial print, if you remove it serial will print encoder values in line, not in the table.

The next if statement is motor controller, when it sees the error=(REF - encoder_pos) is negative it spins one way, if the error value is positive, the motor spins another way until reaches zero. 
```cpp
void loop() 
{





  if (old_encoder_pos != encoder_pos){ //This code is responsible for pinout of the changing position count
    Serial.print("Position in steps:");
    Serial.print(encoder_pos);
    Serial.println();
    old_encoder_pos = encoder_pos;
  }





    if(encoder_pos > REF_position){
      digitalWrite(motorPinA, HIGH);// Deactivate H bidge 
      digitalWrite(motorPinB, HIGH);
      digitalWrite(motorPinA, LOW);// CCW rotation
      digitalWrite(motorPinB, HIGH);

    }else if(encoder_pos < REF_position){
      digitalWrite(motorPinA, HIGH);// Deactivate H bidge 
      digitalWrite(motorPinB, HIGH);

      digitalWrite(motorPinA, HIGH);// CW rotation
      digitalWrite(motorPinB,LOW);
    }

}
```
-
-
-
This is the heart of the counter, without this code, nothing would have worked, this code is not truly by me, I used it from an optical encoder example. I will have to go deeper into this. 
So, when the interrupt function that has been declared in void setup is activated input on that pin will call the function, look at the names!
```cpp
void Counter_triggerA()
{
  A_set = digitalRead(encoderPinA) == HIGH; // A |````|____|            |````|____|      
  encoder_pos += (A_set != B_set) ? +1 : -1;//  ___|````|__       ___|````|____|`````
}

// Interrupt on B changing state
void Counter_triggerB() 
{
  B_set = digitalRead(encoderPinB) == HIGH;// B    ___|````|__       ___|````|____|````  
  encoder_pos += (B_set == A_set) ? +1 : -1;//      |````|____|            |````|____|


}
```
-
-
Here we took this from the first function which for example was called by interrupt,
we ask the controller (digitalRead will return whether HIGH or LOW) what is current pin signal is high or low, see double equal sign it asks whether digitalRead(encoderPinB) is equal to HIGH or not. If it is, set value to A_set true, if not, set value false. now we know something about the signal from pinA.
```cpp
A_set = digitalRead(encoderPinB) == HIGH;
```
-
-
Here this line identifies the direction of the motor, look closely at the picture. Question: When A_set is true, (encoderA signal is high) and B_set is true what is the direction, look at the picture above, particularly in this picture what is the direction of the encoder relative to the encoder strip?
In this line (this is important) **from sensorA perspective, called by encoderA signal interrupt**, when A_set is not equal to B_set +1 to the encoder position that's why encoder_pos is '+=' but when A_set is equal to B_set we will subtract 1 from encoder_pos, therefore we can count steps based on the direction.
```cpp
encoder_pos += (A_set != B_set) ? +1 : -1;
```
Here is another problem for you to solve. 
Here is another function that will be called by the interrupt on encoderB or encoderB from sensorB. We check its state (HIGH or LOW)
Then we identify the direction and based on it we subtract or add 1 to encoder_pos. See the difference? B_set == A_set?
Why? What Happened? Hint: refer to the picture above again, but do now look from the encoderB perspective
```cpp
 B_set = digitalRead(encoderPinB) == HIGH;// B    ___|````|__       ___|````|____|````  
  encoder_pos += (B_set == A_set) ? +1 : -1;//      |````|____|            |````|____|
```
-
-
-
I should include that I made some changes to this code, I wanted to control the REF Position too so I connected the potentiometer and mapped its output as steps so I could control the motor position with a screwdriver.
```cpp
#define REF_PSignal_IN 28 ///new pin defined for potent
//
int potent_value; //new variable to freshly converted value from analog signal.
//
 pinMode(REF_PSignal_IN, INPUT); //setting up the pinmode
//
  potent_value = analogRead(REF_PSignal_IN);

  REF_position = map(potent_value, 0, 1023, 10000, -10000); //mapping converted value from fresh digital value to my steps, so 10000 on potent, zero in steps, 1023 on potent, -10000 in steps
```
-
-
-
# Conclusion
Basically, this is a simple close-to "servo" control program that has two inputs from the encoder, evaluates them, calculates steps, and then reflects error to output, controlling the motor and making errors equal to 0. It would worked smoothly if not Physics... Friction... Inertia... Force...
This code was good to start with, like programming, dealing with interrupts, sensors, optical encoder, counters, and h-bridge, but, the problem is that when the controller sees that the motor is off, it will "push the gas pedal on full" and eventually overshooting the position if controller releases the gas pedal it doesn't mean motor stop will instantaneously, my motor is from the printer with big stator it has enough mass to spin couple times when it is off. Imagine cruise control in your car, if you turn it on and the car computer will see that you are off by 1m/h to get to 60m/h it will accelerate the motor to 7000rpm, and then when you just start to realize that something is wrong car reaches 61m/h in half a second it will push brakes on full trying to brake and "slow down"??? No... Maybe if you were the first tester of the first cruise control...of topic... One way or another, our code acts just like this, that is where PID control comes in.
My motor was moving back and forth but never stopping, (sometimes it did but it was caused by my "brilliantly engineering and 3D printer part that perfectly sits on the motor and keeps the encoder perfectly strong relative to the encoder" - Friction).
Watch my (firstYoutubeVideo).
