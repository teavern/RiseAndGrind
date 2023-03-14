#include "searchparameters.h"

SearchParameters::SearchParameters(QObject *parent) : QObject(parent)
{

}

void SearchParameters::AddSkill(qint16 id, qint16 value) {
    qDebug("Added skill to find.");
    this->skillMap[id] = value;
    this->skillIds.push_back(id);
    this->skillLevels.push_back(value);
}
