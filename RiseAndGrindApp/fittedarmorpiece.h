#ifndef FITTEDARMORPIECE_H
#define FITTEDARMORPIECE_H

#include "decoration.h"
#include "armorpiece.h"
/**
 * @brief The FullArmorPiece class represents an armor piece that is able to be fitted with decorations.
 * This is so the armor peice class is able to be separated from the set search engine by acting
 * as a database only. This class is an instance that contains references to the armor piece along with
 * the valid decorations it can wear. It is also responsible for validating the attached decorations.
 * The search engine can permute through all the pieces and decorations by making many instances of this class.
 */
class FittedArmorPiece
{
public:
    FittedArmorPiece();
    /**
     * @brief FittedArmorPiece Constructor method
     * @param armor Armor piece reference
     * @param decos Decorations applied to the armorset
     */
    FittedArmorPiece(ArmorPiece * armor, std::vector<Decoration> & decos);
    /**
     * @brief Constructor methodm with no decorations
     * @param armor Armor piece to apply
     */
    FittedArmorPiece(ArmorPiece * armor);
    ArmorPiece * GetArmorPiece();
    /**
     * @brief Applies a decoration to the armor piece
     * @param slot Slot to put the decoration in (1, 2 or 3)
     * @param d reference to the Decoration to add
     */
    void PutDecoration(qint16 slot, Decoration * d);

    /**
     * @brief Returns the validity of the armor piece
     * @return
     */
    bool GetValidSet();

    Decoration * getDecoA();
    Decoration * getDecoB();
    Decoration * getDecoC();
private:
    /**
     * @brief Reference to the armor piece in the equipment database
     */
    ArmorPiece * armorPiece;

    /**
     * @brief Vector of decorations fitted to the armor peice.
     */
    std::vector<Decoration> decorations;

    Decoration * decoA;
    Decoration * decoB;
    Decoration * decoC;

    /**
     * @brief Validates that the decorations fitted can actually be fitted
     */
    bool ValidateDecorations();
    bool validSet;
};

#endif // FITTEDARMORPIECE_H
