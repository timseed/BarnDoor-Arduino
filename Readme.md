# BarnDoor Tracer V1.0

This is a development of my basic - "Control a Stepper" development.

# VisualStudio Code 

This is expeted for you to be using the **platformIO** externsion module.

# Libraries

There is 1 Additional library required.

    AccelStepper

# Hardware

I used an Arduino Nano - with a breadboard.
Digital PINS on the Nano used are 

  -  D7
  -  D8
  -  D9
  - D10

These pins are connected to a ULN2003 Stepper motor board.


## Arduino to ULN2003 Wiring

   - D10   - IN4
   -  D9   - IN3
   - D8    - IN2
   - D7    - IN1

# Code

The code is quite simple - it estimates the roational speed to complete 1 revolution in 1 minute, and then using a sub-sample of 10 Seconds (you can change to any value you want), if calculates the error in rotation, and adjusts the rotation speed.

That's it. 

## Caveats 

This will only work with a **28BYJ-48** Stepper Motor - as is, due to the steps per revolution will be different. However Should you get another motor with a Gearbox maybe -then adjust the value of **StepsPerRevolution** and it should work !!

I am not sure how a load will effect this motor - but as it self-adjusts maybe it will be able to cope.


## Expected Output

This is the output when monitoring the serial interface I see


```text
Setup BarnDoor V1.0
Cur pos is 327    dtg 2086585  Spd 33.967In Time step - we have moved 327 positions. 1962 /min
Speeding Up
Cur pos is 669    dtg 2086243  Spd 34.306In Time step - we have moved 342 positions. 2052 /min
Slowing Down
Cur pos is 1008    dtg 2085904  Spd 34.032In Time step - we have moved 339 positions. 2034 /min
Within Tolerance.
Cur pos is 1347    dtg 2085565  Spd 34.032In Time step - we have moved 339 positions. 2034 /min
Within Tolerance.
Cur pos is 1686    dtg 2085226  Spd 34.032In Time step - we have moved 339 positions. 2034 /min
Within Tolerance.
Cur pos is 2025    dtg 2084887  Spd 34.032In Time step - we have moved 339 positions. 2034 /min
Within Tolerance.
Cur pos is 2364    dtg 2084548  Spd 34.032In Time step - we have moved 339 positions. 2034 /min
```

