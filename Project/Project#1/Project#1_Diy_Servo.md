## So officially starting with the first project! YAY

**For this project I needed:**
-breadboard
-female-male jumper wires
-male-male jumper wires
-motor
-optical encoder sensors
-encoder
-soldering gun
-controller (recommended Arduino, or Pico, don't know about ESP32)
-potentiometer (optional)
-H-bridge
-hot glue gun (you don't want stuff to be flying around)

## Code

Before I start I though it is good idea to go over the system of optical encoder, it is really inportant because you can control the accuracy of oprtical encoder, whole code is based on this.
Here is the sketch of basic function of step signal comming from optical qudrature encoder.
![image](https://github.com/SprinterBot/SPrinterBot-AWD-Cross_gantry-330/assets/101147725/fa994ce7-d969-4c55-b1f9-9ff525454684)
![image](https://github.com/SprinterBot/SPrinterBot-AWD-Cross_gantry-330/assets/101147725/08d2e32b-96eb-4e2d-8207-62ba59397c69)
Let's say that we will tell our controller to count (late I will talk about defining the derection) the pulses from the encoder signal. We have 4 wires from the encoder, ground, power (my encoder can do 5v max input but controller can only work with 3.3 input voltage othewise I will burn it), and two signal wires, they will carry signal to controller.

-
-
-
Sorry this is my early code and I did not include many comments but I will go over it and my results. (scroll down for explnation)

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


volatile int old_encoder_pos = 0; // old encoder position, will be used to creat "new" encoder position
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





  if (old_encoder_pos != encoder_pos){ //This code is responcible for printout ot the changing position count
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
I started the code with defineing the pins
I should include that my h-bridge has two inputs, when both inputs are HIGH or LOW, bridge does nothing, but if one of the input is HIGH and another one is LOW, motor is spins one way, change pins, the first one is now LOW and another one is now HIGH motor spins another way. For those who had not yet tasted the programing, HIGH means controller out put is high means its pin right now it giver max out put voltage, usualy 3.3v, for some controler it is 5v, HIGH and LOW can also be defines as 1 and 0.
  ```cpp
#define encoderPinA 15 //encoderA pin, (remeber our encoder is made out of two sensors)
#define encoderPinB 14 //encoderB pin
#define motorPinA 8 //my h bridge pin1
#define motorPinB 9 //my h bridge pin2
```
-
-
-
These variables will hold value, boolean (true, or, false), C++ likes to declare global varibles at first so I have to tell C++ that this are my variables and they are going to hold booleans, basicaly this is simple declareation, in decleration line you can also add valeu to the variable.
```cpp
boolean A_set = false; //This boolean with tell me if current signal that is coming from encoder A is high or low, in later fucntion we will assighn value to A_set varible, true-if sensor  signalA is high, false if not
boolean B_set = false; //Same thing here but for diffrent sensor on the encoder
```
-
-
-
Here we declare more variables, variable for encoder posistion, this variable will hold the posistion in steps from 0, so if you start moving the encoder it will start counting steps therfore we get a releative positiong, another varible called old_encoder_pos is just extra varible that will be used to update the serail output, later on this. Last one is important one, this varible will store the number stepp number the should be compared to step number of encoder varible and motor should move to position where live encoder posisition is equale to requested by user REF_posistion.
```cpp
volatile int old_encoder_pos = 0; // old encoder position, will be used to creat "new" encoder position
volatile int encoder_pos = 0; //"current" encoder position
volatile int REF_position = 10000;
```
-
-
-
Our first loop, from arduin IDE, this is called void setup loop, this loop is only run once at start, you can put anything there but it will be run only once. Usualy it is used to declare pin function like tell arduino or anyother controler if this pin is input or output?

This is more interesting, this is special function that will interrupt any controller proccese when it see the change on specified pins, so if you having a fast moving encoder and you don't want counter function to miss the step and have inaccurate posistiong this function is very usufl, basicaly this line is activated when on specified pin it see change in signal,(falling + rising = change) this means than for each black line on the encoder you get two step signals!! you get twice as many steps from encoder and it seems to be, more accurate stepping.
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
Now,interesting stuff, controlling the motor itself, this is a real lopp, it will run until you turn off the controller, it will loop infinitely, running and updating your code.  The first if statment you see here compares the two varibles encoder and old_encoder, this was initialy made to reduce number of printed values going to serial because you may have already noticed there are no delays in this loop so controller will be running this couple thousand of times per second (depends on the work to do) you don want you serial to filled with many reapaeated positions. This function cleanes up your serial and updates it only when motor has changes its position. Also, impostnat note, the Serial.println(); is empty you may think it is usles, it plays a great role in organizing the serial print, it you remove it serial will print encoder values in line not in table.

The next if statment is basicaly motor controler, when it see the error (REF - encoder_pos) is negative it spins one way, if error value is positive, motor spin another way untill reaches the zero. 
```cpp
void loop() 
{





  if (old_encoder_pos != encoder_pos){ //This code is responcible for printout ot the changing position count
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
This is the heart of the counter, without this code nothing would have worked, this code is not truly by me, I used it from optical encoder example. I will have to go deeper over this. 
So, when interrupt function that has been declared in void setup is activated input on that pin it will call the function, look at the names!
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
_
_
Here we took this from first function which for example was called by interrupt,
simple we ask controller (digitalRead will return wither HIGH or LOW) what is current pin signal is it high or low, see double equal sighn it asks wither digitalRead(encoderPinB) is qual to HIGH or not. If it is, set value to A_set true, if not, set value false. now we know something about the signal from pinA.
```cpp
A_set = digitalRead(encoderPinB) == HIGH;
```
_
_
Here this line identifies the direction of the motor, look closely at the picture. Question: When A_set is true, (sensorA signal is high) and B_set is true what is the direction, look at the pciture above, particulary on this picture what is the derection of encoder relatively to encoder strip?
In this line (this is important) **from sensorA perspective, called by encoderA signal interrupt**, when A_set is not equale to B_set +1 to the encoder position that's why encoder_pos is '+=' but when A_set is equale to B_set we will subtract 1 from encoder_pos, therfore we can count steps based on the direction.
```cpp
encoder_pos += (A_set != B_set) ? +1 : -1;
```
Here is another problem for you to solve. 
Here is another function which will be called by the interrup on encoderB or encoderB from sensorB. We check it state (HIGH or LOW)
Then we are identifying the direction and based on it we subtract or add 1 to encoder_pos. See the difference? B_set == A_set?
Why? What Happend? Hint: refer to the picture aboce again, but not look from encoderB perspective
```cpp
 B_set = digitalRead(encoderPinB) == HIGH;// B    ___|````|__       ___|````|____|````  
  encoder_pos += (B_set == A_set) ? +1 : -1;//      |````|____|            |````|____|
```
_
_
_
# Conclusion
Basicaly this is a simple close to "servo" control program that has two inputs from encoder, evaluets them, calculates steps and then reflects error to output, controlling the motor and making error to equale to 0. It would worked smoothly if not Physics... Friction... Inertia... Force...
This code was good to start with, like programming, dealing with interrupts, sensors, optical encoder, counters, h-bridge, but, the problem is that when controller see that motor is off, it will "push gas pedal on full" and eventualy overshooting the position, if controller realleases the gas pedal it doesn't mean motor stop will instantaniusly, my motor is from printer with big stator it has enough mass to spin couple times when it is off. Imagine cruse control in your car, if turn you turn it on and car computer will see that you are off my 1m/h to get to 60m/h it will acceleration motor to 7000rpm, and then when you just start to relise that something is wrong car reaches 61m/h in half a second it will push brakes on full trying to brake and "slooww down"??? Noooo... Maybe if you were first testor of first cruse control...of topic... One way or another, our code act just like this, there where PID control comes in.
Basicaly my motor was moving back and forth but and never stopping, (sometimes it did but it was cause my "briliantly enggeneraing and 3d printer part that perfectly sits on the motor and keeps encoder perfectly straingth relatively to encoder" - Friction).
