#ifndef EQUIPMENTDATABASE_H
#define EQUIPMENTDATABASE_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QDebug>

#include "armorpiece.h"
#include "weapon.h"
#include "talisman.h"
#include "weapon.h"
#include "decoration.h"
#include "skill.h"
#include <vector>
/**
 * @brief Class containing all the equipment data loaded on startup.
 * This class is used as data for the combinatorics engine.
 * Also contains functions for loading data from CSV.
 */
using namespace::std;
class EquipmentDatabase
{
public:
    EquipmentDatabase();
    /**
      * @brief Destructor
      */
    ~EquipmentDatabase();
    /**
     * @brief Load all the data from CSV into their respective vectors
     */
    void LoadData();
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
private:
    qint16 LoadArmor();
    /**
    * @brief Load all the skills from the skills CSV. Skills are the lowest and most
    * important dataset. Every single instance of a skill in the program should be
    * a reference to an object in the skills database.
    * @return
    */
    qint16 LoadSkills();
    qint16 LoadDecorations();
    /**
     * @brief Loads all talismans from the talisman database file
     * @return
     */
    qint16 LoadTalismans();
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

#endif // EQUIPMENTDATABASE_H
