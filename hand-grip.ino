#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <Servo.h>
#include <SimpleKalmanFilter.h>
#include "tasks.h"
#include "pins.h"
#include "sensor-constants.h"


SemaphoreHandle_t xSerialSemaphore;
Servo servo;

volatile uint8_t encoder_cw = 0;
volatile uint8_t encoder_ccw = 0;

String serial_instruction = "init";

// values from flex and force sensors

// degrees
//double thumb_flex_value;
double index_flex_value;
//double middle_flex_value;
//double ring_flex_value;
double pinky_flex_value;

// grams
double thumb_force_value;
//double index_force_value;

// finger/thumb structs

// flex sensor structs
// finger_sensor_struct thumb_flex_t = {
//         .pin = FLEX_THUMB_PIN,
//         .pvalue = &thumb_flex_value,
//         .resistance = M_47K_RES_THUMB,
//         .resistance_straight = M_THUMB_FLEX_STRAIGHT,
//         .resistance_bent = M_THUMB_FLEX_BENT};
finger_sensor_struct index_flex_t = {
        .pin = FLEX_INDEX_PIN,
        .pvalue = &index_flex_value,
        .resistance = M_47K_RES_INDEX,
        .resistance_straight = M_INDEX_FLEX_STRAIGHT,
        .resistance_bent = M_INDEX_FLEX_BENT};
// finger_sensor_struct middle_flex_t = {
//         .pin = FLEX_MIDDLE_PIN,
//         .pvalue = &middle_flex_value,
//         .resistance = M_47K_RES_MIDDLE,
//         .resistance_straight = M_MIDDLE_FLEX_STRAIGHT,
//         .resistance_bent = M_MIDDLE_FLEX_BENT};
finger_sensor_struct pinky_flex_t = {
        .pin = FLEX_PINKY_PIN,
        .pvalue = &pinky_flex_value,
        .resistance = M_47K_RES_PINKY,
        .resistance_straight = M_PINKY_FLEX_STRAIGHT,
        .resistance_bent = M_PINKY_FLEX_BENT};

// force sensor structs
finger_sensor_struct thumb_force_t = {
        .pin = FORCE_THUMB_PIN,
        .pvalue = &thumb_force_value,
        .resistance = M_3K_RES_THUMB};
// finger_sensor_struct index_force_t = {
//         .pin = FORCE_INDEX_PIN,
//         .pvalue = &index_force_value,
//         .resistance = M_3K_RES_INDEX};


void inc_cw(void)
{
    ++encoder_cw;
}

void inc_ccw(void)
{
    ++encoder_ccw;
}

void setup()
{
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);

    // attach servo
    servo.attach(SERVO_PIN);

    servo.write(90);

    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
    }
    Serial.println("Serial attached!");

    if (xSerialSemaphore == NULL) // Check to confirm that the Serial Semaphore has not already been created.
    {
        xSerialSemaphore = xSemaphoreCreateMutex(); // Create a mutex semaphore we will use to manage the Serial Port
        if (xSerialSemaphore != NULL)
            xSemaphoreGive(xSerialSemaphore); // Make the Serial Port available for use, by "Giving" the Semaphore.
    }

    // pinMode(2, INPUT);
    // pinMode(3, INPUT);
    // attachInterrupt(digitalPinToInterrupt(2), inc_cw, RISING);
    // attachInterrupt(digitalPinToInterrupt(3), inc_ccw, RISING);

    Serial.println("Starting tasks...");

    // Now set up tasks to run independently.

    xTaskCreate (
        TaskSerialWrite,
        (const portCHAR *)"SerialWrite", // A name just for humans
        350, // This stack size can be checked & adjusted by reading the Stack Highwater
        NULL,
        2, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        NULL);

    /*
    xTaskCreate (
        TaskSerialRead,
        (const portCHAR *)"SerialRead", // A name just for humans
        128, // This stack size can be checked & adjusted by reading the Stack Highwater
        NULL,
        2, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        NULL);
    */

    // xTaskCreate (
    //     TaskReadFlex,
    //     (const portCHAR *)"ReadFlexThumb",
    //     64,
    //     &thumb_flex_t,
    //     2,
    //     NULL);

    xTaskCreate (
        TaskReadFlex,
        (const portCHAR *)"ReadFlexIndex",
        64,
        &index_flex_t,
        2,
        NULL);

    // xTaskCreate (
    //     TaskReadFlex,
    //     (const portCHAR *)"ReadFlexMiddle",
    //     64,
    //     &middle_flex_t,
    //     2,
    //     NULL);

    xTaskCreate (
        TaskReadFlex,
        (const portCHAR *)"ReadFlexPinky",
        64,
        &pinky_flex_t,
        2,
        NULL);

    xTaskCreate (
        TaskReadForce,
        (const portCHAR *)"ReadForceThumb",
        64,
        &thumb_force_t,
        2,
        NULL);

    // xTaskCreate (
    //     TaskReadForce,
    //     (const portCHAR *)"ReadForceIndex",
    //     64,
    //     &index_force_t,
    //     2,
    //     NULL);

    // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
    // Empty. Things are done in Tasks.
}
