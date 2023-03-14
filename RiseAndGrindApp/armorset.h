#ifndef ARMORSET_H
#define ARMORSET_H

#include <QObject>
#include <vector>
#include "armorpiece.h"
#include "decoration.h"
#include "talisman.h"
#include "weapon.h"
#include "fittedarmorpiece.h"

using namespace::std;
/**
 * @brief Data class for a whole armor set.
 */
class ArmorSet
{
public:
    ArmorSet();
    ArmorSet(FittedArmorPiece &head,
              FittedArmorPiece &body,
              FittedArmorPiece &arm,
              FittedArmorPiece &waist,
              FittedArmorPiece &leg,
              Talisman * talisman);
    /**
     * @brief Add a decoration to the set list
     * @param Reference to a decoration object
     */
    void appendDecoration(Decoration &d);

    FittedArmorPiece getHeadPiece();
    FittedArmorPiece getBodyPiece();
    FittedArmorPiece getArmPiece();
    FittedArmorPiece getWaistPiece();
    FittedArmorPiece getLegPiece();

    /**
     * @brief Gets all the armor pieces as a convenient list
     * @return
     */
    vector<FittedArmorPiece *> getArmorList();
    /**
     * @brief Appends skillIDs across the armorset along with total skill level
     * @return
     */
    map<qint16, qint16> getSkillLevels();

private:
    FittedArmorPiece headArmor;
    FittedArmorPiece bodyArmor;
    FittedArmorPiece armArmor;
    FittedArmorPiece waistArmor;
    FittedArmorPiece legArmor;

    Talisman * talisman;
};

#endif // ARMORSET_H
