#ifndef TENACI_TASKS_H
#define TENACI_TASKS_H

void TaskAnalogRead(void *);
void TaskSerialRead(void *);
void TaskSerialWrite(void *);

void TaskReadFlex(void *);
void TaskReadForce(void *);

void TaskReadSensitivity(void *);

struct finger_struct
{
    int pin;
    double *pvalue;
};

#endif
