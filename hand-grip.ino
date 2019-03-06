#include <Servo.h>
#include "SimpleKalmanFilter.h"
#include "pins.h"
#include "sensor-constants.h"
#include "Sensor.hpp"
#include "FlexSensor.hpp"
#include "ForceSensor.hpp"

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

// grip sensitivity
double *grip_sensitivity;




// finger/thumb structs

// flex sensor structs
sensor_data_t thumb_flex_data = {
        FLEX_THUMB_PIN,
        thumb_flex_value,
        M_47K_RES_THUMB,
        M_THUMB_FLEX_STRAIGHT,
        M_THUMB_FLEX_BENT
};
sensor_data_t index_flex_data = {
        FLEX_INDEX_PIN,
        index_flex_value,
        M_47K_RES_INDEX,
        M_INDEX_FLEX_STRAIGHT,
        M_INDEX_FLEX_BENT
};
sensor_data_t middle_flex_data = {
        FLEX_MIDDLE_PIN,
        middle_flex_value,
        M_47K_RES_MIDDLE,
        M_MIDDLE_FLEX_STRAIGHT,
        M_MIDDLE_FLEX_BENT
};
sensor_data_t pinky_flex_data = {
        FLEX_PINKY_PIN,
        pinky_flex_value,
        M_47K_RES_PINKY,
        M_PINKY_FLEX_STRAIGHT,
        M_PINKY_FLEX_BENT
};

// force sensor structs
sensor_data_t thumb_force_data = {
        FORCE_THUMB_PIN,
        thumb_force_value,
        M_3K_RES_THUMB,
        0,
        0
};
sensor_data_t index_force_data = {
        FORCE_INDEX_PIN,
        index_force_value,
        M_3K_RES_INDEX,
        0,
        0
};

FlexSensor thumb_flex_sensor(&thumb_flex_data);
FlexSensor index_flex_sensor(&index_flex_data);
FlexSensor middle_flex_sensor(&middle_flex_data);
FlexSensor pinky_flex_sensor(&pinky_flex_data);

ForceSensor thumb_force_sensor(&thumb_force_data);
ForceSensor index_force_sensor(&index_force_data);

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
    thumb_flex_sensor.read();
    index_flex_sensor.read();
    middle_flex_sensor.read();
    pinky_flex_sensor.read();

    thumb_force_sensor.read();
    index_force_sensor.read();

    Serial.print("Thumb flex: ");
    Serial.println(*thumb_flex_value);

    Serial.print("Index flex: ");
    Serial.println(*index_flex_value);

    Serial.print("Middle flex: ");
    Serial.println(*middle_flex_value);

    Serial.print("Pinky flex: ");
    Serial.println(*pinky_flex_value);

    Serial.print("Thumb force: ");
    Serial.println(*thumb_force_value);

    Serial.print("Index force: ");
    Serial.println(*index_force_value);

    delay(1000);
}
