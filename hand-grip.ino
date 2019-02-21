#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <Servo.h>
#include "tasks.h"
#include "pins.h"


SemaphoreHandle_t xSerialSemaphore;
Servo servo;

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

    servo.attach(9);
    servo.attach(10);

    // Now set up tasks to run independently.
    xTaskCreate (
        TaskBlink,
        (const portCHAR *)"Blink", // A name just for humans
        128, // This stack size can be checked & adjusted by reading the Stack Highwater
        NULL,
        2, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        NULL);

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

    // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
    // Empty. Things are done in Tasks.
}
