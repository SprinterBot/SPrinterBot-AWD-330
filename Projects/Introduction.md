## Introduction

**[Meeting goals, future projects, Ideas.]**



Final project idea. (Onenote basic sketches) It is a basic idea of a project. I will go more deeply in future chapters.
![image](https://github.com/studdev101/Quality-Speed-Printing-DIY-SERVOS-/assets/101147725/0bff0d91-4913-4a3b-9a9c-68676ec6b92b)

> [!NOTE]
>UPDATE: The picture represents a tubular linear DC motor, the design has been changed to a sandwich-type linear DC motor, more in Project #2.


Motor (coil)
![image](https://github.com/studdev101/Quality-Speed-Printing-DIY-SERVOS-/assets/101147725/09d390c1-aea4-49e4-b7a3-8013e31633f9)

Generally, there are 4 Servo motors, one on each side of the printer, balancing. Each motor has a mount for an optical linear sensor that will tell the controller the motor's relative position. The main controller has 4 input signals, step and dir, feedback from position, and current sensor. The controller then calculates PID values and as a result it keeps the requested position of a motor. More on this in Project #1.
