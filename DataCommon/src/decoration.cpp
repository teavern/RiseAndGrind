#include "decoration.h"

Decoration::Decoration() {

}
Decoration::Decoration(qint16 decoId, qint16 slotLevel, Skill & skill, QString name) {
    this->decoID = decoId;
    this->decoLevel = slotLevel;
    this->skill = &skill;
    this->name = name;
}

Decoration::~Decoration() {

}

qint16 Decoration::getDecoLevel() {
    return decoLevel;
}

Skill * Decoration::getDecoSkill() {
    return skill;
}
