#include "Arduino.h"
#include <Servo.h>
#include "SimpleKalmanFilter.h"
#include "pins.h"
#include "sensor-constants.h"
#include "Sensor.hpp"
#include "FlexSensor.hpp"
#include "ForceSensor.hpp"
#include "FuzzyController.hpp"

#define INIT_TIME 5000

int loop_delay = 5;
bool tenaci_debug = false;

Servo servo;

// values from flex and force sensors

// degrees
float thumb_flex_value;
float index_flex_value;
float middle_flex_value;
float ring_flex_value;
float pinky_flex_value;

// grams
float thumb_force_value;
float index_force_value;

// grip sensitivity
float grip_sensitivity;




// finger/thumb structs

// flex sensor structs
sensor_data_t thumb_flex_data = {
        FLEX_THUMB_PIN,
        &thumb_flex_value,
        M_47K_RES_THUMB,
        M_THUMB_FLEX_STRAIGHT,
        M_THUMB_FLEX_BENT
};
sensor_data_t index_flex_data = {
        FLEX_INDEX_PIN,
        &index_flex_value,
        M_47K_RES_INDEX,
        M_INDEX_FLEX_STRAIGHT,
        M_INDEX_FLEX_BENT
};
sensor_data_t middle_flex_data = {
        FLEX_MIDDLE_PIN,
        &middle_flex_value,
        M_47K_RES_MIDDLE,
        M_MIDDLE_FLEX_STRAIGHT,
        M_MIDDLE_FLEX_BENT
};
sensor_data_t pinky_flex_data = {
        FLEX_PINKY_PIN,
        &pinky_flex_value,
        M_47K_RES_PINKY,
        M_PINKY_FLEX_STRAIGHT,
        M_PINKY_FLEX_BENT
};

// force sensor structs
sensor_data_t thumb_force_data = {
        FORCE_THUMB_PIN,
        &thumb_force_value,
        M_3K_RES_THUMB,
        0,
        0
};
sensor_data_t index_force_data = {
        FORCE_INDEX_PIN,
        &index_force_value,
        M_3K_RES_INDEX,
        0,
        0
};

FlexSensor *thumb_flex_sensor;
FlexSensor *index_flex_sensor;
FlexSensor *middle_flex_sensor;
FlexSensor *pinky_flex_sensor;

ForceSensor *thumb_force_sensor;
ForceSensor *index_force_sensor;


FuzzyController *fc;

void setup()
{
    Serial.begin(9600);

    unsigned long start_time = millis();
    while ( (millis() < start_time + INIT_TIME) && !Serial )
    {
        ; // wait for serial port to connect
    }
    if (!Serial)
    {
        // serial is not connected (ie. using battery power), disabling serial lines
        Serial.end();
    } else {
        // serial is connected, enabling serial debugging messages
        tenaci_debug = true;
        loop_delay = 500;
        Serial.println("Serial attached!");
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, HIGH);
    }


    // attach servo
    servo.attach(SERVO_PIN);

    thumb_flex_sensor = new FlexSensor(&thumb_flex_data);
    index_flex_sensor = new FlexSensor(&index_flex_data);
    middle_flex_sensor = new FlexSensor(&middle_flex_data);
    pinky_flex_sensor = new FlexSensor(&pinky_flex_data);

    thumb_force_sensor = new ForceSensor(&thumb_force_data);
    index_force_sensor = new ForceSensor(&index_force_data);

    fc = new FuzzyController(&index_flex_value, &middle_flex_value, &pinky_flex_value, &thumb_force_value, &index_force_value);
}

int loop_counter = 0;

void loop()
{
    servo.write(90);

    // thumb_flex_sensor->read();
    index_flex_sensor->read();
    // middle_flex_sensor->read();
    // pinky_flex_sensor->read();

    // thumb_force_sensor->read();
    // index_force_sensor->read();

    index_flex_value = loop_counter;
    loop_counter += 10;
    if (loop_counter > 100)
    {
        loop_counter = 0;
    }

    float output = fc->getThumbOutput();

    if (tenaci_debug)
    {

        // Formatted to use Arduino serial plotter
        // Serial.print("TF: "); Serial.print(thumb_flex_value); Serial.print(", "); // Thumb flex
        Serial.print("IF: "); Serial.print(index_flex_value); Serial.print(", "); // Index flex
        // Serial.print("MF: "); Serial.print(middle_flex_value); Serial.print(", "); // Middle flex
        // Serial.print("PF: "); Serial.print(pinky_flex_value); Serial.print(", "); // Pinky flex
        // Serial.print("TP: "); Serial.print(thumb_force_value); Serial.print(", "); // Thumb force
        // Serial.print("IP: "); Serial.println(index_force_value); // Index force

        Serial.print("TF: "); Serial.print(output); Serial.println();
    }



    delay(500);
}
