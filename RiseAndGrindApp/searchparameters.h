#ifndef SEARCHPARAMETERS_H
#define SEARCHPARAMETERS_H

#include <QObject>
#include <QMap>
#include <vector>
#include "skill.h"

/**
 * @brief Data structure holding all the parameters for searching for a set
 */
using namespace::std;
class SearchParameters : public QObject
{
    Q_OBJECT
public:
    explicit SearchParameters(QObject *parent = nullptr);
    void AddSkill(qint16 id, qint16 value);
    /**
     * @brief Generic of the desired skill IDs (key) and the desired skill level (Value);
     * @return
     */
    std::map<qint16, qint16> skillMap;
    vector<int> skillIds;
    vector<int> skillLevels;
signals:

};

#endif // SEARCHPARAMETERS_H
