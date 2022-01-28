// -------------------------------------------------------------------------------
// Copyright (c) Ladendorfer Daniel.
// All Rights Reserved.  See LICENSE in the project root for license information.
// -------------------------------------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "CT2000.h"

#define c_BAUD 9600
#define c_DELAY 10

int g_loop_c = 0;

void f_ct2000_setup()
{
    Serial.begin(c_BAUD);
    Serial.println("CT2000 setup");
}

void f_ct2000_loop()
{
    Serial.print("CT-G_L: ");
    Serial.println(g_loop_c++);
    delay(c_DELAY);
}