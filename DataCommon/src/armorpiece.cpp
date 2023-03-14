#include "armorpiece.h"

ArmorPiece::ArmorPiece()
{
    this->defenceMin = 0;
    this->defenceMax = 0;
    this->fireRes = 0;
    this->waterRes = 0;
    this->lightRes = 0;
    this->iceRes = 0;
    this->dragonRes = 0;
}
ArmorPiece::ArmorPiece(qint16 id,
                       QString name,
                       ARMOR_TYPE type,
                       vector<qint16> skillLevels,
                       vector<qint16> decoSlots,
                       vector<Skill *> skills) {
    this->armorID = id;
    this->name = name;
    this->armorType = type;

    // Load skill values into map
    for (int i = 0; i < (int) skills.size(); i++) {
        this->armorSkills[skills.at(i)] = skillLevels.at(i);
    }

    this->decoSlotLevelA = decoSlots[0];
    this->decoSlotLevelB = decoSlots[1];
    this->decoSlotLevelC = decoSlots[2];
    this->skillList = skills;

    this->defenceMin = 0;
    this->defenceMax = 0;
    this->fireRes = 0;
    this->waterRes = 0;
    this->lightRes = 0;
    this->iceRes = 0;
    this->dragonRes = 0;
}

qint16 ArmorPiece::GetId() {
    return this->armorID;
}

bool ArmorPiece::ContainsSkill(Skill * s) {
    if (this->armorSkills.count(s) > 0) {
        return true;
    }
    return false;
}
QString ArmorPiece::GetName() {
    return this->name;
}

std::map<Skill *, qint16> ArmorPiece::getSkills() {
    return this->armorSkills;
}

qint16 ArmorPiece::getSlotLevelA() {
    return this->decoSlotLevelA;
}

qint16 ArmorPiece::getSlotLevelB() {
    return this->decoSlotLevelB;
}

qint16 ArmorPiece::getSlotLevelC() {
    return this->decoSlotLevelC;
}
