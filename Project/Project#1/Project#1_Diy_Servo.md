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


Sorry this is my early code and I did not include the comment but I will go over it and my results. (scroll down for explnation)

```cpp

/*
Defining pins, to be used as outputs or inputs
*/

#define encoderPinA 15
#define encoderPinB 14
#define motorPinA 8
#define motorPinB 9
#define REF_PSignal_IN 28


boolean A_set = false;
boolean B_set = false;

/*
Defining variables to be used
*/


volatile int old_encoder_pos = 0; // old encoder position, will be used to creat "new" encoder position
volatile int encoder_pos = 0; //"current" encoder position
volatile int REF_position;
int potent_value;




void setup() {
  pinMode(encoderPinA, INPUT); //define these pins as inputs
  pinMode(encoderPinB, INPUT); //same
  pinMode(motorPinA, OUTPUT); //motor pin
  pinMode(motorPinB, OUTPUT); //motor pin
  pinMode(REF_PSignal_IN, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), Counter_triggerA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), Counter_triggerB, CHANGE);

  Serial.begin(300);
  

}

void loop() 
{

  potent_value = analogRead(REF_PSignal_IN);

  REF_position = map(potent_value, 0, 1023, 10000, -10000);





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
 
