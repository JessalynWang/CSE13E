Jessalyn Wang
jwang456

Summary of lab: This lab was made to familiarize us with using the stack and passing by reference. It also allowed me learn how to use fgets, which I 
have found I prefer to scanf. We also learned good error handling and how enum works, using constants defined in an enum to characterize errors within
output. In addition, learning about pass by reference helped us also learn more about memory and pointers and the differences in syntax they cause, 
especially when using the stack.

My approach: I started the lab by doing the stack functions. They were pretty easy as I had worked with stack before. I tested each function as I wrote
it, and built my test harness simulateneously. I did the same approach for the rpn functions. The difference was that before I finished rpn evaluate I 
defined my own helper function to help determine whether or not a token was valid. Just like before, I tested as I ran and eventually finished both the
rpn_evaluate and processing_backspaces, and the test harness. Then, I moved on to lab04 main. For that one, all I had to do was convert the string from
fgets into something that would be usable by rpn_evaluate, so I called process backspaces and removed the ending newline character before I put the 
string into evaluate. I also tested to make sure the string would not accept more than 60 characters. Nothing went terribly wrong, and altogether I 
found the lab to be pretty simple. The only thing I had some trouble with was figuring out the discrepancies between the linux terminal and coolterm

Final product: As far as I have tested the lab will now run on both the linux terminal and coolterm. It tests for 7 errors: stack overflow, stack 
underflow, too many items remaining, too few items remaining, invalid token, divide by 0, and more than 60 characters. I probably spent about 6 hours
doing the lab. I disliked figuring out the coolterm errors, but everything else was nice and simple. I think it would be better if the lab was more
conceptually difficult, though I am not entirely sure how that could be done, I think it would have been cool if we somehow made the type of the stack
ambiguous, as it stands it will only take doubles, but if we did one that took chars as well, I think that could have been a good combination with 
processing backspaces (then we could push to stack when we had a character, and then pop from stack when we found a backspace, and the final string 
could be built in reverse order). All in all I thought the lab was good and had thoughtfull parts. The grading seems appropriate and discussion and 
examples helped a bunch!

Note: This lab was built to run in coolterm on CR mode in terminal (not CR + LF).
