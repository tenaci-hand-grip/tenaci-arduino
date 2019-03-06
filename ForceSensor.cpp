#include "Arduino.h"
#include "ForceSensor.hpp"

ForceSensor::ForceSensor(struct sensor_data_t *sensor_info) : Sensor(sensor_info)
{
    resistor_resistance = sensor_info->resistor_resistance;
}

void ForceSensor::read()
{
    // https://learn.sparkfun.com/tutorials/force-sensitive-resistor-hookup-guide/all

    double force = 0;

    int raw_adc_reading = analogRead(pin);

    // If the FSR has no pressure, the resistance will be
    // near infinite. So the voltage should be near 0.
    if (raw_adc_reading != 0) // If the analog reading is non-zero
    {
        // Use ADC reading to calculate voltage:
        double force_voltage = raw_adc_reading * M_VCC / 1023.0;

        // Use voltage and static resistor value to
        // calculate FSR resistance:
        double force_resistance = resistor_resistance * (M_VCC / force_voltage - 1.0);

        // Guesstimate force based on slopes in figure 3 of
        // FSR datasheet:
        double force_conductance = 1.0 / force_resistance; // Calculate conductance

        // Break parabolic curve down into two linear slopes:
        if (force_resistance <= 600)
            force = (force_conductance - 0.00075) / 0.00000032639;
        else
            force = force_conductance / 0.000000642857;
    }

    double processed = kalmanFilter.updateEstimate(force);

    *value = processed;
}