#ifndef TENACI_SENSOR_H
#define TENACI_SENSOR_H

#include "SimpleKalmanFilter.h"
#include "pins.h"
#include "sensor-constants.h"

struct sensor_data_t
{
    int pin;
    double *pvalue; // pointer to where value is stored
    double resistor_resistance; // resistance of voltage divider resistor
    double resistance_straight; // resistance of straight flex sensor
    double resistance_bent; // resistance of bent (90 degrees) flex sensor
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
    double *value;
};


#endif // TENACI_SENSOR_H
