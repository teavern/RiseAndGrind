#include "setreport.h"

SetReport::SetReport(ArmorSet & armorSet) {
    SetReport::armorSet = & armorSet;
    SetReport::setTotal = std::map<qint16, qint16>();
    // Run the report
    calculateSetTotals();
}

void SetReport::calculateSetTotals() {

    auto skills = SetReport::armorSet->getSkillLevels();

    SetReport::setTotal = skills;
}

std::map<qint16, qint16> SetReport::getSetTotals() {
    return SetReport::setTotal;
}
