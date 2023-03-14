#include "engine.h"

Engine::Engine(QObject *parent) : QObject(parent)
{

}

Engine::Engine(EquipmentDatabase * d) {
    this->database = d;
}

vector<ArmorSet> Engine::FindSets(SearchParameters &params, qint16 maxCount) {
    vector<ArmorSet> foundSets;
    // Candidates should match any of the params
    //IE even though the minimum skill may be 3, we want all sets with that skill regardless
    // If the piece also has slots >= the skill deco, add that too
    vector<ArmorPiece *> headCandidates;
    vector<ArmorPiece *> torsoCandidates;
    vector<ArmorPiece *> armsCandidates;
    vector<ArmorPiece *> waistCandidates;
    vector<ArmorPiece *> legsCandidates;
    vector<Weapon> weaponCandidates;
    vector<Talisman *> talismanCandidates = findTalismans(params);
    // Go over every skill and level and append them to the appropriate vector
    for (int i = 0; i < (int) params.skillLevels.size(); i++) {
        auto headTmp = FindCandidates(params.skillIds[i], 1, ArmorPiece::HEAD);
        auto torsoTmp = FindCandidates(params.skillIds[i], 1, ArmorPiece::TORSO);
        auto armTmp = FindCandidates(params.skillIds[i], 1, ArmorPiece::ARMS);
        auto waistTmp = FindCandidates(params.skillIds[i],1, ArmorPiece::WAIST);
        auto legTmp = FindCandidates(params.skillIds[i], 1, ArmorPiece::LEGS);
        // evil copy pasted code
        for (int j = 0; j < (int) headTmp.size(); j++)
            headCandidates.push_back(headTmp.at(j));

        for (int j = 0; j < (int) torsoTmp.size(); j++)
            torsoCandidates.push_back(torsoTmp.at(j));

        for (int j = 0; j < (int) armTmp.size(); j++)
            armsCandidates.push_back(armTmp.at(j));

        for (int j = 0; j < (int) waistTmp.size(); j++)
            waistCandidates.push_back(waistTmp.at(j));

        for (int j = 0; j < (int) legTmp.size(); j++)
            legsCandidates.push_back(legTmp.at(j));
    }
    // Search the weapons and talismans next


    // Add a No Armor armor piece to each category (prevents idx oob error in cartesian product search)
    vector<qint16> emptySlots = {0,0,0};
    headCandidates.push_back(new ArmorPiece(0, "No Head Piece", ArmorPiece::HEAD, vector<qint16>(), vector<qint16>(), emptySlots, vector<Skill *>()));
    torsoCandidates.push_back(new ArmorPiece(1, "No Torso Piece", ArmorPiece::TORSO, vector<qint16>(), vector<qint16>(), emptySlots, vector<Skill *>()));
    armsCandidates.push_back(new ArmorPiece(2, "No Arm Piece", ArmorPiece::ARMS, vector<qint16>(), vector<qint16>(), emptySlots, vector<Skill *>()));
    waistCandidates.push_back(new ArmorPiece(3, "No Waist Piece", ArmorPiece::WAIST, vector<qint16>(), vector<qint16>(), emptySlots, vector<Skill *>()));
    legsCandidates.push_back(new ArmorPiece(4, "No Leg Piece", ArmorPiece::LEGS, vector<qint16>(), vector<qint16>(), emptySlots, vector<Skill *>()));
    // TODO: Handle weapons and talismans, weapons should just be a slot choice
    // Find every combination
    foundSets = Engine::CartesianProduct(headCandidates,
                                         torsoCandidates,
                                         armsCandidates,
                                         waistCandidates,
                                         legsCandidates,
                                         weaponCandidates,
                                         talismanCandidates,
                                         maxCount,
                                         params);
    qDebug() << "Found" << foundSets.size() << "unique sets";
    return foundSets;
}

vector<Decoration *> Engine::FindDecorations(SearchParameters & params) {
    vector<Decoration *> validDecos = vector<Decoration *>();
    // Go through the search parameter skills
    for (Skill skill : params.skillIds) {
         validDecos.push_back(this->database->FindDecoById(skill.GetSkillId()));
    }
    return validDecos;
}

