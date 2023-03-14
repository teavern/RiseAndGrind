#include "talisman.h"

Talisman::Talisman()
{
    skills = map<qint16, qint16>();
    slotA = 0;
    slotB = 0;
    slotC = 0;

    decoA = 0;
    decoB = 0;
    decoC = 0;
}

Talisman::Talisman(map<qint16, qint16> skillList, qint16 slotALevel, qint16 slotBLevel, qint16 slotCLevel) {
    skills = skillList;
    slotA = slotALevel;
    slotB = slotBLevel;
    slotC = slotCLevel;

    decoA = 0;
    decoB = 0;
    decoC = 0;
}

int Talisman::addDecoration(Decoration * d, qint16 decoSlot) {
    switch (decoSlot) {
    case 0:
        if (slotA >= d->getDecoLevel()) {
            decoA = d;
            qDebug("Appended decoration %p to slot A", (void *) d);
            return 0;
        } else {
            qDebug("Slot A level is less than decoration %p needs", (void *) d);
            return -2;
        }
        break;
    case 1:
        if (slotB >= d->getDecoLevel()) {
            decoB = d;
            qDebug("Appended decoration %p to slot B", (void *) d);
            return 0;
        } else {
            qDebug("Slot B level is less than decoration %p needs", (void *) d);
            return -2;
        }
        break;
    case 2:
        if (slotC >= d->getDecoLevel()) {
            decoC = d;
            qDebug("Appended decoration %p to slot C", (void *) d);
            return 0;
        } else {
            qDebug("Slot C level is less than decoration %p needs", (void *) d);
            return -2;
        }
        break;
    }
    qDebug("Decoration %p tried to be applied to an invalid slot", (void *) d);
    return -1;
}

map<qint16, qint16> Talisman::getSkillLevels() {
    // get a copy of the already existing skill map
    map<qint16, qint16> skillMap = skills;

    // increment decoration levels
    if (skillMap.count(decoA->getDecoSkill()->GetSkillId()) > 0) {
        skillMap[decoA->getDecoSkill()->GetSkillId()] += 1;
    } else {
        skillMap[decoA->getDecoSkill()->GetSkillId()] = 1;
    }

    if (skillMap.count(decoB->getDecoSkill()->GetSkillId()) > 0) {
        skillMap[decoB->getDecoSkill()->GetSkillId()] += 1;
    } else {
        skillMap[decoB->getDecoSkill()->GetSkillId()] = 1;
    }

    if (skillMap.count(decoC->getDecoSkill()->GetSkillId()) > 0) {
        skillMap[decoC->getDecoSkill()->GetSkillId()] += 1;
    } else {
        skillMap[decoC->getDecoSkill()->GetSkillId()] = 1;
    }
    return skillMap;
}
