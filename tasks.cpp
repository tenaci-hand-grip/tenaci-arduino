#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <Servo.h>
#include <SimpleKalmanFilter.h>
#include "tasks.h"
#include "pins.h"
#include "sensor-constants.h"

#define MAX_INSTRUCTION_BUFFER_SIZE 8

extern SemaphoreHandle_t xSerialSemaphore;

extern Servo servo;

void TaskSerialRead(void *pvParameters)
{
    (void)pvParameters;

    extern String serial_instruction;

    for (;;) // A Task shall never return or exit.
    {
        int incoming_byte = 0;
        char buffer[MAX_INSTRUCTION_BUFFER_SIZE];
        int count = 0;

        bool error_flag = false;

        /*
        if (Serial.available() > 0)
        {
            while (Serial.available())
            {
                incoming_byte = Serial.read();
                delay(5);

                // reset buffer if its size reaches the max size for the array
                if (count >= MAX_INSTRUCTION_BUFFER_SIZE - 1)
                {
                    count = 0;
                    memset(&buffer[0], 0, sizeof(buffer));
                    error_flag = true;
                    break;
                }

                // add one char at a time to char array buffer
                buffer[count] = char(incoming_byte);
                count++;
            }

            if (!error_flag)
            {
                buffer[count] = '\0';

                serial_instruction = String(buffer);

                // reset buffer
                memset(&buffer[0], 0, sizeof(buffer));
                count = 0;
            }
        }
        */
        //serial_instruction = "asdf";
        if (Serial.available() > 0)
            serial_instruction = Serial.readString();

        vTaskDelay(10 / portTICK_PERIOD_MS); // wait for one tick (15ms)
    }
}

void TaskSerialWrite(void *pvParameters) // This is a task.
{
    (char *)pvParameters;

    extern String serial_instruction;

    // values from flex and force sensors

    // degrees
    //extern double thumb_flex_value;
    extern double index_flex_value;
    // extern double middle_flex_value;
    // extern double ring_flex_value;
    extern double pinky_flex_value;

    // grams
    extern double thumb_force_value;
    //extern double index_force_value;

    // extern volatile uint8_t encoder_cw;
    // extern volatile uint8_t encoder_ccw;

    for (;;) // A Task shall never return or exit.
    {
        if (xSerialSemaphore != NULL)
        {
            if (xSemaphoreTake(xSerialSemaphore, (TickType_t)0) == pdTRUE)
            {
                // Serial.print("serial_instruction: [");
                // Serial.print(serial_instruction);
                // Serial.println("]");

                // Serial.print("thumb_flex_value: [");
                // Serial.print(thumb_flex_value);
                // Serial.println("]");

                Serial.print("index_flex_value: [");
                Serial.print(index_flex_value);
                Serial.println("]");

                // Serial.print("middle_flex_value: [");
                // Serial.print(middle_flex_value);
                // Serial.println("]");

                Serial.print("pinky_flex_value: [");
                Serial.print(pinky_flex_value);
                Serial.println("]");

                Serial.print("thumb_force_value: [");
                Serial.print(thumb_force_value);
                Serial.println("]");

                // Serial.print("index_force_value: [");
                // Serial.print(index_force_value);
                // Serial.println("]");

                // Serial.print("cc: ");
                // Serial.println(encoder_cw);

                // Serial.print("ccw: ");
                // Serial.println(encoder_ccw);

                xSemaphoreGive(xSerialSemaphore);
            }
        }
        else
        {
            xSerialSemaphore = xSemaphoreCreateMutex();
            if (xSerialSemaphore != NULL)
                xSemaphoreGive(xSerialSemaphore);
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
    }
}

void TaskReadFlex(void *pvParameters)
{
    // https://learn.sparkfun.com/tutorials/flex-sensor-hookup-guide/all

    finger_sensor_struct *sensor = (finger_sensor_struct *)pvParameters;
    pinMode(sensor->pin, INPUT);

    // SimpleKalmanFilter(e_mea, e_est, q);
    // e_mea: Measurement Uncertainty
    // e_est: Estimation Uncertainty
    // q: Process Noise
    SimpleKalmanFilter kalman(2, 2, 0.01);

    for (;;)
    {
        // Read the ADC, and calculate voltage and resistance from it
        int raw_adc_reading = analogRead(sensor->pin);
        double flex_voltage = raw_adc_reading * M_VCC / 1023.0;
        double flex_resistance = sensor->resistance * (M_VCC / flex_voltage - 1.0);

        // Use the calculated resistance to estimate the sensor's
        // bend angle:
        double angle = map(flex_resistance, sensor->resistance_straight, sensor->resistance_bent, 0, 90.0);

        double processed = kalman.updateEstimate(angle);

        *(sensor->pvalue) = processed;

        vTaskDelay(1); // wait for one tick (15ms)
    }
}

void TaskReadForce(void *pvParameters)
{
    // https://learn.sparkfun.com/tutorials/force-sensitive-resistor-hookup-guide/all

    finger_sensor_struct *sensor = (finger_sensor_struct *)pvParameters;
    pinMode(sensor->pin, INPUT);

    // SimpleKalmanFilter(e_mea, e_est, q);
    // e_mea: Measurement Uncertainty
    // e_est: Estimation Uncertainty
    // q: Process Noise
    SimpleKalmanFilter kalman(2, 2, 0.01);

    for (;;)
    {
        double force = 0;

        int raw_adc_reading = analogRead(sensor->pin);

        // If the FSR has no pressure, the resistance will be
        // near infinite. So the voltage should be near 0.
        if (raw_adc_reading != 0) // If the analog reading is non-zero
        {
            // Use ADC reading to calculate voltage:
            double force_voltage = raw_adc_reading * M_VCC / 1023.0;

            // Use voltage and static resistor value to
            // calculate FSR resistance:
            double force_resistance = sensor->resistance * (M_VCC / force_voltage - 1.0);

            // Guesstimate force based on slopes in figure 3 of
            // FSR datasheet:
            double force_conductance = 1.0 / force_resistance; // Calculate conductance

            // Break parabolic curve down into two linear slopes:
            if (force_resistance <= 600)
                force = (force_conductance - 0.00075) / 0.00000032639;
            else
                force = force_conductance / 0.000000642857;
        }

        double processed = kalman.updateEstimate(force);

        *(sensor->pvalue) = processed;

        vTaskDelay(1); // wait for one tick (15ms)
    }
}
