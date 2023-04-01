#ifndef DATABASE_H
#define DATABASE_H

#include "../DataCommon/src/armorpiece.h"
#include "../DataCommon/src/weapon.h"
#include "../DataCommon/src/talisman.h"
#include "../DataCommon/src/weapon.h"
#include "../DataCommon/src/decoration.h"
#include "../DataCommon/src/skill.h"
#include "../DataCommon/src/riseexception.h"

#include <vector>
#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <filesystem>
#include <QJsonObject>
#include <QJsonDocument>
/**
 * @brief Database service for locally holding loaded skills
 */
using namespace::std;
class Database
{
public:
    Database();
    /**
      * @brief Destructor
      */
    ~Database();
    /**
     * @brief Load all the data from CSV into their respective vectors
     */
    void LoadData(QString);
    /**
     * @brief Creates the database files inside a new directory in the present working directory
     */
    void SaveData(QString);
    /**
     * @brief Saves the contents of the database to JSON format
     */
    void saveData();
    vector<ArmorPiece *> GetHeadPieces();
    vector<ArmorPiece *> GetBodyPieces();
    vector<ArmorPiece *> GetArmPieces();
    vector<ArmorPiece *> GetWaistPieces();
    vector<ArmorPiece *> GetLegPieces();
    vector<Talisman *> getTalismans();
    /**
     * @brief Gets the skill at index
     * @param id ID of the skill
     * @return reference to the skill that has been loaded
     */
    Skill * FindSkillById(qint16 id);
    /**
     * @brief Gets the decoration at the index it was loaded into memory
     * @param id
     * @return
     */
    Decoration * FindDecoById(qint16 id);
    /**
     * @brief Gets the decoration that corresponds to a certain skill by its ID
     * @param skillId
     * @return
     */
    Decoration * FindDecoBySkillId(qint16 skillId);

    /**
     * @brief Loads all entries from d into current instance through deep copying
     */
    void mergeDatabase(Database * d);
    /**
     * @brief Converts the database into a JSON object
     */
    QJsonObject ToJSON();
private:
    qint16 LoadArmor(QString);
    /**
    * @brief Load all the skills from the skills CSV. Skills are the lowest and most
    * important dataset. Every single instance of a skill in the program should be
    * a reference to an object in the skills database.
    * @return
    */
    qint16 LoadSkills(QString);
    qint16 LoadDecorations(QString);
    /**
     * @brief Loads all talismans from the talisman database file
     * @return
     */
    qint16 LoadTalismans(QString);
    /**
     * @brief Parses slots into an array from a pipe-delimited string
     * @param The string to parse (E.G. 3|2|0)
     * @return Pointer to size-3 array on stack with int values
     */
    vector<qint16> parseSlots(QString str);
    /**
     * @brief Parses pipe-separated skills string into array of ints
     * @param string input
     * @return vector oof skill ids
     */
    vector<qint16> parseSkills(QString str);
    /**
     * @brief Parses pipe-separated skill-levels into an array of its
     * @param string input
     * @return pointer to array containing qints
     */
    vector<qint16> parseLevels(QString str);

    vector<ArmorPiece *> headArmorPieces;
    vector<ArmorPiece *> bodyArmorPieces;
    vector<ArmorPiece *> gauntletArmorPieces;
    vector<ArmorPiece *> waistArmorPieces;
    vector<ArmorPiece *> legArmorPieces;

    vector<Weapon *> weapons;
    vector<Talisman *> talismans;
    vector<Decoration *> decorations;
    /**
     * @brief Vector of skills loaded into memory from a file.
     */
    vector<Skill *> skills;
};

#endif // DATABASE_H
