#include "armorset.h"

ArmorSet::ArmorSet()
{
    this->headArmor = FittedArmorPiece();
    this->bodyArmor = FittedArmorPiece();
    this->armArmor = FittedArmorPiece();
    this->waistArmor = FittedArmorPiece();
    this->legArmor = FittedArmorPiece();
}

ArmorSet::ArmorSet(FittedArmorPiece &head,
                   FittedArmorPiece &body,
                   FittedArmorPiece &arm,
                   FittedArmorPiece &waist,
                   FittedArmorPiece &leg,
                   Talisman * talisman) {
    ArmorSet::headArmor = head;
    ArmorSet::bodyArmor = body;
    ArmorSet::armArmor = arm;
    ArmorSet::waistArmor = waist;
    ArmorSet::legArmor = leg;
    ArmorSet::talisman = talisman;
}
FittedArmorPiece ArmorSet::getHeadPiece() {
    return ArmorSet::headArmor;
}
FittedArmorPiece ArmorSet::getBodyPiece() {
    return ArmorSet::bodyArmor;
}
FittedArmorPiece ArmorSet::getLegPiece() {
    return ArmorSet::legArmor;
}
FittedArmorPiece ArmorSet::getWaistPiece() {
    return ArmorSet::waistArmor;
}
FittedArmorPiece ArmorSet::getArmPiece() {
    return ArmorSet::armArmor;
}

vector<FittedArmorPiece *> ArmorSet::getArmorList() {
    vector<FittedArmorPiece *> v = vector<FittedArmorPiece *>();

    v.push_back(&headArmor);
    v.push_back(&bodyArmor);
    v.push_back(&legArmor);
    v.push_back(&waistArmor);
    v.push_back(&armArmor);

    return v;
}

map<qint16, qint16> ArmorSet::getSkillLevels() {
    map<qint16, qint16> skillMap = map<qint16, qint16>();
    // Go through all armor pieces
    for (FittedArmorPiece * p : ArmorSet::getArmorList()) {
        // Get the skills
        map<qint16, qint16> armorSkills = p->GetArmorPiece()->getSkills();
        // add values of each skill to map
        for (auto skill : armorSkills) {
            if (skillMap.count(skillMap[skill.first])) {
                // add current value if exists
                skillMap[skill.first] = skillMap[skill.first] + skill.second;
            } else {
                // otherwise create new entry
                skillMap[skill.first] = skill.second;
            }
        }

        // Iterate through decorations
        // TODO: as of current, decorations only apply a single skill value
        // This will definitely change in sunbreak

        // TODO: Refactor this to reuse code
        // Deco A
        Decoration * d = p->getDecoA();
        qint16 decoSkill = 0;
        // Pointers have a possibility of being null
        if (d != NULL) {
            decoSkill = d->getDecoSkill()->GetSkillId();
            if (skillMap.count(skillMap[decoSkill])) {
                // add current value if exists
                skillMap[decoSkill] = skillMap[decoSkill] + 1;
            } else {
                // otherwise create new entry
                skillMap[decoSkill] = 1;
            }
        }

        // Deco B
        d = p->getDecoB();
        if (d != NULL) {
            decoSkill = d->getDecoSkill()->GetSkillId();
            if (skillMap.count(skillMap[decoSkill])) {
                // add current value if exists
                skillMap[decoSkill] = skillMap[decoSkill] + 1;
            } else {
                // otherwise create new entry
                skillMap[decoSkill] = 1;
            }
        }

        // Deco C
        d = p->getDecoC();
        if (d != NULL) {
            decoSkill = d->getDecoSkill()->GetSkillId();
            if (skillMap.count(skillMap[decoSkill])) {
                // add current value if exists
                skillMap[decoSkill] = skillMap[decoSkill] + 1;
            } else {
                // otherwise create new entry
                skillMap[decoSkill] = 1;
            }
        }

        // TODO: Implement talismans
    }
    return skillMap;

}
