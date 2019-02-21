#ifndef TENACI_TASKS_H
#define TENACI_TASKS_H

void TaskBlink(void *);
void TaskAnalogRead(void *);
void TaskSerialRead(void *);
void TaskSerialWrite(void *);
void TaskServoSweep(void *);
void TaskReadThumb(void *);
void TaskReadIndexFinger(void *);
void TaskReadMiddleFinger(void);
void TaskReadRingFinger(void *);
void TaskReadPinkyFinger(void *);

#endif