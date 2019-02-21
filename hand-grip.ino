#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <Servo.h>
#include <Stepper.h>
#include "tasks.h"
#include "pins.h"

#define STEPPER_STEPS 200

SemaphoreHandle_t xSerialSemaphore;
Servo servo;
Stepper stepper(STEPPER_STEPS, STEPPER_1A_PIN, STEPPER_2A_PIN, STEPPER_3A_PIN, STEPPER_4A_PIN);

// values from flex and force sensors
double thumb_flex_value;
double index_flex_value;
double middle_flex_value;
double ring_flex_value;
double pinky_flex_value;

double thumb_force_value;
double index_force_value;

// finger/thumb structs
finger_struct thumb_flex_t = {FLEX_THUMB_PIN, &thumb_flex_value};
finger_struct index_flex_t = {FLEX_INDEX_PIN, &index_flex_value};
finger_struct middle_flex_t = {FLEX_MIDDLE_PIN, &middle_flex_value};
finger_struct ring_flex_t = {FLEX_RING_PIN, &ring_flex_value};
finger_struct pinky_flex_t = {FLEX_PINKY_PIN, &pinky_flex_value};

finger_struct thumb_force_t = {FORCE_THUMB_PIN, &thumb_force_value};
finger_struct index_force_t = {FORCE_INDEX_PIN, &index_force_value};

// the setup function runs once when you press reset or power the board
void setup()
{
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);

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

    // Now set up tasks to run independently.
    xTaskCreate (
        TaskAnalogRead,
        (const portCHAR *)"AnalogRead",
        128, // Stack size
        NULL,
        1, // Priority
        NULL);

    xTaskCreate (
        TaskSerialWrite,
        (const portCHAR *)"SerialWrite", // A name just for humans
        128, // This stack size can be checked & adjusted by reading the Stack Highwater
        NULL,
        2, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        NULL);

    xTaskCreate (
        TaskReadFlex,
        (const portCHAR *)"ReadFlexThumb",
        128,
        &thumb_flex_t,
        2,
        NULL);

    xTaskCreate (
        TaskReadFlex,
        (const portCHAR *)"ReadFlexIndex",
        128,
        &index_flex_t,
        2,
        NULL);

    xTaskCreate (
        TaskReadFlex,
        (const portCHAR *)"ReadFlexMiddle",
        128,
        &middle_flex_t,
        2,
        NULL);

    xTaskCreate (
        TaskReadFlex,
        (const portCHAR *)"ReadFlexRing",
        128,
        &ring_flex_t,
        2,
        NULL);

    xTaskCreate (
        TaskReadFlex,
        (const portCHAR *)"ReadFlexPinky",
        128,
        &pinky_flex_t,
        2,
        NULL);

    xTaskCreate (
        TaskReadForce,
        (const portCHAR *)"ReadForceThumb",
        128,
        &thumb_force_t,
        2,
        NULL);

    xTaskCreate (
        TaskReadForce,
        (const portCHAR *)"ReadForceIndex",
        128,
        &index_force_t,
        2,
        NULL);

    // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
    // Empty. Things are done in Tasks.
}
