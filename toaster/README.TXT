Jessalyn Wang

Summary of lab: This lab we explored furhter into programming state machines, and programmed a simple toaster. We used
the state machine as a part of learning how to program reactive systems. It also gave insight on how the common finite
state machines operate. We also learned about event driving programming as in the previous lab, though this time a lot
of the events were decided with respect to the duration of a button press, rather than detecting whether or not it had
been pressed at all. I thought the most important part was learning event driving programming and learning how to follow
a diagram for a state machine.

Process: In the beginning I followed the process precisely to the lab and got a basic OLED output working. Then, I kind
of played by ear and did whatever I felt was easiest to accomplish and went from there. I did the extra credit and the
LED bar last, as I was confused how I would implement the progress bar for a cook time of one sec, as given that only
five ticks happen in a second, it is virtually impossible to turn off all eight lights unless a new ISR is defined or
multiple lights are turned off at once. I eventually settled for turning off a light each tick, and then the last three
lights off all at once, as I was not sure we would be allowed to define a new ISR just for the progress bar. Other than
the LED display, I had no trouble with the rest of the lab. It was pretty easy to accomplish and because there was no
learning curve as we used buttons and OLED and LEDs in Lab 6, it felt easier than that lab. If I were to do the lab
again, I would follow the same approach.

I think my lab ended up good. I tried to make it as close to the output as possible, I should note that for me, a long
press is defined as one second or greater, not greater than one second, because a short press was defined as less than a
second and I did not want to also define a long press as greater than a second because then a press of exactly one 
second would accomplish nothing. The lab manual was very thorough this lab and I felt no need to go to section because 
of that fact. It was a lot of fun, and I have no suggestions of altering it other than that it would be amazing if
somehow we were able to do a bit more programming, connect the microcontroller to working parts to see the toaster in
action.

Extra credit state: I defined the extra credit state as follows. Once cooking ends successfully, we enter the extra
credit state. Once in the extra credit state, if the flag is false we output an inverted OLED, and if it is true we 
output a normal OLED, creating a flashing effect. Since button press duration does not seem to matter here, I simply 
look for a release of button for since pressing it down does not matter. Once a release of button 4 has happened 
(aka button_event_4up), we stop flashing and revert to the SETUP state.
