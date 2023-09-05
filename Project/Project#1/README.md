# Let's build a miniature model of a servo motor with precision position feedback loop control.
**Goal**:
-Learn stuff-learn everything about servo motors in detail


## Before we actually build a servo motor
**Servo motor, hmmm what is unique about servo motor, that stepper can't do**

**What are feedback loop and open loop control**

**What is PID**

To be able to understand this let's go over everything step by step.

### DC Motor (1/10)

DC motor is one of the important things in servo motor, it converts electrical energy into mechanical energy, in our situation it will move the print head. As you might have known DC motors are made of permanent magnet stators and 3-pole winding rotors. Usually, this type of rotary motor has brushes.

(imag #1)![image 1](https://github.com/3DGuyExplorer/Quality-Speed-Printing-DIY-SERVOS-SprinterBot/assets/101147725/8abed3e1-969c-48a8-8909-d6f7291a4b20)

(image #2)![image 2](https://github.com/3DGuyExplorer/Quality-Speed-Printing-DIY-SERVOS-SprinterBot/assets/101147725/56b6d6be-3e10-4862-bc40-9120db9aa9c8)
(image #3)![Untitled](https://github.com/3DGuyExplorer/Quality-Speed-Printing-DIY-SERVOS-SprinterBot/assets/101147725/c084969e-d9ec-498e-bce4-c900192b5a1e)


(image #4)![image 3](https://github.com/3DGuyExplorer/Quality-Speed-Printing-DIY-SERVOS-SprinterBot/assets/101147725/5d30c65c-2704-44c0-b790-761509a28f85)
![Untitled](https://github.com/3DGuyExplorer/Quality-Speed-Printing-DIY-SERVOS-SprinterBot/assets/101147725/f27e2075-b0cd-46f6-b493-e43c0a30fcf5)



(image #5)![image 4](https://github.com/3DGuyExplorer/Quality-Speed-Printing-DIY-SERVOS-SprinterBot/assets/101147725/e7d44aad-a858-4df5-b318-fb83bfd2b55b)


In the first image, you can see the basic concept of a DC motor coil has a direct current flowing through it creating an electromagnetic field thus resulting in a directional force after all making the rotor spin. As you may know now magnetic field of a coil will have two poles based on the direction of the current flowing through it. In (image #4), the Right-hand rule can help us find the direction of the force in this situation, so the thumb stands for the direction of force, index direction of the current, and middle direction of the magnetic field (Magnetic field goes from the north pole to south pole). So in (image #1) the current flows clockwise over the could, and the magnetic field goes from the N magnet to the S Pole magnet, the right-hand rule tells us that in this situation  force will be directed downward where the N magnet and upward where is S magnet, creating a rotational force thus rotating the stator and anything that is connected...? But wait what if poles of the magnet match the poles of the coil? Your motor will be stalled and short-circuited (later on this). But this has been solved, (Image #1) just shows one pole while the actual, DC motor usually has 3 or more poles. Look at (Image #2). In (image #3) this is part of the motor called the rotor-it spins, it has 3 pole poles, and each of these poles has shared contacts-pads on the commutator where brushes from GND and Power+ contact it. When brushes touch two of the pads electrical current starts to flow through one of three poles thus as we've already learned, a rotational force moves the stator, but when the rotor moves more than 1/3 of a turn this pole loses contact with brushes and a new pole takes its place thus making another 1/3 of a turn, afterward losing contact as previous pole did and being replaced with our last 3rd pole which completes its turn and succeeding losses contact and new poles takes its place. The motor has completed the first cycle. This type of motor can spin forever until the brushes get all used up or lose power. This is the simplest DC brushed motor. 

This is by far one of the simplest examples, DC motor seems to be simple but it is far more complex, the interaction of the magnetic field with an electromagnetic field, the position of windings, type of coil, thickness, resistance, inductance, magnets, back EMF, friction, temperature, and many other things have crucial effect on the motor performance. Also as I understand back EMF is the generated voltage like in the generator that counters the voltage that is getting to the coil to power the motor. That's why when the motor is stalled by for example holding you and of the shart and preventing it from spinning, there will be no Back EMF and thus creating a short circuit that will eventually overheat the coils and destroy its insulation-ending up with a broken motor. (Correct me if I'm wrong.)

But let's get back on track, we now understand what right-hand rule and I think the left-hand rule too, two magnets on the side with different poles and coil with the flow of current that is perpendicular to the magnetic flux (now I must introduce you to new word flux, it means that only portion of the magnetic field of whole magnet interacts with electromagnetic filed of coil, this 
portion is called flux) ...we get a rotational force, one side of the coil is pulled downward another upward. In Theory think about this, as your first problem to solve using materials that you just have learned or maybe know. What if we leave this system the same as before but we will make the South Pole of both magnets face the coil, what will be the direction of the force?

**UPWARD**

(image#5)![image](https://github.com/3DGuyExplorer/Quality-Speed-Printing-DIY-SERVOS-SprinterBot/assets/101147725/dcd1b432-4caa-442d-ab2d-4d6707af5167)

We built the first DC linear motor and it is not required to have brushes so basically DC brushless motor.

Also at last, when building a DC motor there several things to consider. The max amps, mass, voltage, magnets, number of poles.
The more amps you want to draw the thicker the copper coil wire to be or increase the number of poles, more voltage more loops but increasingly more heat will be dispatched. 

### Encoder (2/10)

The encoder my the most crucial thing in the servo, it is the encoder that turns any motor into a servo motor. The encoder enables the driver controller to know its current position and speed. There are two types of encoders absolute, and relative. Basically, the absolute encoder can find its position at any time even if you power down and power up your driver controller; while the relative position encoder can only tell you the relative position like, you made a homing sequence on your 3D printer and from this point it can tell you relatively to the zero where its location but if you power down and power up the driver it will have to repeat homing sequence.

In my project I will be using the optical encoder, there are many other encoders like laser alternatives and magnetic potentiometers, but some of them are too expensive, others are not reliable, and the rest are unimaginable. An optical encoder can provide great precision without being expensive, it can be as simple as a plastic strip with dark lines and two light sensors. Or a reflective strip with sensors that will detect reflection. 

The encoder will work like an on/off switch every time a dark line passes in between the sensors, they will give 0 value in other situations 1, thus creating a square wave which can later be compared with the step wave from the controller board. (Later on this). The sensor block usually has two sensors with a small gap in between that helps it identify the direction of the motor, by comparing the signal from one sensor to another. 

### PWM (3/10)

Basically, PWM is defined as Puls-Width-Modulation, if any of you played with pins on Raspberry Pi or played with Arduino you know that PWM is a signal that varies in signal widths, this signal can be used to control motors in our situation. We can control the speed of the motor by varying the signal width which is a square wave. If on 100% duty cycle we have a voltage of 5v then at 50% we have a voltage of 2.5. But PWM is generated directly from the controller that can't provide high enough current and voltage, in order to do that we need a transistor that will work like a switch for higher voltage and current; usually, it is a MOSFET transistor because mosfet is being controller by voltage while BJT transistor controlled by the current into the collector. That is why current amplifiers are made of BJTs and voltage amplifiers are made of MOSFETs. One transistor will be able to control the speed of the motor but only in one direction, that is why we need a H-bridge.
![Pulse-Width-Modulation](https://github.com/SprinterBot/SPrinterBot-AWD-Cross_gantry-330/assets/101147725/a90e9b6f-9b72-450b-b77b-ce823ae5dca0)

### H-Bridge (4/10)

Basically, 4 transistors are positioned in a specific way that when two of them switch on the motor speen one way other transistors turn on the motor another way. This is the simplest form of this circuit. H-Bridge can be either used as one for the DC motor or it can also control the speed of the motor with PWM that comes from the main controller.
![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-Cross_gantry-330/assets/101147725/255eecd8-d82f-45b3-a428-7c39a204d528)

### Open loop control (no feedback) (5/10)

Open loop control is where no feedback control implemented, like

### Example of Open loop control (6/10)

### Closed loop control (feedback) (7/10)

In this system for example temperature control. We have a heater cartridge that heats up the hotend, and we have a thermometer that gives its resistance data to the controller based on which the controller can calculate the actual temperature of the hotend and compare it to the requested temperature and correct the setting. But it is not easy just to fix, the controller needs to know how to fix, it for accurate and fast response Closed loop control usually implements P, PI, PD, or PID control. (Later on this)

### Servo Motor

There you go in theory we built a simple model of a servo motor, we got DC motor that is being controlled by H-bridge, and we have encoder that will give us the feedback