bool Engine::ValidSetCheck(ArmorSet & armorSet, SearchParameters & parameters) {
    SetReport report = SetReport(armorSet);
    bool valid = true;
    // Iterate through all the skills in the search parameters (top level iteration is important)
    for (auto &setSkill : parameters.skillMap) {
        // Check if the required skill is in the skill report
        if (report.getSetTotals().count(setSkill.first) > 0) {
            // Now check if the requirement doesnt match so we can set the flag to false and go to the next set
            // This algorithm assumes that the set matches until proven otherwise
            if (setSkill.second < (report.getSetTotals())[setSkill.first] ) {
                valid = false;
                break;
            }
        } else {
            // Skill not in the set, skip it
            valid = false;
            break;
        }
    }
    if (valid) {
        qDebug("Found a valid set!");
        return true;
    }
    return false;
}

vector<ArmorPiece *> Engine::FindCandidates(qint16 skillId, qint16 minSkillLevel, ArmorPiece::ARMOR_TYPE type) {
    vector<ArmorPiece *> candidates;
    vector<ArmorPiece *> data;     // pointer to the group of pieces we want
    int numObjects;
    switch (type) {
    case ArmorPiece::HEAD:
        numObjects = this->database->GetHeadPieces().size();
        data = this->database->GetHeadPieces();
        break;
    case ArmorPiece::TORSO:
        numObjects = this->database->GetBodyPieces().size();
        data = this->database->GetBodyPieces();
        break;
    case ArmorPiece::ARMS:
        numObjects = this->database->GetArmPieces().size();
        data = this->database->GetArmPieces();
        break;
    case ArmorPiece::WAIST:
        numObjects = this->database->GetWaistPieces().size();
        data = this->database->GetWaistPieces();
        break;
    case ArmorPiece::LEGS:
        numObjects = this->database->GetLegPieces().size();
        data = this->database->GetLegPieces();
        break;
    default:
        return candidates;
    }
    // Assumes that data will never be null here
    for (int i = 0; i < numObjects; i++) {
        if( data.at(i)->ContainsSkill(skillId)) {
            candidates.push_back(data.at(i));
            qDebug() << "Matched skill " << skillId << " to " << data.at(i)->GetName();
        }
    }

    return candidates;
}

vector<Talisman *> Engine::findTalismans(SearchParameters & searchParams)  {
    vector<Talisman *> foundTalismans = vector<Talisman *>();
    for (auto skill : searchParams.skillIds) {
        for (auto talisman : database->getTalismans()) {
            if (talisman->getSkillLevels().count(skill) > 0) {
                foundTalismans.push_back(talisman);
            }
        }
    }
    return foundTalismans;

}

