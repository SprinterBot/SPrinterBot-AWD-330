## Introduction

**[Meeting goals, future projects, Ideas.]**



Final project idea. (Onenote basic sketches) It is a basic idea of a project. I will go more deeply in future chapters.
![image](https://github.com/studdev101/Quality-Speed-Printing-DIY-SERVOS-/assets/101147725/0bff0d91-4913-4a3b-9a9c-68676ec6b92b)

> [!NOTE]
>UPDATE: The picture represents a sandwich-type linear DC motor, updated form tubular to sandwich, more in Project #2.


Motor
![Untitled](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/d6803328-60d0-4f42-a5dd-867ede59bcd6)


Generally, there are 4 Servo motors, one on each side of the printer, balancing. Each motor has a mount for an optical linear sensor that will tell the controller the motor's relative position. The main controller has 4 input signals, step and dir, feedback from position, and current sensor. The controller then calculates PID values and as a result, it keeps the requested position of a motor. More on this in Project #1.
