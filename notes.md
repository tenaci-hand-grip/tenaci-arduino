# Notes and TODO

## LED_BUILTIN Status

* LED_BUILTIN (pin 13) is used as an error status indicator for FreeRTOS
* Slow blink: stack overflow  (if any stack (for the loop() or) for any task overflows)
* Fast blink: heap overflow (if any task tries to allocate memory and that allocation fails)

## Memory Usage

* there isn't enough memory to use all of the sensors...
* there is only 2KB of memory
* only ~128B available when using [thumb, index, middle, pinky] flex sensors and [thumb, index] force sensors
* still need to implement task for fuzzy logic controller which would take more than 128B...

**Temporary workaround:**

* only use [index, pinky] flex sensors and [thumb] pressure sensor
* no serial input
* no serial output
* attempt to include the fuzzy logic controller

**TODO:**

* try to use only two tasks to measure flex and force