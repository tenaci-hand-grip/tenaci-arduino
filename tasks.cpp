#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <Servo.h>
#include "tasks.h"

extern Servo servo;
extern SemaphoreHandle_t xSerialSemaphore;

void TaskBlink(void *pvParameters) // This is a task.
{
    (void)pvParameters;

    // initialize digital LED_BUILTIN on pin 13 as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    for (;;) // A Task shall never return or exit.
    {
        digitalWrite(LED_BUILTIN, HIGH);      // turn the LED on (HIGH is the voltage level)
        vTaskDelay(100 / portTICK_PERIOD_MS); // wait for one second
        digitalWrite(LED_BUILTIN, LOW);       // turn the LED off by making the voltage LOW
        vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
    }
}

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

void TaskServoSweep(void *pvParameters) // This is a task.
{
    (void)pvParameters;

    int pos;
    for (;;) // A Task shall never return or exit.
    {
        for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            servo.write(pos);              // tell servo to go to position in variable 'pos'
            vTaskDelay(15 / portTICK_PERIOD_MS); // wait for one second
        }
        for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
            servo.write(pos);              // tell servo to go to position in variable 'pos'
            vTaskDelay(15 / portTICK_PERIOD_MS); // wait for one second
        }
    }
}
