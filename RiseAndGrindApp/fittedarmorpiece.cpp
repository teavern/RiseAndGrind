#include "fittedarmorpiece.h"

FittedArmorPiece::FittedArmorPiece()
{
    this->decorations = std::vector<Decoration>();
    this->decoA = NULL;
    this->decoB = NULL;
    this->decoC = NULL;
}

FittedArmorPiece::FittedArmorPiece(ArmorPiece * armor) {
    this->armorPiece = armor;
    this->decorations = std::vector<Decoration>();
    this->decoA = NULL;
    this->decoB = NULL;
    this->decoC = NULL;
}

void FittedArmorPiece::PutDecoration(qint16 slot, Decoration  * d) {
    // Check if the slot level matches the desired decoration's level
    // empty slots should be level zero
    qint16 slotLevel = 0;
    switch (slot) {
    case 0:
        slotLevel = this->armorPiece->getSlotLevelA();
        break;
    case 1:
        slotLevel = this->armorPiece->getSlotLevelB();
        break;
    case 2:
        slotLevel = this->armorPiece->getSlotLevelC();
        break;
    }
    if (d->getDecoLevel() > slotLevel) {
        qDebug("Can not fit decoration! Level too high for slot!");
    } else {
        // Slot the decoration
        switch (slot) {
        case 0:
            this->decoA = d;
            break;
        case 1:
            this->decoB = d;
            break;
        case 2:
            this->decoC = d;
            break;
        }
        qDebug("Slotted the decoration into slot %d" , slot);
    }
}

ArmorPiece * FittedArmorPiece::GetArmorPiece() {
    return this->armorPiece;
}

Decoration * FittedArmorPiece::getDecoA() {
    return decoA;
}
Decoration * FittedArmorPiece::getDecoB() {
    return decoB;
}
Decoration * FittedArmorPiece::getDecoC() {
    return decoC;
}
