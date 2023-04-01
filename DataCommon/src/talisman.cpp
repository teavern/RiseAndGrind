#include "talisman.h"

Talisman::Talisman()
{
    skills = map<qint16, qint16>();
    slotA = 0;
    slotB = 0;
    slotC = 0;
}

Talisman::Talisman(map<qint16, qint16> skillList, qint16 slotALevel, qint16 slotBLevel, qint16 slotCLevel) {
    skills = skillList;
    slotA = slotALevel;
    slotB = slotBLevel;
    slotC = slotCLevel;
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

QJsonObject Talisman::toJSON() {
    QJsonObject obj;
    obj["slotLevelA"] = this->slotA;
    obj["slotLevelB"] = this->slotB;
    obj["slotLevelC"] = this->slotC;
    if (this->skills.size() > 0) {
        QJsonArray arr;
        for (map<qint16, qint16>::iterator it = this->skills.begin(); it != this->skills.end(); it++) {
            QJsonObject o;
            o["skillID"] = it->first;
            o["skillLevel"] = it->second;
            arr.append(o);
        }
        obj["skills"] = arr;
    }
    return obj;
}
