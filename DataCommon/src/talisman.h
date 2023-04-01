#ifndef TALISMAN_H
#define TALISMAN_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
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
     * @brief Calculates the levels for each of the skills the decoration has
     * @return map<skill ID, skill level>
     */
    map<qint16, qint16> getSkillLevels();

    QJsonObject toJSON();
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
