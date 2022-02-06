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
#define INIT_POS_SERVO_BASE 90   // degrees
#define INIT_POS_SERVO_LEFT 60   // degrees
#define INIT_POS_SERVO_RIGHT 130 // degrees
#define INIT_POS_SERVO_ARM 0     // degrees

int g_loop_c = 0;
Servo servo_base;
Servo servo_left;
Servo servo_right;
Servo servo_arm;
int pos_base = INIT_POS_SERVO_BASE;
int pos_left = INIT_POS_SERVO_LEFT;
int pos_right = INIT_POS_SERVO_RIGHT;
int pos_arm = INIT_POS_SERVO_ARM;

const int right_X = A2;  // define the right X pin to A2
const int right_Y = A5;  //define the right Y pin to A5
const int right_key = 7; // define the right key to 7(the value of Z axis)
const int left_X = A3;   // define the left X pin to A3
const int left_Y = A4;   // define the left Y pin to A4
const int left_key = 6;  // define the left key to 6(the value of Z axis)

int x1, y1, z1; //define a variable to store the read Joystick value
int x2, y2, z2;

void f_ct2000_setup()
{
    Serial.begin(c_BAUD);
    Serial.println("CT2000 setup");
    servo_base.write(pos_base);
    delay(1000);
    servo_left.write(pos_left);
    servo_right.write(pos_right);
    delay(1500);

    pinMode(right_key, INPUT); // set the right/left key to INPUT
    pinMode(left_key, INPUT);
}
void servo_handling()
{
}

void f_ct2000_loop()
{
    Serial.print("CT-G_L: ");
    Serial.println(g_loop_c++);

    servo_base.attach(A1); //set the control pin of Servo1 to A1
    servo_left.attach(A0); //set the control pin of Servo2 to A0
    servo_right.attach(8); //set the control pin of Servo3 to D8
    servo_arm.attach(9);   //set the control pin of Servo4 to D9

    x1 = analogRead(right_X); // read the value of right X axis

    y1 = analogRead(right_Y);    // read the value of right Y axis
    z1 = digitalRead(right_key); ////read the value of right Z axis

    x2 = analogRead(left_X);    //read the value of left X axis
    y2 = analogRead(left_Y);    //read the value of left Y axis
    z2 = digitalRead(left_key); //read the value of left Z axis

    Serial.println("**********right**********");
    Serial.print("right_X = "); // on the serial monitor, print out right_X =
    Serial.print(x1, DEC);      // print out the value of right X and line wrap
    Serial.print("  ");
    Serial.print("right_Y = ");
    Serial.print(y1, DEC);
    Serial.print("  ");
    Serial.print("right_key = ");
    Serial.print(z1, DEC);
    Serial.print(" ||| ");
    Serial.println("*********left***********");
    Serial.print("left_X = ");
    Serial.print(x2, DEC);
    Serial.print("  ");
    Serial.print("left_Y = ");
    Serial.print(y2, DEC);
    Serial.print("  ");
    Serial.print("left_key = ");
    Serial.println(z2, DEC);

    spoon();
    rotate();
    right_ser();
    left_ser();
}

void spoon()
{
    // todo
}

void rotate()
{
    if (x1 < 50) // right stick right
    {
        pos_base--;
        servo_base.write(pos_base);
        delay(5);
        if (pos_base < 1)
        {
            pos_base = 1;
        }
    }

    if (x1 > 1000) // if push the right joystick to the left
    {
        pos_base++;                 //posa plus 1
        servo_base.write(pos_base); //arm turns left
        delay(5);
        if (pos_base > 180) //limit the angle when turn left
        {
            pos_base = 180;
        }
    }
}

//Right Servo
void right_ser()
{
    if (y1 < 50) //if push the right joystick backward
    {
        pos_right = pos_right - 1;
        servo_right.write(pos_right); //the joystick of right Servo swings backward
        delay(5);
        if (pos_right < 0) //limit the angle
        {
            pos_right = 0;
        }
    }
    if (y1 > 1000) // if push the right joystick forward
    {
        pos_right = pos_right + 1;
        servo_right.write(pos_right); //the joystick of right Servo swings forward
        delay(5);
        if (pos_right > 180) //limit the angle when go down
        {
            pos_right = 180;
        }
    }
}

//*************************************************************/
//Left Servo
void left_ser()
{
    if (y2 < 50) //if push the left joystick backward
    {
        pos_left = pos_left + 1;
        servo_left.write(pos_left); //the joystick of left Servo swings backward
        delay(5);
        if (pos_left > 180) // limit the retracted angle
        {
            pos_left = 180;
        }
    }

    if (y2 > 1000) //if push the left joystick forward
    {
        pos_left = pos_left - 1;
        servo_left.write(pos_left); //the joystick of left Servo swings forward
        delay(5);
        if (pos_left < 35) // Limit the the stretched angle
        {
            pos_left = 35;
        }
    }
}