vector<ArmorSet> Engine::CartesianProduct(vector<ArmorPiece *> &headPieces,
                                          vector<ArmorPiece *> &bodyPieces,
                                          vector<ArmorPiece *> &armPieces,
                                          vector<ArmorPiece *> &waistPieces,
                                          vector<ArmorPiece *> &legPieces,
                                          vector<Weapon> &weapons,
                                          vector<Talisman *> &talismans,
                                          qint16 maxSearchResults,
                                          SearchParameters & params) {
    vector<ArmorSet> foundSets;
    int foundSetCount = 0;
    int headIdx = 0;
    int bodyIdx = 0;
    int armIdx = 0;
    int waistIdx = 0;
    int legIdx = 0;
    int taliIdx = 0;
    while(1) {
        // Do all the index parsing first before making a set
        if (taliIdx == (int) talismans.size()) {    // Talisman index
            taliIdx = 0;
            legIdx++;
        }
        /*
        if (weaponIdx == (int) weapons.size()) {
            weaponIdx = 0;
            legIdx++;
        }
        */
        if (legIdx == (int) legPieces.size()) {
            legIdx = 0;
            waistIdx++;
        }
        if (waistIdx == (int) waistPieces.size()) {
            waistIdx = 0;
            armIdx++;
        }
        if (armIdx == (int) armPieces.size()) {
            armIdx = 0;
            bodyIdx++;
        }
        if (bodyIdx == (int) bodyPieces.size()) {
            bodyIdx = 0;
            headIdx++;
        }
        if (headIdx == (int) headPieces.size()) {
            // If headidx is equal to the count then we traversed through everything
            break;
        }
        // Head is the slowest moving
        // Create the set
        Weapon weapon = Weapon(); // TODO:
        Talisman * tali = talismans.at(taliIdx);
        auto fittedHead = FittedArmorPiece(headPieces.at(headIdx));
        auto fittedBody = FittedArmorPiece(bodyPieces.at(bodyIdx));
        auto fittedArm = FittedArmorPiece(armPieces.at(armIdx));
        auto fittedWaist =  FittedArmorPiece(waistPieces.at(waistIdx));
        auto fittedLegs = FittedArmorPiece(legPieces.at(legIdx));
        ArmorSet tempSet = ArmorSet(fittedHead,
                                    fittedBody,
                                    fittedArm,
                                    fittedWaist,
                                    fittedLegs,
                                    tali);

        if (ValidSetCheck(tempSet, params)) {
            // Set valid and matches, no need to check for decorations
            foundSets.push_back(tempSet);
            foundSetCount++;
        } else {
            // Need to try and add decorations or talismans
            // So iterate through each desired skill, get the difference
            // between what is desired and what is available
            // and attempt to fit decorations to the armor pieces

            // Ths while should keep the loop running until there are
            // no more valid slots to add decos to

            // Unoptimized brute force deco adding method
            bool validSet = false;
            while (!validSet) {
                // Check var whether a decoration was added
                bool addedDeco = false;
                // Iterate over all skills we are searching for
                for (qint16 skillId : params.skillIds) {
                    qint16 desiredSkillVal = params.skillMap.at(skillId);
                    qint16 currentSkillVal = 0;
                    qint16 difference;

                    map<qint16, qint16> setSkillMap = tempSet.getSkillLevels();
                    if (setSkillMap.count(skillId)) {
                        currentSkillVal = setSkillMap[skillId];
                    }

                    // Get the difference from what we want with what is there
                    difference = desiredSkillVal - currentSkillVal;

                    // If there is a difference then that means we have to add decorations
                    if (difference > 0) {
                        // Start with decoration A
                        // Slot a decoration within the first open valid slot
                        // If there are no available slots and the set still is
                        // not valid then the set must be discarded

                        for (auto armor : tempSet.getArmorList()) {
                            Decoration * d = database->FindDecoBySkillId(skillId);
                            // empty slots SHOULD be null
                            if (armor->getDecoA() == NULL && armor->GetArmorPiece()->getSlotLevelA() >= d->getDecoLevel()) {
                                armor->PutDecoration(0, d);
                                addedDeco = true;
                            } else if (armor->getDecoB() == NULL && armor->GetArmorPiece()->getSlotLevelB() >= d->getDecoLevel()) {
                                armor->PutDecoration(1, d);
                                addedDeco = true;
                            } else if (armor->getDecoC() == NULL && armor->GetArmorPiece()->getSlotLevelC() >= d->getDecoLevel()) {
                                armor->PutDecoration(2, d);
                                addedDeco = true;
                            }
                        }
                    }
                }
                // Check if it is a valid set yet
                if (ValidSetCheck(tempSet, params)) {
                    validSet = true;
                    break;
                }

                // break out of the while loop if no deco was added
                // this assumes that after iterating through all decos and none were fitted
                // then there are no more open slots
                if (!addedDeco) {
                    break;
                }
            }
            if (validSet) {
                foundSets.push_back(tempSet);
                foundSetCount++;
            }
        }

        if (foundSetCount >= maxSearchResults)
            break;

        // Increment the lowest order category
        taliIdx++;
    }

    return foundSets;

}
