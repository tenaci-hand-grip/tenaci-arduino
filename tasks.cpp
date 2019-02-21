#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <Servo.h>
#include <Stepper.h>
#include "tasks.h"
#include "pins.h"

extern Servo servo;
extern SemaphoreHandle_t xSerialSemaphore;


void TaskAnalogRead(void *pvParameters) // This is a task.
{
    (void)pvParameters;

    for (;;)
    {
        // read the input on analog pin 0:
        int sensorValue = analogRead(A0);
        // print out the value you read:
        Serial.println(sensorValue);
        vTaskDelay(100); // one tick delay (15ms) in between reads for stability
    }
}

void TaskSerialRead(void *pvParameters) // This is a task.
{
    (void)pvParameters;

    for (;;) // A Task shall never return or exit.
    {
        if (xSerialSemaphore != NULL)
        {
            if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE)
            {
                Serial.println("hello!");
                xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
            }
        }
        vTaskDelay(1); // wait for one tick (15ms)
    }
}

void TaskSerialWrite(void *pvParameters) // This is a task.
{
    (char *)pvParameters;

    for (;;) // A Task shall never return or exit.
    {
        if (xSerialSemaphore != NULL)
        {
            // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
            if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE)
            {
                Serial.println("hello!");
                xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
            }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
    }
}

void TaskReadFlex(void *pvParameters)
{
    finger_struct *finger = (finger_struct *)pvParameters;
    pinMode(finger->pin, INPUT);
    int raw_value;

    for (;;)
    {
        raw_value = analogRead(finger->pin);
        // TODO: value processing
        *(finger->pvalue) = 0;
    }
}

void TaskReadForce(void *pvParameters)
{
    finger_struct *finger = (finger_struct *)pvParameters;
    pinMode(finger->pin, INPUT);
    int raw_value;

    for (;;)
    {
        raw_value = analogRead(finger->pin);
        // TODO: value processing
        *(finger->pvalue) = 0;
    }
}
