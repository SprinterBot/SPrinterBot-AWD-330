# Time to Learn!


## Let's build a miniature model of a servo motor with precision position feedback loop control.

**Goal**:
-Learn stuff-learn everything about servo motors in detail



## Before we actually build a servo motor
**Servo motor, hmmm what is unique about servo motor, that stepper can't do**

**What are feedback loop and open loop control**

**What is PID**

To be able to understand this let's go over everything step by step.

### DC Motor (1/10)

DC motor is one of the important things in servo motor, it converts electrical energy into mechanical energy, in our situation it will move the print head. As you might have known DC motors are made of permanent magnet stators and 3-pole winding rotors. Usually, this type of rotary motor has brushes.

(imag #1)![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/fa046804-ddf2-48c9-92bc-ffcdabd507b2)



(image #2)![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/b54d802b-f850-4a22-930c-5393a86d5ff8)


(image #3)![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/a77ea7ed-1de5-4293-9872-afaa70b6fde0)


(image #4)![Untitled-1](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/d5c66bf3-366f-4f6e-b25f-58f724e8d17e)




In the 3rd image, you can see the basic concept of a DC motor coil has a direct current flowing through it creating an electromagnetic field thus resulting in a directional force after all making the rotor spin. As you may know now magnetic field of a coil will have two poles based on the direction of the current flowing through it. In (image #4), the Right-hand rule can help us find the direction of the force in this situation, so the thumb stands for the direction of force, index direction of the current, and middle direction of the magnetic field (Magnetic field goes from the north pole to south pole). So in (image #3) the current flows clockwise over the could, and the magnetic field goes from the N magnet to the S Pole magnet, the right-hand rule tells us that in this situation  force will be directed downward where the N magnet and upward where is S magnet, creating a rotational force thus rotating the stator and anything that is connected...? But wait what if poles of the magnet match the poles of the coil? Your motor will be stalled and short-circuited (there is no more resistance therefore we let in too much current, which heats up the coil and burns). But this has been solved, (Image #1) just shows one pole while the actual, DC motor usually has 3 or more poles. Look at (Image #1). In (image #2) this is part of the motor called the rotor-it spins, it **usually** 3 pole poles, and each of these poles has shared contacts-pads on the commutator where brushes from GND and Power+ contact it. When brushes touch two of the pads electrical current starts to flow through one of three poles thus as we've already learned, a rotational force moves the stator, but when the rotor moves more than 1/3 of a turn this pole loses contact with brushes and a new pole takes its place thus making another 1/3 of a turn, afterward losing contact as previous pole did and being replaced with our last 3rd pole which completes its turn and succeeding losses contact and new poles takes its place. The motor has completed the first cycle. This type of motor can spin forever until the brushes get all used up or lose power. This is the simplest DC brushed motor. 

This is by far one of the simplest examples, DC motor seems to be simple but it is far more complex, the interaction of the magnetic field with an electromagnetic field, the position of windings, type of coil, thickness, resistance, inductance, magnets, back EMF, friction, temperature, and many other things have crucial effect on the motor performance. 

But let's get back on track, we now understand what right-hand rule and I think the left-hand rule too, two magnets on the side with different poles and coil with the flow of current that is perpendicular to the magnetic flux (now I must introduce you to new word flux, it means that only portion of the magnetic field of whole magnet interacts with electromagnetic filed of coil, this 
portion is called flux) ...we get a rotational force, one side of the coil is pulled downward another upward. In Theory think about this, as your first problem to solve using materials that you just have learned or maybe knew already. What if we leave this system the same as before but we will make the South Pole of both magnets face the coil, what will be the direction of the force?

**UPWARD**

(image#5)![image](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/f8a60269-c22c-4f5a-8a51-4a62332401e1)


We built the first DC linear motor and it is not required to have brushes so basically DC brushless motor.

Also at last, when building a DC motor there several things to consider. The max amps, mass, voltage, magnets, number of poles.
The more amps you want to draw the thicker the copper coil wire to be or increase the number of poles, more voltage more loops but increasingly more heat will be dispatched. Just a note.


### Encoder (2/10)

The encoder my the most crucial thing in the servo, it is the encoder that turns any motor into a servo motor. The encoder enables the driver controller to know its current position and speed. There are two types of encoders absolute, and relative. Basically, the absolute encoder can find its position at any time even if you power down and power up your driver controller; while the relative position encoder can only tell you the relative position like, you made a homing sequence on your 3D printer and from this point it can tell you relatively to the zero where its location but if you power down and power up the driver it will have to repeat homing sequence.

In my project I will be using the optical encoder, there are many other encoders like laser alternatives and magnetic potentiometers, but some of them are too expensive, others are not reliable, and the rest are unimaginable. An optical encoder can provide great precision without being expensive, it can be as simple as a plastic strip with dark lines and two light sensors. Or a reflective strip with sensors that will detect reflection. 

The encoder will work like an on/off switch every time a dark line passes in between the sensors, they will give 0 value in other situations 1, thus creating a square wave which can later be compared with the step wave from the controller board. (Later on this). The sensor block usually has two sensors with a small gap in between that helps it identify the direction of the motor, by comparing the signal from one sensor to another. 

**How does the optical encoder work**

The optical encoder requires two things: a strip - a long clear plastic strip with very dark lines spaced in micrometers, and an encoder - a plastic piece U-shaped between one of the halves that has infrared LED and the other half has two sensors that are spaced the way that they will give of two signals one shifted 90 degrees to another.
![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/fe858041-6624-4fa3-ace2-f5725b5e8fc8)
(relative vs absolute optical position)


![Untitled-1](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/22e805c6-6577-4869-8a15-230c08de71ad)


When the plastic strip moves between two halves of the encoder, those dark lines block and open the way for infrared light to reach each of the sensors on the opposite side. When it is blocked, the sensor gives you 0, when there is a gap (clear space between lines) sensor will give you 1. If you graph it, x-time, y-signal from the sensor, you will get a square wave, the faster you move the strip the thinner these squares(rectangles) be. For reference look at the picture below, a similar system, the circular encoder with gaps, infrared LED, and two sensors, each giving a square wave signal, you can see that the signal from one sensor is shifted 90 degrees relative to the signal from another sensor. This is very important, you need two sensors to be able to identify the direction of the motor signals that will shift 90 degrees one way or another based on the direction of the strip movement. Let's tell our controller to count the pulses from the encoder signal. We have 4 wires from the encoder, ground, power (my encoder can do 5v max input but the controller can only work with 3.3 input voltage otherwise I will burn it), and two signal wires, which will carry the signal to the controller. This way, our controller will count pulses, and based on the direction this pulse will be represented as -1 or 1, if we move the encoder for 100 pulses in one direction, the controller will have a value of 100, if move the encoder another direction but only 50 pulses, the controller will have a value of 50. This way we can find the position of the encoder relative to the starting point, it is only limited by the length of the encoder strip.

> [!NOTE]
> 0 and 1 can be anything based on the type of the sensor, for example, an optical sensor from printing paper printers, the optical sensor will give you 0 or 3 volts based position of the strip.

> [!NOTE]
> Any driver controller should be fast enough to be able to "see" and respond quickly to the signal from the encoder. Imagine a 25-micron strip, at a speed of 1m/s, which means 40, 000 thousand lines per sec. Arduino controllers are basically enough for this type of experiment but preferably get a faster controller like ESP32 as I did in later chapters.

![image](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/d226c3d4-8963-4538-99ca-1be4575d5b59)

![image](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/6262fb07-97ce-4596-a492-8ca19e2df5aa)



### PWM (3/10)

Basically, PWM is defined as Puls-Width-Modulation, if any of you played with pins on Raspberry Pi or played with Arduino you know that PWM is a signal that varies in signal widths, this signal can be used to control motors in our situation. We can control the speed of the motor by varying the signal width which is a square wave. If we are on a 100% duty cycle we have a voltage of 5v then at 50% we have a voltage of 2.5. But PWM is generated directly from the controller that can't provide high enough current and voltage, in order to do that we need a transistor that will work like a switch for higher voltage and current; usually, it is a MOSFET transistor because they are more efficient (not going into details). One transistor will be able to control the speed of the motor but only in one direction, that is why we need a H-bridge. (4 transistors

![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/17415588-b05b-4b99-89e7-27fdac115f35)



![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/f9ff46bc-c2ee-44b1-b8f5-dd042d0663f2)



### H-Bridge (4/10)

Basically, 4 transistors are positioned in a specific way: when two of them switch on the motor spins one way, and the other two transistors turn on the motor another way. This is the simplest form of this circuit. H-Bridge can be either used as one for the DC motor or it can also control the speed of the motor with PWM that comes from the main controller.
![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/c5b341e6-635b-4220-bc0a-a7c592c25e85)


### Open loop control (no feedback) (5/10)

Open loop control is where no feedback control is implemented, like an RC plane or RC car, when you move one of your control joysticks it increases the RPM of your motor without knowing its actual speed or position. We are using the same System in 3D printing, laser cutting, and sometimes even CNC, but companies are usually using servos.

![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-Cross_gantry-330/assets/101147725/9681fdd2-a6ee-497b-afe1-fde81e056963)


### Example of Open loop control (6/10)
 Stepper motor control does not require feedback, and most 3D printing systems do not implement closed-loop control. Stepper motors are made in a specific way that one rotor turn is divided into small precise steps. When the controller requests the motor to move a specific number of steps stepper motor moves precisely this number of steps.

 ![open-loop-system](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/043b8e57-cedc-4e7d-b0aa-8a1464c157de)




### Closed loop control (feedback) (7/10)

In this system for example temperature control. We have a heater cartridge that heats up the hotend, and we have a thermometer that gives its resistance data to the controller based on which the controller can calculate the actual temperature of the hotend and compare it to the requested temperature and correct the setting. But it is not easy to fix, the controller needs to know how to fix, it for accurate and fast response Closed loop control usually implements P, PI, PD, or PID control. (Later on this)
![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/1f575163-b40c-490d-8a2b-8bc76fdfa760)


### PID Loop Control (8/10)

PID is the heart of controlling the servo motor, It is some sort of software that does calculation based on the given constraints and error signal it will give a out as correction to keep for example motor from moving but staying at a certain position, PID can also be used for position loop and velocity loop, including current loop. I won't go over PID control in detail as we going to use the PID library, and how PID works is a completely different project, if you are interested there are many articles that go into detail about how PID works. I can go over it just covering basics and explaining important points. But, it does not mean I won't do it, I will go over it when we concentrate on specifically on the control of the motor next project page. But for now, remember PID is made out of 3 components. Proportional, Integral, Derivative. I won't be the best at explaining it so here are a couple of links you can use to find more about this (Recommended), I will update if I get more knowledge of this.
**Start with this:** https://www.vdwalle.com/Norte/Servo_tuning_tutorial.pdf **and**https://www.youtube.com/watch?v=JFTJ2SS4xyA
#1: https://www.parkermotion.com/manuals/6270/6270_3.pdf
#2:http://manuals.chudov.com/Servo-Tuning/Tuning-Servomotors.pdf
#3:https://www.electronicdesign.com/markets/automation/article/21261678/neuronicworks-positioning-a-linear-servo-motor-with-a-pid-controller

Check out this interactive PID contr: [ol](https://www.geogebra.org/m/tyd3f8dy)

![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/cce27701-6f65-47da-9db9-34616d81f913)


![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/eee0f436-d3e4-4bc2-8d13-9ab456e95994)


### PID Tuning (9/10)

This is a short section. This is one of the crucial things in servo control because without it the servo will be impossible to "control," when tuning PID you find values, and gains for each component of PID control, it is possible to find it using **auto PID tune** or manually, usually when servo motors are tuned professionally, they use auto PID tune and then fine-tuned to specific needs.

![Untitled-1](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/3d4b2b7e-9b27-4527-b82a-af89d8f7956f)



### Servo Motor (10/10)

There you go in theory we built a simple model of a servo motor, we got a DC motor that is being controlled by an H-bridge, and we have an encoder that will give us feedback, we got a controller with PID control that will control the DC motor. But to be able to build on our own in real-world 'real' servo we have to go over each of these things and understand them. But before we do this it is a good idea to begin with experiments and prototypes.
In the next section, we are going to use a simple DC motor with an optical encoder, h-bridge, and controller, the goal is to make a working servo motor from these things, and that is a challenge, and those who are in DIY printer building and printing world like challenges >:>.
![Untitled-1](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/75db0e01-b529-48af-9c25-373b29c99d07)

