#ifndef TENACI_FUZZY_CONTROLLER_H
#define TENACI_FUZZY_CONTROLLER_H

#include "Fuzzy.h"

#define INDEX_FLEX_INPUT_INDEX 1
#define MIDDLE_FLEX_INPUT_INDEX 2
#define PINKY_FLEX_INPUT_INDEX 3
#define THUMB_FORCE_INPUT_INDEX 4
#define INDEX_FORCE_INPUT_INDEX 5

#define THUMB_FLEX_OUTPUT_INDEX 1

struct fuzzy_set_t
{
    double a;
    double b;
    double c;
    double d;
};

class FuzzyController
{
public:
    FuzzyController(float *index_flex_ptr, float *middle_flex_ptr, float *pinky_flex_ptr, float *thumb_force_ptr, float *index_force_ptr);
    float getThumbOutput();

protected:
    float *index_flex_ptr;
    float *middle_flex_ptr;
    float *pinky_flex_ptr;
    float *thumb_force_ptr;
    float *index_force_ptr;

    Fuzzy *fuzzy;

    // fuzzy input/output sets for flex sensors
    FuzzySet *thumbNotFlexed;
    FuzzySet *thumbPartiallyFlexed;
    FuzzySet *thumbHalfFlexed;
    FuzzySet *thumbMostlyFlexed;
    FuzzySet *thumbFullyFlexed;

    FuzzySet *indexNotFlexed;
    FuzzySet *indexPartiallyFlexed;
    FuzzySet *indexHalfFlexed;
    FuzzySet *indexMostlyFlexed;
    FuzzySet *indexFullyFlexed;

    FuzzySet *middleNotFlexed;
    FuzzySet *middlePartiallyFlexed;
    FuzzySet *middleHalfFlexed;
    FuzzySet *middleMostlyFlexed;
    FuzzySet *middleFullyFlexed;

    FuzzySet *pinkyNotFlexed;
    FuzzySet *pinkyPartiallyFlexed;
    FuzzySet *pinkyHalfFlexed;
    FuzzySet *pinkyMostlyFlexed;
    FuzzySet *pinkyFullyFlexed;

    // fuzzy input sets for force sensor
    FuzzySet *thumbNoForce;
    FuzzySet *thumbLightForce;
    FuzzySet *thumbMediumForce;
    FuzzySet *thumbHighForce;

    FuzzySet *indexNoForce;
    FuzzySet *indexLightForce;
    FuzzySet *indexMediumForce;
    FuzzySet *indexHighForce;

    // inputs
    FuzzyInput *index_flex_input;
    FuzzyInput *middle_flex_input;
    FuzzyInput *pinky_flex_input;

    FuzzyInput *thumb_force_input;
    FuzzyInput *index_force_input;

    // outputs
    FuzzyOutput *thumb_flex_output;

    // fuzzy rules
    FuzzyRuleAntecedent *ifIndexNotFlexed;
    FuzzyRuleAntecedent *ifIndexPartiallyFlexed;
    FuzzyRuleAntecedent *ifIndexHalfFlexed;
    FuzzyRuleAntecedent *ifIndexMostlyFlexed;
    FuzzyRuleAntecedent *ifIndexFullyFlexed;

    FuzzyRuleAntecedent *ifPinkyNotFlexed;
    FuzzyRuleAntecedent *ifPinkyPartiallyFlexed;
    FuzzyRuleAntecedent *ifPinkyHalfFlexed;
    FuzzyRuleAntecedent *ifPinkyMostlyFlexed;
    FuzzyRuleAntecedent *ifPinkyFullyFlexed;

    FuzzyRuleAntecedent *ifThumbNoForce;
    FuzzyRuleAntecedent *ifThumbLightForce;
    FuzzyRuleAntecedent *ifThumbMediumForce;
    FuzzyRuleAntecedent *ifThumbHighForce;

    FuzzyRuleAntecedent *ifIndexNoForce;
    FuzzyRuleAntecedent *ifIndexLightForce;
    FuzzyRuleAntecedent *ifIndexMediumForce;
    FuzzyRuleAntecedent *ifIndexHighForce;


    FuzzyRuleAntecedent *ifIndexNotFlexedANDPinkyNotFlexed;
    FuzzyRuleAntecedent *ifThumbNoForceANDIndexNoForce;
    FuzzyRuleAntecedent *ifIndexNotFlexedANDPinkyNotFlexedANDThumbNoForceANDIndexNoForce;



    FuzzyRuleConsequent *thenThumbNotFlexed;
    FuzzyRuleConsequent *thenThumbPartiallyFlexed;
    FuzzyRuleConsequent *thenThumbHalfFlexed;
    FuzzyRuleConsequent *thenThumbMostlyFlexed;
    FuzzyRuleConsequent *thenThumbFullyFlexed;
};

#endif // TENACI_FUZZY_CONTROLLER_H
