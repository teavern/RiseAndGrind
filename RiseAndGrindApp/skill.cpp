#include "skill.h"

Skill::Skill()
{

}
Skill::Skill(qint16 id, QString name) {
    this->name = name;
    this->skillID = id;
    this->maxSkillLevel = 7;
}

Skill::Skill(qint16 id) {
    this->name = "";
    this->skillID = id;
    this->maxSkillLevel = 7;
}
QString Skill::GetSkillName() {
    return this->name;
}

qint16 Skill::GetSkillId() {
    return this->skillID;
}
