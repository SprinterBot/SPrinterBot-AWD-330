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


In the first image, you can see the basic concept of a DC motor coil has a direct current flowing through it creating an electromagnetic field thus resulting in a directional force after all making the rotor spin. As you may know now magnetic field of a coil will have two poles based on the direction of the current flowing through it. In (image #4), the Right-hand rule can help us find the direction of the force in this situation, so the thumb stands for the direction of force, index direction of the current, and middle direction of the magnetic field (Magnetic field goes from the north pole to south pole). So in (image #1) the current flows clockwise over the could, and the magnetic field goes from the N magnet to the S Pole magnet, The right-hand rule tells us that in this situation  force will be directed downward where the N magnet and upward where is S magnet, creating a rotational force thus rotating the stator and anything that is connected...? But wait what if poles of the magnet match the poles of the coil? Your motor will be stalled and short-circuited (later on this). But this has been solved, (Image #1) just shows one pole while the actual, DC motor usually has 3 or more poles. Look at (Image #2). In (image3) This is part of the motor called the rotor-it spins, it has 3 pole poles, and each of these poles has shared contacts on the commutator where brushes from GND and Power+ contact it. When brushes touch two of the pads electrical current starts to flow through one of three poles thus as we've already learned, a rotation force moves the stator, but when the rotor moves more than 1/3 of a turn this pole loses contact with brushes and a new pole takes its place thus making another 1/3 of a turn, afterward losing contact as previous pole did and being replaced with our last 3rd pole which completes its turn and succeeding losses contact and new poles takes its place. The motor has completed the first cycle. This type of motor can spin forever until the brushes get all used up or lose power. This is the simplest DC brushed motor. 

This is by far one of the simplest examples, DC motor seems to be simple but it is far more complex, the interaction of the magnetic field with an electromagnetic field, the position of windings, type of coil, thickness, resistance, inductance, magnets, back EMF, friction, temperature, and many other things have crucial effect on the motor performance. Also as I understand back EMF is the generated voltage like in the generator that tried to counter the voltage that is getting to the coil to power the motor. correct me if I'm wrong.

But let's get back on track, we now understand what right-hand rule and I think left-hand rule too, two magnets on the side with different poles and coil with the flow of current that is perpendicular to the magnetic flux (now I must introduce you to new word flux, it means that only portion of the magnetic field of whole magnet interacts with electromagnetic filed of coil, this 
portion is called flux) ...we get a rotational force, one side of the coil is pulled downward another upward. In Theory think about this, as your first problem to solve using material that you just have learned or known. What if we leave this system the same as before but we will make the South Pole of both magnets face the coil, what will be the direction of the force?

**UP**

(image#5)![image](https://github.com/3DGuyExplorer/Quality-Speed-Printing-DIY-SERVOS-SprinterBot/assets/101147725/dcd1b432-4caa-442d-ab2d-4d6707af5167)

We built the first DC linear motor and it is not required to have brushes so basically DC brushless motor.

Also at last, when building a DC motor there several things to consider. The max amps, mass, voltage, magnets, number of poles.
More ups you want to draw thicker you want coil copper wire to be or increase the number of poles, more voltage more loops but increasingly more heat will be dispatched, less amps, I don't know how yet but less inductance the better. 
 
### Encoder (2/10)

The encoder my the most crucial thing in the servo, it is the encoder that turns any motor into a servo motor. The encoder enables the driver controller to know its current position and speed. There are two types of encoders absolute, and relative. Basically, the absolute encoder can find its position at any time even if you pored down and power up your driver controller; while the relative position encoder can only tell you the relative position like, you made a homing sequence on your 3D printer and from this point it can tell you relatively to the zero where its location, like correlation coficient how far from the given point. 

In my project I will be using the optical encoder, there are many other encoders like laser alternatives and magnetic potentiometers, but some of them are too expensive, others are not reliable, and the rest are unimaginable. An optical encoder can provide great precision without being expensive, it can be as simple as a plastic strip with dark lines and two light sensors.

