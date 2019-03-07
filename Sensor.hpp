#ifndef TENACI_SENSOR_H
#define TENACI_SENSOR_H

#include "SimpleKalmanFilter.h"
#include "pins.h"
#include "sensor-constants.h"

struct sensor_data_t
{
    int pin;
    float *pvalue; // pointer to where value is stored
    float resistor_resistance; // resistance of voltage divider resistor
    float resistance_straight; // resistance of straight flex sensor
    float resistance_bent; // resistance of bent (90 degrees) flex sensor
};

class Sensor
{
public:
    Sensor(struct sensor_data_t *sensor_info);
    Sensor();
    virtual void read(void);
protected:
    SimpleKalmanFilter kalmanFilter;
    int pin;
    float *value;
};


#endif // TENACI_SENSOR_H
