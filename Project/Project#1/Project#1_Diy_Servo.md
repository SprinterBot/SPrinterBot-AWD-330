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

### Code

Before I start I though it is good idea to go over the system of optical encoder, it is really inportant because you can control the accuracy of oprtical encoder, whole code is based on this.
Here is the sketch of basic function of step signal comming from optical qudrature encoder.
![image](https://github.com/SprinterBot/SPrinterBot-AWD-Cross_gantry-330/assets/101147725/fa994ce7-d969-4c55-b1f9-9ff525454684)
![image](https://github.com/SprinterBot/SPrinterBot-AWD-Cross_gantry-330/assets/101147725/08d2e32b-96eb-4e2d-8207-62ba59397c69)
Let's say that we will tell our controller to count (late I will talk about defining the derection) the pulses from the encoder signal. We have 4 wires from the encoder, ground, power (my encoder can do 5v max input but controller can only work with 3.3 input voltage othewise I will burn it), and two signal wires, they will carry signal to controller.


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




  I started the code with defineing the pins
  I should include that my h-bridge has two inputs, when both inputs are HIGH or LOW, bridge does nothing, but if one of the input is HIGH and another one is LOW, motor is spins one way, change pins, the first one is now LOW and another one is now HIGH motor spins another way. For those who had not yet tasted the programing, HIGH means controller out put is high means its pin right now it giver max out put voltage, usualy 3.3v, for some controler it is 5v, HIGH and LOW can also be defines as 1 and 0.
  ```cpp
#define encoderPinA 15 //encoderA pin, (remeber our encoder is made out of two sensors)
#define encoderPinB 14 //encoderB pin
#define motorPinA 8 //my h bridge pin1
#define motorPinB 9 //my h bridge pin2
```



These variables will hold value, boolean (true, or, false), C++ likes to declare global varibles at first so I have to tell C++ that this are my variables and they are going to hold booleans, basicaly this is simple declareation, in decleration line you can also add valeu to the variable.
```cpp
boolean A_set = false; //This boolean with tell me if current signal that is coming from encoder A is high or low, in later fucntion we will assighn value to A_set varible, true-if sensor  signalA is high, false if not
boolean B_set = false; //Same thing here but for diffrent sensor on the encoder
```

