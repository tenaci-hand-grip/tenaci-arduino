#ifndef TENACI_FORCE_SENSOR_H
#define TENACI_FORCE_SENSOR_H

#include "Sensor.hpp"

class ForceSensor : public Sensor
{
public:
    ForceSensor(struct sensor_data_t *sensor_info);
    void read();
protected:
    float resistor_resistance;
};


#endif // TENACI_FORCE_SENSOR_H
