#ifndef TENACI_FLEX_SENSOR_H
#define TENACI_FLEX_SENSOR_H

#include "Sensor.hpp"

class FlexSensor : public Sensor
{
public:
    FlexSensor(struct sensor_data_t *sensor_info);
    void read();
protected:
    float resistance_straight;
    float resistance_bent;
    float resistor_resistance;
};


#endif // TENACI_FLEX_SENSOR_H
