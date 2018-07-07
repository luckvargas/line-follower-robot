#ifndef FUZZYCONTROLLER_H
#define FUZZYCONTROLLER_H

#include "Fuzzy.h"

class FuzzyController {
public:
    FuzzyController();

    float evaluate(const float& input);

private:
    void setup();
    Fuzzy m_fuzzy;
    float m_lastInput;
};

#endif // FUZZYCONTROLLER_H
