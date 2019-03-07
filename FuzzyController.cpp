#include "FuzzyController.hpp"

FuzzyController::FuzzyController(float *index_flex_ptr, float *middle_flex_ptr, float *pinky_flex_ptr, float *thumb_force_ptr, float *index_force_ptr)
{
    this->index_flex_ptr = index_flex_ptr;
    this->middle_flex_ptr = middle_flex_ptr;
    this->pinky_flex_ptr = pinky_flex_ptr;
    this->thumb_force_ptr = thumb_force_ptr;
    this->index_force_ptr = index_force_ptr;

    fuzzy = new Fuzzy();

    // input sets for flex sensors
    indexNotFlexed = new FuzzySet(0, 0, 12.5, 25);
    indexPartiallyFlexed = new FuzzySet(0, 12.5, 37.5, 50);
    indexHalfFlexed = new FuzzySet(25, 37.5, 62.5, 75);
    indexMostlyFlexed = new FuzzySet(50, 62.5, 87.5, 100);
    indexFullyFlexed = new FuzzySet(75, 87.5, 100, 100);

    middleNotFlexed = new FuzzySet(0, 0, 12.5, 25);
    middlePartiallyFlexed = new FuzzySet(0, 12.5, 37.5, 50);
    middleHalfFlexed = new FuzzySet(25, 37.5, 62.5, 75);
    middleMostlyFlexed = new FuzzySet(50, 62.5, 87.5, 100);
    middleFullyFlexed = new FuzzySet(75, 87.5, 100, 100);

    pinkyNotFlexed = new FuzzySet(0, 0, 12.5, 25);
    pinkyPartiallyFlexed = new FuzzySet(0, 12.5, 37.5, 50);
    pinkyHalfFlexed = new FuzzySet(25, 37.5, 62.5, 75);
    pinkyMostlyFlexed = new FuzzySet(50, 62.5, 87.5, 100);
    pinkyFullyFlexed = new FuzzySet(75, 87.5, 100, 100);

    // input sets for force sensor
    thumbNoForce = new FuzzySet(0, 0, 350, 700);
    thumbLightForce = new FuzzySet(0, 350, 1050, 1400);
    thumbMediumForce = new FuzzySet(700, 1050, 1750, 2100);
    thumbHighForce = new FuzzySet(1400, 1750, 2100, 2100);

    indexNoForce = new FuzzySet(0, 0, 350, 700);
    indexLightForce = new FuzzySet(0, 350, 1050, 1400);
    indexMediumForce = new FuzzySet(700, 1050, 1750, 2100);
    indexHighForce = new FuzzySet(1400, 1750, 2100, 2100);

    // output sets for thumb flex sensor
    thumbNotFlexed = new FuzzySet(0, 0, 12.5, 25);
    thumbPartiallyFlexed = new FuzzySet(0, 12.5, 37.5, 50);
    thumbHalfFlexed = new FuzzySet(25, 37.5, 62.5, 75);
    thumbMostlyFlexed = new FuzzySet(50, 62.5, 87.5, 100);
    thumbFullyFlexed = new FuzzySet(75, 87.5, 100, 100);

    // assign input sets to inputs

    // index flex
    index_flex_input = new FuzzyInput(INDEX_FLEX_INPUT_INDEX);

    index_flex_input->addFuzzySet(indexNotFlexed);
    index_flex_input->addFuzzySet(indexPartiallyFlexed);
    index_flex_input->addFuzzySet(indexHalfFlexed);
    index_flex_input->addFuzzySet(indexMostlyFlexed);
    index_flex_input->addFuzzySet(indexFullyFlexed);
    fuzzy->addFuzzyInput(index_flex_input);

    // middle flex
    middle_flex_input = new FuzzyInput(MIDDLE_FLEX_INPUT_INDEX);

    middle_flex_input->addFuzzySet(middleNotFlexed);
    middle_flex_input->addFuzzySet(middlePartiallyFlexed);
    middle_flex_input->addFuzzySet(middleHalfFlexed);
    middle_flex_input->addFuzzySet(middleMostlyFlexed);
    middle_flex_input->addFuzzySet(middleFullyFlexed);
    fuzzy->addFuzzyInput(middle_flex_input);

    // pinky flex
    pinky_flex_input = new FuzzyInput(PINKY_FLEX_INPUT_INDEX);

    pinky_flex_input->addFuzzySet(pinkyNotFlexed);
    pinky_flex_input->addFuzzySet(pinkyPartiallyFlexed);
    pinky_flex_input->addFuzzySet(pinkyHalfFlexed);
    pinky_flex_input->addFuzzySet(pinkyMostlyFlexed);
    pinky_flex_input->addFuzzySet(pinkyFullyFlexed);
    fuzzy->addFuzzyInput(pinky_flex_input);

    // thumb force
    thumb_force_input = new FuzzyInput(THUMB_FORCE_INPUT_INDEX);

    thumb_force_input->addFuzzySet(thumbNoForce);
    thumb_force_input->addFuzzySet(thumbLightForce);
    thumb_force_input->addFuzzySet(thumbMediumForce);
    thumb_force_input->addFuzzySet(thumbHighForce);
    fuzzy->addFuzzyInput(thumb_force_input);

    // index force
    index_force_input = new FuzzyInput(INDEX_FORCE_INPUT_INDEX);

    index_force_input->addFuzzySet(indexNoForce);
    index_force_input->addFuzzySet(indexLightForce);
    index_force_input->addFuzzySet(indexMediumForce);
    index_force_input->addFuzzySet(indexHighForce);
    fuzzy->addFuzzyInput(index_force_input);

    // Add outputs
    thumb_flex_output = new FuzzyOutput(THUMB_FLEX_OUTPUT_INDEX);

    thumb_flex_output->addFuzzySet(thumbNotFlexed);
    thumb_flex_output->addFuzzySet(thumbPartiallyFlexed);
    thumb_flex_output->addFuzzySet(thumbHalfFlexed);
    thumb_flex_output->addFuzzySet(thumbMostlyFlexed);
    thumb_flex_output->addFuzzySet(thumbFullyFlexed);
    fuzzy->addFuzzyOutput(thumb_flex_output);

    // Build fuzzy rules

    //
}

float FuzzyController::getThumbOutput()
{
    fuzzy->setInput(INDEX_FLEX_INPUT_INDEX, *index_flex_ptr);
    fuzzy->setInput(MIDDLE_FLEX_INPUT_INDEX, *middle_flex_ptr);
    fuzzy->setInput(PINKY_FLEX_INPUT_INDEX, *pinky_flex_ptr);
    fuzzy->setInput(THUMB_FORCE_INPUT_INDEX, *thumb_force_ptr);
    fuzzy->setInput(INDEX_FORCE_INPUT_INDEX, *index_force_ptr);

    fuzzy->fuzzify();
    return fuzzy->defuzzify(THUMB_FLEX_OUTPUT_INDEX);
}
