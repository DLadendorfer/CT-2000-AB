// -------------------------------------------------------------------------------
// Copyright (c) Ladendorfer Daniel.
// All Rights Reserved.  See LICENSE in the project root for license information.
// -------------------------------------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Servo.h>
#include "CT2000.h"

#define c_BAUD 9600
#define c_DELAY 10

int g_loop_c = 0;
Servo myservo1; // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
int pos1 = 90, pos2 = 60, pos3 = 130, pos4 = 0;

void f_ct2000_setup()
{
    //Serial.begin(c_BAUD);
    //Serial.println("CT2000 setup");
    myservo1.attach(A1); // attaches the servo on pin 9 to the servo object
    myservo2.attach(A0);
    myservo3.attach(8);
    myservo4.attach(9);

    myservo1.write(pos1);
    delay(1000);
    myservo2.write(pos2);
    myservo3.write(pos3);
    myservo4.write(pos4);
    delay(1500);
}
void servo_handling()
{
    // turn right
    for (pos1; pos1 > 0; pos1--)
    {
        myservo1.write(pos1);
        delay(5); // delay 5ms（used to adjust the servo speed）
    }
    delay(1000);

    // open the claw
    for (pos4; pos4 < 100; pos4++)
    {
        myservo4.write(pos4);
    }
    delay(1000);

    // right servo rotates to 100 degrees
    for (pos2; pos2 < 100; pos2++)
    {
        myservo2.write(pos2);
        delay(5);
    }
    // left servo rotates to 5 degrees
    for (pos3; pos3 < 180; pos3++)
    {
        myservo3.write(pos3);
        delay(5);
    }
    delay(1500);

    // close the claw
    for (pos4; pos4 > 0; pos4--)
    {
        myservo4.write(pos4);
    }
    delay(1000);

    // left servo rotates to100 degrees, rocker arm lifts.
    for (pos3; pos3 > 120; pos3--)
    {
        myservo3.write(pos3);
        delay(5);
    }
    delay(1000);

    // turn to left
    for (pos1; pos1 < 180; pos1++)
    {
        myservo1.write(pos1);
        delay(5);
    }
    delay(1000);

    // Lower the arm
    for (pos3; pos3 < 180; pos3++)
    {
        myservo3.write(pos3);
        delay(5);
    }
    delay(1000);

    // open the claw
    for (pos4; pos4 < 100; pos4++)
    {
        myservo4.write(pos4);
    }
    delay(1000);

    // lift up the arm
    for (pos3; pos3 > 120; pos3--)
    {
        myservo3.write(pos3);
        delay(5);
    }
    delay(1000);

    // close the claw
    for (pos4; pos4 > 0; pos4--)
    {
        myservo4.write(pos4);
    }
    delay(1000);
}

void f_ct2000_loop()
{
    Serial.print("CT-G_L: ");
    Serial.println(g_loop_c++);
    servo_handling();
    delay(c_DELAY);
}
