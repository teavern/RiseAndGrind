#ifndef SKILL_H
#define SKILL_H
#include <QObject>
#include <QJsonObject>

/**
 * @brief The Skill class
 */
class Skill
{
public:
    explicit Skill();
    Skill(qint16, qint16, QString, QString);
    Skill(qint16, qint16, QString);
    Skill(qint16 id, QString name);
    Skill(qint16 id);
    /**
     * @brief Instantiates a skill object from a json object
     * @param json
     */
    Skill(QJsonObject &json);
    /**
     * @brief Get the name of the skill
     * @return
     */
    QString GetSkillName();

    /**
     * @brief Get the ID of the skill
     * @return
     */
    qint16 GetSkillId();

    /**
     * @brief Gets the max level of the skill
     * @return
     */
    qint16 GetMaxSkillLevel();

    /**
     * @brief Converts the representation of this object to JSON
     * @return
     */
    QJsonObject ToJSON();
    /**
     * @brief Loads instance of object with data from JSON
     */
    void FromJSON(QJsonObject &json);
    /**
     * @brief Converts object to string
     * @return
     */
    QString ToString();
private:
    /**
     * @brief ID of the skill (internal use)
     */
    qint16 skillID;
    /**
     * @brief name
     * Name of the skill.
     */
    QString name;
    /**
     * @brief maxSkillLevel
     * Max skill level of the skill
     */
    qint16 maxSkillLevel;
    QString description;
};

#endif // SKILL_H
