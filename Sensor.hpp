#ifndef TENACI_SENSOR_H
#define TENACI_SENSOR_H

struct finger_sensor_struct
{
    int pin;
    double *pvalue; // pointer to where value is stored
    double resistance; // resistance of voltage divider resistor
    double resistance_straight; // resistance of straight flex sensor
    double resistance_bent; // resistance of bent (90 degrees) flex sensor
};

class Sensor
{
public:
    Sensor();
    virtual void read(void);

private:
    uint8_t pin;
    double *value;
};


#endif // TENACI_SENSOR_H
