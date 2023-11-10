# Chapter 1
## Introduction

**[Meeting goals, future projects, Ideas.]**



Final project idea. (One note simple sketches) Gives an overall idea of the project. I will go more deeply in future chapters.
![image](https://github.com/studdev101/Quality-Speed-Printing-DIY-SERVOS-/assets/101147725/0bff0d91-4913-4a3b-9a9c-68676ec6b92b)

Motor (coil)
![image](https://github.com/studdev101/Quality-Speed-Printing-DIY-SERVOS-/assets/101147725/09d390c1-aea4-49e4-b7a3-8013e31633f9)

4 Servo motors, one on each side of the printer to make it balanced, note there are no belts. Each motor will have a mount for an optical linear sensor that will tell the motor its relative position. This signal from the sensor will be sent to the custom controller drive like a micro Arduino, which will process and compare the position requested by the main controller board and the actual position of the motor, thus calculating error and processing it through the PID sub-program which will calculate Proportional Integral and Derivative Gain as output to H-Bridge using PWM signal thus controlling position and speed of the motor. In a future chapter, we will cover this more deeply.

EDIT 1:
Design of tubular motor now changed to flat linear motors due to properties of common magnet, will be explained later.


### How does the optical encoder work

The optical encoder requires two things: a strip - a long clear plastic strip with very dark lines spaced in micrometers, and an encoder - a plastic piece U-shaped between one of the halves that has infrared LED and the other half has two sensors that are spaced the way that they will give of two signals one shifted 90 degrees to another, (explained later). When the plastic strip moves between two halves relative to the position of the encoder (could be reverse, encoder moves) those dark lines are close and open the way for infrared light to reach each of the sensors on the opposite side. When there is a dark line sensor will give you 0, when there is a gap (clear space between lines) sensor will give you 1. If you graph it you will get a square wave, the faster you move the strip the thinner these squares be. For reference look at the picture below, a similar system, the circular encoder with gaps, infrared LED, and two sensors, each giving a square wave signal, you can see that the signal from one sensor is shifted 90 degrees relative to the signal from another sensor. This is important, you need two sensors to be able to identify the direction of the motor signals that will shift 90 degrees one way or another based on the direction of the strip movement.
> [!NOTE]
> 0 and 1 can be anything based on the type of the sensor, for example, an optical sensor from printing paper printers, the optical sensor will give you 0 or 3 volts based position of the strip.

> [!NOTE]
> Any driver controller should be fast enough to be able to "see" and respond quickly to the signal from the encoder. Imagine a 25-micron strip, at a speed of 1m/s, which means 40, 000 thousand lines per sec.

![Untitled](https://github.com/studdev101/Quality-Speed-Printing-DIY-SERVOS-/assets/101147725/02a652e7-dcd0-4820-95ca-9e2b80e15df0)

![HEDS-9701-E50](https://github.com/studdev101/Quality-Speed-Printing-DIY-SERVOS-/assets/101147725/28544202-92c1-4b70-86b4-051d1f4af333)
