#ifndef DECORATION_H
#define DECORATION_H

#include <QObject>
#include <QJsonObject>

#include "skill.h"
/**
 * @brief Represents a single decoration in the game
 */
class Decoration
{
public:
    explicit Decoration();
    /**
     * @brief Decoration constructor
     * @param decoId ID of the decoration from CSV
     * @param slotLevel Slot level of the decoration (1, 2, 3)
     * @param skill Reference to the skill the decoration maps to
     * @param name Name of the decoration
     */
    Decoration(qint16 decoId, qint16 slotLevel, Skill & skill, QString name);
    qint16 getDecoLevel();
    /**
     * @brief Gets the reference to the skill the deco points to
     * @return
     */
    Skill * getDecoSkill();
    /**
     * @brief Converts the instance of the object into JSON representation, setting its skill to the skill ID
     * @return
     */
    QJsonObject ToJSON();
    /**
     * @brief Loads new skill from JSON
     * @param json JSON object to load
     * @param loadedSkills Vector of skills previoulsy loaded to match the decos skill with
     */
    void FromJSON(QJsonObject &json, std::vector<Skill *> &loadedSkills);
    QString ToString();
    ~Decoration();
private:
    /**
     * @brief Decoration ID (internal use for searching)
     */
    qint16 decoID;
    /**
     * @brief Pointer to the skill the decoration has
     */
    Skill * skill;
    /**
     * @brief Level of the decoration (1-3)
     */
    qint16 decoLevel;
    /**
     * @brief Name of the decoration
     */
    QString name;
};

#endif // DECORATION_H
