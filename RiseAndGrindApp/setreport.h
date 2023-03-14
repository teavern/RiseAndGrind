#ifndef SETREPORT_H
#define SETREPORT_H
#include <map>
#include <QObject>
#include "armorset.h"

/**
 * @brief Represents a report on an armor set that contains its total skills
 */
class SetReport
{
public:
    SetReport(ArmorSet & armorSet);
    std::map<qint16, qint16> getSetTotals();
    /**
     * @brief Clears all memory allocated by the object only
     */
    void clear();
private:
    /**
     * @brief Set skill totals mapping the skill's ID to its total value
     */
    std::map<qint16, qint16> setTotal;
    /**
     * @brief Pointer to the armorset to generate a report from
     */
    ArmorSet * armorSet;
    /**
     * @brief Goes through an armor set and caluclates the total skills
     */
    void calculateSetTotals();
};

#endif // SETREPORT_H
