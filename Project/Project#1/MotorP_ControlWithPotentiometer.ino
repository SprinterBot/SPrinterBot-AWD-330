/*
Defining pins, to be used as outputs or inputs
*/

#define encoderPinA 10 //your pin number
#define encoderPinB 11 //your pin number
#define motorPinA 0    //your pin number, note if your motor is going in reverse direction and never reaches it goal switch pins or reqire your motor.
#define motorPinB 1    //your pin number



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
