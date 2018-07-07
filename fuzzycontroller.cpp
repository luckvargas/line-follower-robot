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
const int maxOutput = 200;
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

    // Setting FuzzyInput position
    FuzzyInput* last_position = new FuzzyInput(2);
    FuzzySet* dnegative = new FuzzySet(-10, -10, -10, 0);
    last_position->addFuzzySet(dnegative);
    FuzzySet* dcenter = new FuzzySet(-10, 0, 0, 10);
    last_position->addFuzzySet(dcenter);
    FuzzySet* dpositive = new FuzzySet(0, 10, 10, 10);
    last_position->addFuzzySet(dpositive);

    m_fuzzy.addFuzzyInput(last_position);

    // Setting FuzzyOutput direction
    FuzzyOutput* direction = new FuzzyOutput(1);

    FuzzySet* left = new FuzzySet(-maxOutput, -maxOutput, -maxOutput, 0);
    direction->addFuzzySet(left);

    FuzzySet* forward = new FuzzySet(-maxOutput, 0, 0, maxOutput);
    direction->addFuzzySet(forward);

    FuzzySet* right = new FuzzySet(0, maxOutput, maxOutput, maxOutput);
    direction->addFuzzySet(right);

    m_fuzzy.addFuzzyOutput(direction);

    // Setting Rules
    /******************************** positionNegative **************************/
    // 1 - If position is negative and last position is negative then turn left //
    FuzzyRuleAntecedent* ifPositionNegative1 = new FuzzyRuleAntecedent();
    ifPositionNegative1->joinWithAND(negative, dnegative);
    FuzzyRuleConsequent* thenTurnLeft1 = new FuzzyRuleConsequent();
    thenTurnLeft1->addOutput(left);

    FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifPositionNegative1, thenTurnLeft1);
    m_fuzzy.addFuzzyRule(fuzzyRule01);
    //////////////////////////////////////////////////////////////////////////////
    // 2 - If position is negative and last position is center then turn left //
    FuzzyRuleAntecedent* ifPositionNegative2 = new FuzzyRuleAntecedent();
    ifPositionNegative2->joinWithAND(negative, dcenter);
    FuzzyRuleConsequent* thenTurnLeft2 = new FuzzyRuleConsequent();
    thenTurnLeft2->addOutput(left);

    FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifPositionNegative2, thenTurnLeft2);
    m_fuzzy.addFuzzyRule(fuzzyRule02);
    //////////////////////////////////////////////////////////////////////////////
    // 3 - If position is negative and last position is positive then turn left //
    FuzzyRuleAntecedent* ifPositionNegative3 = new FuzzyRuleAntecedent();
    ifPositionNegative3->joinWithAND(negative, dpositive);
    FuzzyRuleConsequent* thenTurnLeft3 = new FuzzyRuleConsequent();
    thenTurnLeft3->addOutput(left);

    FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifPositionNegative3, thenTurnLeft3);
    m_fuzzy.addFuzzyRule(fuzzyRule03);
    //////////////////////////////////////////////////////////////////////////////
    /******************************** positionCenter **************************/
    // 4 - If position is center and last position is negative then turn left //
    FuzzyRuleAntecedent* ifPositionCenter1 = new FuzzyRuleAntecedent();
    ifPositionCenter1->joinWithAND(center, dnegative);
    FuzzyRuleConsequent* thenTurnLeft0 = new FuzzyRuleConsequent();
    thenTurnLeft0->addOutput(left);

    FuzzyRule* fuzzyRule04 = new FuzzyRule(4, ifPositionCenter1, thenTurnLeft0);
    m_fuzzy.addFuzzyRule(fuzzyRule04);
    //////////////////////////////////////////////////////////////////////////////
    // 5 - If position is center and last position is center then turn left //
    FuzzyRuleAntecedent* ifPositionCenter2 = new FuzzyRuleAntecedent();
    ifPositionCenter2->joinWithAND(center, dcenter);
    FuzzyRuleConsequent* thenGoForward = new FuzzyRuleConsequent();
    thenGoForward->addOutput(forward);

    FuzzyRule* fuzzyRule05 = new FuzzyRule(5, ifPositionCenter2, thenGoForward);
    m_fuzzy.addFuzzyRule(fuzzyRule05);
    //////////////////////////////////////////////////////////////////////////////
    // 6 - If position is center and last position is positive then turn left //
    FuzzyRuleAntecedent* ifPositionCenter3 = new FuzzyRuleAntecedent();
    ifPositionCenter3->joinWithAND(center, dpositive);
    FuzzyRuleConsequent* thenTurnRight0 = new FuzzyRuleConsequent();
    thenTurnRight0->addOutput(right);

    FuzzyRule* fuzzyRule06 = new FuzzyRule(6, ifPositionCenter3, thenTurnRight0);
    m_fuzzy.addFuzzyRule(fuzzyRule06);
    //////////////////////////////////////////////////////////////////////////////
    /******************************** positionPositive **************************/
    // 4 - If position is center and last position is negative then turn left //
    FuzzyRuleAntecedent* ifPositionRight1 = new FuzzyRuleAntecedent();
    ifPositionRight1->joinWithAND(positive, dnegative);
    FuzzyRuleConsequent* thenTurnRight1 = new FuzzyRuleConsequent();
    thenTurnRight1->addOutput(right);

    FuzzyRule* fuzzyRule07 = new FuzzyRule(7, ifPositionRight1, thenTurnRight1);
    m_fuzzy.addFuzzyRule(fuzzyRule07);
    //////////////////////////////////////////////////////////////////////////////
    // 5 - If position is center and last position is center then turn left //
    FuzzyRuleAntecedent* ifPositionRight2 = new FuzzyRuleAntecedent();
    ifPositionRight2->joinWithAND(positive, dcenter);
    FuzzyRuleConsequent* thenTurnRight2 = new FuzzyRuleConsequent();
    thenTurnRight2->addOutput(right);

    FuzzyRule* fuzzyRule08 = new FuzzyRule(8, ifPositionRight2, thenTurnRight2);
    m_fuzzy.addFuzzyRule(fuzzyRule08);
    //////////////////////////////////////////////////////////////////////////////
    // 6 - If position is center and last position is positive then turn left //
    FuzzyRuleAntecedent* ifPositionRight3 = new FuzzyRuleAntecedent();
    ifPositionRight3->joinWithAND(positive, dpositive);
    FuzzyRuleConsequent* thenTurnRight3 = new FuzzyRuleConsequent();
    thenTurnRight3->addOutput(right);

    FuzzyRule* fuzzyRule09 = new FuzzyRule(9, ifPositionRight3, thenTurnRight3);
    m_fuzzy.addFuzzyRule(fuzzyRule09);
    //////////////////////////////////////////////////////////////////////////////

    //    FuzzyRuleAntecedent* ifPositionNegative = new FuzzyRuleAntecedent();
    //    ifPositionNegative->joinSingle(negative);
    //    FuzzyRuleConsequent* thenTurnLeft = new FuzzyRuleConsequent();
    //    thenTurnLeft->addOutput(left);
    //    FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifPositionNegative, thenTurnLeft);
    //    m_fuzzy.addFuzzyRule(fuzzyRule01);

    //    FuzzyRuleAntecedent* ifPositionCenter = new FuzzyRuleAntecedent();
    //    ifPositionCenter->joinSingle(center);
    //    FuzzyRuleConsequent* thenGoForward = new FuzzyRuleConsequent();
    //    thenGoForward->addOutput(forward);
    //    FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifPositionCenter, thenGoForward);
    //    m_fuzzy.addFuzzyRule(fuzzyRule02);

    //    FuzzyRuleAntecedent* ifPositionPositive = new FuzzyRuleAntecedent();
    //    ifPositionPositive->joinSingle(positive);
    //    FuzzyRuleConsequent* thenTurnRight = new FuzzyRuleConsequent();
    //    thenTurnRight->addOutput(right);

    //    FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifPositionPositive, thenTurnRight);
    //    m_fuzzy.addFuzzyRule(fuzzyRule03);
}

float FuzzyController::evaluate(const float& input)
{
    m_fuzzy.setInput(1, input);
    m_fuzzy.setInput(2, m_lastInput);

    m_lastInput = input;
    m_fuzzy.fuzzify();

    return m_fuzzy.defuzzify(1);
}
