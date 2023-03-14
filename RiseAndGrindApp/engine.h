#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <vector>
#include "equipmentdatabase.h"
#include "armorset.h"
#include "searchparameters.h"
#include "setreport.h"
#include "fittedarmorpiece.h"
#include <algorithm>

/**
 * @brief Engine that creates combinations based on user input
 */
using namespace::std;
class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);
    /**
     * @brief Engine Constructor
     * @param Reference to a database object with the loaded data
     */
    Engine(EquipmentDatabase * database);
    /**
     * @brief Find a max of N valid sets given the search parameters
     * @param Search Parameters with desired skills
     * @param Max number of results to find
     * @return QVector containing the armor sets
     */
    vector<ArmorSet> FindSets(SearchParameters &params, qint16 maxCount);
signals:

private:
    /**
     * @brief Pointer to a database object
     */
    EquipmentDatabase * database;
    /**
     * @brief Find candidates from the database such that the armor pieces have the desired skill
     * @param ID of the desired skill
     * @param Minimum level of the skill
     * @return vector containing pointers to the armor pieces in the database
     */\
    vector<ArmorPiece *> FindCandidates(qint16 skillId, qint16 minSkillLevel, ArmorPiece::ARMOR_TYPE type);
    /**
     * @brief Gets all the decorations that fit the search parameters.
     * @param params Search parameters to use
     * @return Vector of pointers to the decoration object in the database.
     */
    vector<Decoration *> FindDecorations(SearchParameters & params);

    /**
     * @brief Creates a permutation of all possible decoration combinations onto the given set.
     * Each decoroation may be used N number of times.
     * @param set The armor set to apply decorations to
     * @param d The vector of decorations to use
     * @return A list of armorsets that contain the same armor pieces but with every permutation of decorations given by d.
     */
    vector<ArmorSet> PermutateDecorations(ArmorSet & set, vector<Decoration *> d);
    /**
     * @brief Finds all talismans with the skills specified by the search parameters
     * @param Search parameters to use
     * @return Vector or talisman pointers from the master database
     */
    vector<Talisman *> findTalismans(SearchParameters & params);
    /**
     * @brief 7-set cartesian product
     * @return Vector of armorsets such that there is every single combination of the input sets such that one from each category is chosen
     */
    vector<ArmorSet> CartesianProduct(vector<ArmorPiece*> &headPieces,
                                        vector<ArmorPiece*> &bodyPieces,
                                        vector<ArmorPiece*> &armPieces,
                                        vector<ArmorPiece*> &waistPieces,
                                        vector<ArmorPiece*> &legPieces,
                                        vector<Weapon> &weapons,
                                        vector<Talisman *> &talismans,
                                        qint16 maxSearchResults,
                                        SearchParameters & params);
    /**
     * @brief Checks whether the armorset matches the set search parameters
     * @param armorSet The armor set
     * @param parameters The search parameters
     * @return
     */
    bool ValidSetCheck(ArmorSet & armorSet, SearchParameters & parameters);
};

#endif // ENGINE_H
