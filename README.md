# Speed Printing on DIY Linear Servos
Experimental project to build a 3D printer called **SprinterBot** - Speed-Printer-Bot, with a DIY Linear DC Servo Motor. I want to introduce a new type of motor to the 3D printer community, which gives more speed and provides better high accuracy over conventional stepper motors, thus better print quality.

Goal: 

-Simplicity-DC Servo simpler over 3-phase brushless based.

-Linear motor-direct controller of linear movement.

-Strong and Fast

-DIY

-Cheap

-DIY Driver controller

-Cross gantry

-Lightweight

-Driver control from Mainsail

-Ironless (no cogging) smooth operation


# Short Project Description 

To achieve these goals it was considered that the current stepper motor and relatively cheap stepper drivers are not enough or too expensive to keep pushing boundaries of Speed and Acceleration while keeping considerably low cost. High-end hobby-grade stepper motors are relatively cheap and provide a high torque/speed ratio. For example, the new LDO Naema 17 is used by Vez on Legendary Vzbot with heavy water cooling to achieve crazy speeds of 3m/s and printing speeds of 500mm/s. Alternatively, you can get some industrial servos and drivers like MirageC did, or industrial-grade steppers and drivers. And to make it clear, cheap servos and drivers will be no good; even if we could afford to buy industrial servos, community support on these things isn't great, and currently, no 3d printer firmware supports servo motors well enough.
This is why building a low-cost linear & actuator servo (DC) motor is better and as a conventional DC motor, it is simpler in design and provides a good torque and speed ratio.
You may think why linear motor? Linear motor has the advantage over conventional motors, removes the need for belts, have no more pullies, simpler design. Take a look at this article - https://www.machinedesign.com/automation-iiot/article/21836868/stepper-and-servo-motor-tradeoffs. 
I'm not the first one who thought of a linear servo motor, and built them; some German manufacturers make specialized linear servo motors but they are not popular YET. (Most of them are BLC, not DC Motors) For example, a DIY linear servo Project - https://www.instructables.com/DIY-IRONLESS-LINEAR-SERVO-MOTOR/. 
There is a company that introduced a beltless drive linear servo 3d printer as a commercial product, soon this should become a popular choice over Bambulab printers. https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwj5guuZq8aCAxUaPDQIHZLYApQQFnoECBQQAw&url=https%3A%2F%2Fwww.tomshardware.com%2Fnews%2F3d-printer-uses-magnets-to-break-speed-limits-print-at-a-table-shaking-800-mms&usg=AOvVaw3jq6ofTZzqNXgxktUmof64&opi=89978449
I welcome you to my exploration of motors, how they work, how servo works, what is PID control, and how it works. What and why cross gantry, power supplies, drivers, and many other stuff, I will not be getting too deep into engineering stuff.
Simply, Linear servos are just cool!

# Organization
# Lisense

 <p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://github.com/SprinterBot/SPrinterBot-AWD-330">SPrinterBot AWD 330</a> by <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://github.com/SprinterBot">Odysseus</a> is marked with <a href="http://creativecommons.org/publicdomain/zero/1.0?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">CC0 1.0 Universal<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/zero.svg?ref=chooser-v1"></a></p> 

 ![139769027-7267da5b-7f58-499d-96bc-e41d164a3aac](https://github.com/SprinterBot/SPrinterBot-AWD-330/assets/101147725/c01059b4-c78c-43f0-a05f-9715e42efc84)
