#ifndef ARMORPIECE_H
#define ARMORPIECE_H

#include <QVector>
#include <vector>
#include <map>
#include "skill.h"
#include "decoration.h"
using namespace::std;
/**
 * @brief Class describing a single armor piece with available deco slots and skill levels
 */
class ArmorPiece
{
public:
    enum ARMOR_TYPE {
        HEAD,   // 0
        TORSO,  // 1
        ARMS,   // 2
        WAIST,  // 3
        LEGS    // 4
    };
    explicit ArmorPiece();
    /**
     * @brief Basic armor piece constructor, disregards armor values
     * @param Internal ID of the piece
     * @param Name of the piece
     * @param Equipment slot of the piece
     * @param IDs of the skills the armor has
     * @param Levels of the skills the armor has
     * @param Number of skills the piece has
     * @param size-3 array of the slots the armor piece has
     */
    ArmorPiece(qint16 id,
               QString name,
               ARMOR_TYPE type,
               vector<qint16> skillLevels,
               vector<qint16> decoSlots,
               vector<Skill *> skill);
    qint16 GetId();
    qint16 GetLevel();
    /**
     * @brief Checks whether the skill ID exists on the armor piece
     * @param id
     * @return
     */
    bool ContainsSkill(Skill *);
    QString GetName();
    /**
     * @brief Map the skill IDs and the levels
     * @return
     */
    std::map<Skill *, qint16> getSkills();
    qint16 getSlotLevelA();
    qint16 getSlotLevelB();
    qint16 getSlotLevelC();
private:
    /**
     * @brief What slot the armor piece goes to
     */
    ARMOR_TYPE armorType;

    /**
      * @brief ID of the armor piece (Internal use)
      */
    qint16 armorID;

    /**
     * @brief Name of the piece
     */
    QString name;

    /**
     * @brief Vector of reference to the pieces innate skills
     */
    vector<Skill *> skillList;

    /**
     * @brief Map<Skill ID, Level> of skills the armor piece has
     */
    map<Skill *, qint16> armorSkills;

    /**
     * @brief Decoration A slot level
     */
    qint16 decoSlotLevelA;
    /**
     * @brief Decoration B slot level
     */
    qint16 decoSlotLevelB;
    /**
     * @brief Decoration C slot level
     */
    qint16 decoSlotLevelC;

    qint16 defenceMin;
    qint16 defenceMax;
    qint16 fireRes;
    qint16 waterRes;
    qint16 lightRes;
    qint16 iceRes;
    qint16 dragonRes;

signals:

};

#endif // ARMORPIECE_H
