#include "fuzzycontroller.h"

#include <FuzzyComposition.h>
#include <FuzzyIO.h>
#include <FuzzyInput.h>
#include <FuzzyOutput.h>
#include <FuzzyRule.h>
#include <FuzzyRuleAntecedent.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzySet.h>

FuzzyController::FuzzyController()
{
    setup();
}

void FuzzyController::setup()
{
    // Setting FuzzyInput position
    FuzzyInput* position = new FuzzyInput(1);

    // Position negative
    FuzzySet* negative = new FuzzySet(-10, -10, -10, 0);
    position->addFuzzySet(negative);

    // Position center
    FuzzySet* center = new FuzzySet(-10, 0, 0, 10);
    position->addFuzzySet(center);

    // Position positive
    FuzzySet* positive = new FuzzySet(0, 10, 10, 10);
    position->addFuzzySet(positive);

    m_fuzzy.addFuzzyInput(position);

    // Setting FuzzyOutput direction
    FuzzyOutput* direction = new FuzzyOutput(1);

    FuzzySet* left = new FuzzySet(-50, -50, -50, 0);
    direction->addFuzzySet(left);

    FuzzySet* forward = new FuzzySet(-50, 0, 0, 50);
    direction->addFuzzySet(forward);

    FuzzySet* right = new FuzzySet(0, 50, 50, 50);
    direction->addFuzzySet(right);

    m_fuzzy.addFuzzyOutput(direction);

    // Setting Rules
    // 1 - If position is negative then turn left
    FuzzyRuleAntecedent* ifPositionNegative = new FuzzyRuleAntecedent();
    ifPositionNegative->joinSingle(negative);
    FuzzyRuleConsequent* thenTurnLeft = new FuzzyRuleConsequent();
    thenTurnLeft->addOutput(left);

    FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifPositionNegative, thenTurnLeft);
    m_fuzzy.addFuzzyRule(fuzzyRule01);

    // 1 - If position is centered then go forward
    FuzzyRuleAntecedent* ifPositionCenter = new FuzzyRuleAntecedent();
    ifPositionCenter->joinSingle(center);
    FuzzyRuleConsequent* thenGoForward = new FuzzyRuleConsequent();
    thenGoForward->addOutput(forward);

    FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifPositionCenter, thenGoForward);
    m_fuzzy.addFuzzyRule(fuzzyRule02);

    // 1 - If position is positive then turn right
    FuzzyRuleAntecedent* ifPositionPositive = new FuzzyRuleAntecedent();
    ifPositionPositive->joinSingle(positive);
    FuzzyRuleConsequent* thenTurnRight = new FuzzyRuleConsequent();
    thenTurnRight->addOutput(right);

    FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifPositionPositive, thenTurnRight);
    m_fuzzy.addFuzzyRule(fuzzyRule03);
}

float FuzzyController::evaluate(const float& input)
{
    m_fuzzy.setInput(1, input);

    m_fuzzy.fuzzify();

    return m_fuzzy.defuzzify(1);
}
