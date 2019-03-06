#include "FlexSensor.hpp"

FlexSensor::FlexSensor(struct sensor_data_t *sensor_info) : Sensor(sensor_info)
{
    resistor_resistance = sensor_info->resistor_resistance;
    resistance_straight = sensor_info->resistance_straight;
    resistance_bent = sensor_info->resistance_bent;
}

void FlexSensor::read()
{
    // https://learn.sparkfun.com/tutorials/flex-sensor-hookup-guide/all

    // Read the ADC, and calculate voltage and resistance from it
    int raw_adc_reading = analogRead(pin);
    double flex_voltage = raw_adc_reading * M_VCC / 1023.0;
    double flex_resistance = resistor_resistance * (M_VCC / flex_voltage - 1.0);

    // Use the calculated resistance to estimate the sensor's
    // bend angle:
    double angle = map(flex_resistance, resistance_straight, resistance_bent, 0, 90.0);

    double processed = kalmanFilter.updateEstimate(angle);

    *value = processed;
}