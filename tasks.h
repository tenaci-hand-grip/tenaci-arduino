#ifndef TENACI_TASKS_H
#define TENACI_TASKS_H

void TaskSerialRead(void *);
void TaskSerialWrite(void *);

void TaskReadFlex(void *);
void TaskReadForce(void *);

void TaskReadSensitivity(void *);

struct finger_sensor_struct
{
    int pin;
    double *pvalue; // pointer to where value is stored
    double resistance; // resistance of voltage divider resistor
    double resistance_straight; // resistance of straight flex sensor
    double resistance_bent; // resistance of bent (90 degrees) flex sensor
};

#endif // TENACI_TASKS_H
