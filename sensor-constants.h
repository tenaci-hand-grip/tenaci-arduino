#ifndef TENACI_SENSOR_CONSTANTS_H
#define TENACI_SENSOR_CONSTANTS_H

#include "pins.h"

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

/*


// finger/thumb structs

// flex sensor structs
finger_sensor_struct thumb_flex_t = {
        .pin = FLEX_THUMB_PIN,
        .pvalue = &thumb_flex_value,
        .resistance = M_47K_RES_THUMB,
        .resistance_straight = M_THUMB_FLEX_STRAIGHT,
        .resistance_bent = M_THUMB_FLEX_BENT};
finger_sensor_struct index_flex_t = {
        .pin = FLEX_INDEX_PIN,
        .pvalue = &index_flex_value,
        .resistance = M_47K_RES_INDEX,
        .resistance_straight = M_INDEX_FLEX_STRAIGHT,
        .resistance_bent = M_INDEX_FLEX_BENT};
finger_sensor_struct middle_flex_t = {
        .pin = FLEX_MIDDLE_PIN,
        .pvalue = &middle_flex_value,
        .resistance = M_47K_RES_MIDDLE,
        .resistance_straight = M_MIDDLE_FLEX_STRAIGHT,
        .resistance_bent = M_MIDDLE_FLEX_BENT};
finger_sensor_struct ring_flex_t = {
        .pin = FLEX_RING_PIN,
        .pvalue = &ring_flex_value,
        .resistance = M_47K_RES_RING,
        .resistance_straight = M_RING_FLEX_STRAIGHT,
        .resistance_bent = M_RING_FLEX_BENT};
finger_sensor_struct pinky_flex_t = {
        .pin = FLEX_PINKY_PIN,
        .pvalue = &pinky_flex_value,
        .resistance = M_47K_RES_PINKY,
        .resistance_straight = M_PINKY_FLEX_STRAIGHT,
        .resistance_bent = M_PINKY_FLEX_BENT};

// force sensor structs
finger_sensor_struct thumb_force_t = {
        .pin = FORCE_THUMB_PIN,
        .pvalue = &thumb_force_value,
        .resistance = M_3K_RES_THUMB};
finger_sensor_struct index_force_t = {
        .pin = FORCE_INDEX_PIN,
        .pvalue = &index_force_value,
        .resistance = M_3K_RES_INDEX};
*/

#endif // TENACI_SENSOR_CONSTANTS_H
