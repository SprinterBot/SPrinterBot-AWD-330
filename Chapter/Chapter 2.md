# Chapter 2

## Experimenting with PID control, motor control, relay bridge (had no h-bridge)
**Project#1**
**First Project**


Learn to control the brushed motor taken from the paper printer with stock encoder, and try to implement PID control using the main controller RPI Pico (no others currently available).

I will be using an encoder 2 inches in diameter that has 2,500 lines per revolution, precise! The motor is heavy but can be operated up to 45V, I am not really sure about the max amp power 
supply, but its max output is 500mA. I will have a closer look at this thread, https://electronics.stackexchange.com/questions/132720/how-do-i-find-the-voltage-range-for-an-unknown-dc-motor. 
CAD Files are in Project 1 under the Projects section. And encoder details more in the Projects section. https://forum.arduino.cc/t/using-a-canon-printer-incremental-encoder-datasheet/1112039/9

#1 Plan, I will make a bracket for the motor that will hold it in place, and make a part on which I will mount the encoder and put it on the motor shaft. 

![image](https://github.com/3DGuyExplorer/Quality-Speed-Printing-DIY-SERVOS-SprinterBot/assets/101147725/8c2b8acc-dcef-46aa-a910-40f5da4d80bc)


#2 After testing several times I found out that the bracket thing for the encoder disk is too flexible, when detaching from the bed plate it loses its shape quickly, and the motor shaft is not long enough to hold a thicker and rigid encoder bracket.
