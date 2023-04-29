#include <Arduino.h>

#include <AccelStepper.h>

/*
 BreakBoard

 D10   - IN4
 D9    - IN3
 D8    - IN2
 D7    - IN1

Make sure the Breadboard pins are Firm.

All 4 PEDS are light when the Turret is rotating fast (i.e. 5 RPM)
but when rotating at 1 RPM ... you can see the sequence.


TODO ....

Set a Timer when we pass 0, and using millis - adjust the drive speed like a PEM in a decent tracker....

Good info at https://42bots.com/tutorials/28byj-48-stepper-motor-with-uln2003-driver-and-arduino-uno/

*/
#define MAX_MISALIGN 2     // Step positions in the time period
#define TIME_MONITOR 10000 // 5 Seconds
AccelStepper stepper1(AccelStepper::FULL4WIRE, 8, 10, 9, 7);
// Using Full Steps
const int stepsPerRevolution = 2038;
char msg[80];
long int ts1, ts2;
long int step_pos1, step_pos2;
float expected_steps_per_timeperiod = stepsPerRevolution / (60000.0 / (float)TIME_MONITOR);
float speed = stepsPerRevolution / 60.0;
float speed_variance = .01;

void setup()
{
  Serial.begin(9600);
  Serial.write("Setup BarnDoor V1.0\r\n");

  stepper1.setCurrentPosition(0);
  stepper1.moveTo(long(stepsPerRevolution) * (long)1024);
  stepper1.setSpeed(speed);
  stepper1.setMaxSpeed(speed);
  stepper1.setAcceleration(40.0);
  ts1 = millis();
  ts2 = ts1;
  step_pos1 = 0;
  step_pos2 = 0;
}

void loop()
{
  ts1 = millis();
  if (ts1 - ts2 > TIME_MONITOR)
  {
    // put your main code here, to run repeatedly:
    sprintf(msg, "Cur pos is %ld    dtg %ld  Spd ", stepper1.currentPosition(), stepper1.distanceToGo());
    Serial.print(msg);
    Serial.print(stepper1.speed(), 3);

    // Calculate the position
    step_pos1 = stepper1.currentPosition();
    // We now can calculate the number of steps in TIME_MONITOR milli-seconds we have accomplished
    long int distance_in_time = step_pos1 - step_pos2;
    sprintf(msg, "In Time step - we have moved %ld positions. %ld /min\r\n", distance_in_time, distance_in_time * (60000 / TIME_MONITOR));
    Serial.write(msg);

    // Only Adjust is we are more than 6 Steps out
    if (abs(distance_in_time - expected_steps_per_timeperiod) > MAX_MISALIGN)
    {
      if (distance_in_time < expected_steps_per_timeperiod)
      {
        // Need to speed up
        speed *= 1.0 + speed_variance;
        stepper1.setMaxSpeed(speed);
        stepper1.setSpeed(speed);
        speed_variance *= 0.8;
        Serial.print("Speeding Up\r\n");
      }
      else
      {
        // Need to slow down
        speed *= 1.0 - speed_variance;
        stepper1.setMaxSpeed(speed);
        stepper1.setSpeed(speed);
        speed_variance *= 0.85;
        Serial.print("Slowing Down\r\n");
      }
    }
    else
    {
      Serial.print("Within Tolerance.\r\n");
    }
    step_pos2 = step_pos1;
    ts2 = ts1;
  }

  // Move the motor one step
  stepper1.run();
}