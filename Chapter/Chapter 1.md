# Chapter 1
**Introduction**
[Meeting goals, future projects, Ideas.]

Final project idea. (One note simple sketches) Gives an overall idea of the project. I will go more deeply in future chapters.
![image](https://github.com/studdev101/Quality-Speed-Printing-DIY-SERVOS-/assets/101147725/0bff0d91-4913-4a3b-9a9c-68676ec6b92b)

Motor (coil)
![image](https://github.com/studdev101/Quality-Speed-Printing-DIY-SERVOS-/assets/101147725/09d390c1-aea4-49e4-b7a3-8013e31633f9)

4 Servo motors, one on each side of the printer to make it balanced, note there are no belts. Each motor will have a mount for an optical linear sensor that will tell the motor its relative position. This signal from the sensor will be sent to the customer controller drive like a micro Arduino, which will process and compare the position requested by the main controller board and the actual position of the motor, thus calculating error and processing it through the PID sub-program which will calculate Proportional Integral and Derivative Gain as output to H-Bridge using PWM signal thus controlling potion and speed of the motor. In a future chapter, we will cover this more deeply.
