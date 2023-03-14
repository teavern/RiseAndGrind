#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
/**
 * @brief Class representing a weapon
 */
class Weapon
{
public:
    enum ELEMENT {
        FIRE,
        WATER,
        ICE,
        ELECTRICITY,
        DRAGON,
        BLAST,
        POITSON,
        SLEEP,
        PARALYSIS,
        NONE
    };
    enum WEAPON_TYPE {
        GREAT_SWORD,
        LONG_SWORD,
        SWORD_AND_SHIELD,
        DUAL_BLADES,
        LANCE,
        GUNLANCE,
        HAMMER,
        HUNTING_HORN,
        SWITCH_AXE,
        CHARGE_BLADE,
        INSECT_GLAIVE,
        LIGHT_BOWGUN,
        HEAVY_BOWGUN,
        BOW
    };

    explicit Weapon();
private:
    /**
     * @brief Type of the weapon
     */
    WEAPON_TYPE type;
    /**
     * @brief Name of the weapon
     */
    QString name;
    /**
     * @brief Decoration slot levels
     */
    qint16 wepSlots[3];
    /**
     * @brief Raw weapon attack
     */
    qint16 raw;
    /**
     * @brief Elemental Raw
     */
    qint16 elementRaw;
    /**
     * @brief Element of the weapon
     */
    ELEMENT element;
signals:

};

#endif // WEAPON_H
