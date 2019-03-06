#ifndef TENACI_SENSOR_CONSTANTS_H
#define TENACI_SENSOR_CONSTANTS_H

// min/max flex values (degrees)
#define FLEX_MIN 0
#define FLEX_MAX 100

// min/max force values (g)
#define FORCE_MIN 0
#define FORCE_MAX 10000

// 5V line
#define M_VCC 5 // measured voltage of 5V line

// Flex sensor - thumb
#define M_47K_RES_THUMB 47000.0 // measured resistance of 47K resistor
#define M_THUMB_FLEX_STRAIGHT 37300.0 // measured resistance of flex sensor when straight
#define M_THUMB_FLEX_BENT 90000.0 // measured resistance of flex sensor when bent to ninety degrees

// Flex sensor - index
#define M_47K_RES_INDEX 47000.0 // measured resistance of 47K resistor
#define M_INDEX_FLEX_STRAIGHT 37300.0 // measured resistance of flex sensor when straight
#define M_INDEX_FLEX_BENT 90000.0 // measured resistance of flex sensor when bent to ninety degrees

// Flex sensor - middle
#define M_47K_RES_MIDDLE 47000.0 // measured resistance of 47K resistor
#define M_MIDDLE_FLEX_STRAIGHT 37300.0 // measured resistance of flex sensor when straight
#define M_MIDDLE_FLEX_BENT 90000.0 // measured resistance of flex sensor when bent to ninety degrees

// Flex sensor - ring
#define M_47K_RES_RING 47000.0 // measured resistance of 47K resistor
#define M_RING_FLEX_STRAIGHT 37300.0 // measured resistance of flex sensor when straight
#define M_RING_FLEX_BENT 90000.0 // measured resistance of flex sensor when bent to ninety degrees

// Flex sensor - pinky
#define M_47K_RES_PINKY 47000.0 // measured resistance of 47K resistor
#define M_PINKY_FLEX_STRAIGHT 37300.0 // measured resistance of flex sensor when straight
#define M_PINKY_FLEX_BENT 90000.0 // measured resistance of flex sensor when bent to ninety degrees

// Force sensor - thumb
#define M_3K_RES_THUMB 3300.0 // measured resistance of 3.3K resistor

// Force sensor - index
#define M_3K_RES_INDEX 3300.0 // measured resistance of 3.3K resistor

#endif // TENACI_SENSOR_CONSTANTS_H
