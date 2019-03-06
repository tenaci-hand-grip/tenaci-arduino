#include <Servo.h>
#include <SimpleKalmanFilter.h>
#include "tasks.h"
#include "pins.h"
#include "sensor-constants.h"


Servo servo;

// values from flex and force sensors

// degrees
double *thumb_flex_value;
double *index_flex_value;
double *middle_flex_value;
double *ring_flex_value;
double *pinky_flex_value;

// grams
double *thumb_force_value;
double *index_force_value;




















void setup()
{
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);

    // attach servo
    servo.attach(SERVO_PIN);

    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
    }
    Serial.println("Serial attached!");




}

void loop()
{




}
