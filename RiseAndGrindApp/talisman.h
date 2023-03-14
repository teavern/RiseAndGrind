#ifndef TALISMAN_H
#define TALISMAN_H

#include <QObject>
#include <vector>
#include "skill.h"
#include "decoration.h"

/**
 * @brief Represents a talisman with skills and deco slots
 */
using namespace::std;
class Talisman
{
public:
    /**
     * @brief General constructor
     */
    explicit Talisman();
    /**
     * @brief Talisman constructor
     * @param skillList Vector of skills that the talisman has
     * @param slotLevels Vector of ints that
     */
    explicit Talisman(map<qint16, qint16> skillList, qint16 slotALevel, qint16 slotBLevel, qint16 slotCLevel);
    /**
     * @brief Add a decoration to the selected decoration slot, zero indexed.
     * @param d Reference of the decoration from the database to add
     * @param decoSlot Slot, zero indexed, to apply the decoration too
     * @return 0 if successful, -1 if failed, -2 if deco level exceeds slot level.
     */
    int addDecoration(Decoration * d, qint16 decoSlot);
    /**
     * @brief Calculates the levels for each of the skills the decoration has
     * @return map<skill ID, skill level>
     */
    map<qint16, qint16> getSkillLevels();
private:
    /**
     * @brief Map of skills<skill Id, skill level> the talisman has
     */
    map<qint16, qint16> skills;

    /**
     * @brief Slot A max deco level
     */
    qint16 slotA;
    /**
     * @brief Slot B max deco level
     */
    qint16 slotB;
    /**
     * @brief Slot C max deco level
     */
    qint16 slotC;

    /**
     * @brief Slot A applied decoration
     */
    Decoration * decoA;
    /**
     * @brief Slot B applied decoration
     */
    Decoration * decoB;
    /**
     * @brief Slot C applied decoration
     */
    Decoration * decoC;

};

#endif // TALISMAN_H
