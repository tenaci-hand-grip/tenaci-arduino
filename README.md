# Tenaci Hand Grip

## Objective

Tenaci Hand Grip is designed to facilitate our client, who suffers from deteriorated hand grip strength, in everyday tasks involving their hands.

## System Overview

The system is based on a real-time system, specifically FreeRTOS for Arduino. This allows us to run concurrent tasks to:
* measure and apply post-processing to finger flex
* measure and apply post-processing to grip pressure
* calculate and control target thumb flex

The logic to determine what the target thumb flex value should be is based on Embedded Fuzzy Logic Library (eFLL), which allows us to define rules based on degrees of flex in the fingers. This target value is then processed in a PID loop to ensure the thumb movement is accurate and tuned to the client's desired sensitivity.

## Dependencies

* [FreeRTOS](https://github.com/feilipu/Arduino_FreeRTOS_Library)
* [Embedded Fuzzy Logic Library](https://github.com/zerokol/eFLL)
* [SimpleKalmanFilter](https://github.com/denyssene/SimpleKalmanFilter)

## Schematic

![Schematic](https://raw.githubusercontent.com/tenaci-hand-grip/tenaci-schematic/master/schematic.png)
