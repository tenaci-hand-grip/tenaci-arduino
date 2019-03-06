#include <Arduino.h>
#include "Sensor.hpp"

Sensor::Sensor(struct sensor_data_t *sensor_info)
{
    pin = sensor_info->pin;
    value = sensor_info->pvalue;

    pinMode(pin, INPUT);

    kalmanFilter = SimpleKalmanFilter(2, 2, 0.01);
}

Sensor::Sensor()
{
}

void Sensor::read()
{
}
