#include "equipmentdatabase.h"

EquipmentDatabase::EquipmentDatabase()
{
    this->headArmorPieces = *new vector<ArmorPiece *>();
    this->bodyArmorPieces = *new vector<ArmorPiece *>();
    this->gauntletArmorPieces = *new vector<ArmorPiece *>();
    this->waistArmorPieces = *new vector<ArmorPiece *>();
    this->legArmorPieces = *new vector<ArmorPiece *>();

    this->skills = *new vector<Skill *>();
    this->decorations = *new vector<Decoration *>();

}
EquipmentDatabase::~EquipmentDatabase() {
    int i;
    for (i = 0; i < (int) this->headArmorPieces.size(); i++) {
        delete this->headArmorPieces.at(i);
    }

    for (i = 0; i < (int) this->bodyArmorPieces.size(); i++) {
        delete this->bodyArmorPieces.at(i);
    }

    for (i = 0; i < (int) this->gauntletArmorPieces.size(); i++) {
        delete this->gauntletArmorPieces.at(i);
    }

    for (i = 0; i < (int) this->waistArmorPieces.size(); i++) {
        delete this->waistArmorPieces.at(i);
    }

    for (i = 0; i < (int) this->legArmorPieces.size(); i++) {
        delete this->legArmorPieces.at(i);
    }

    for (i = 0; i < (int) this->skills.size(); i++) {
        delete this->skills.at(i);
    }

    for (i = 0; i < (int) this->decorations.size(); i++) {
        delete this->decorations.at(i);
    }
    this->headArmorPieces.clear();
    this->bodyArmorPieces.clear();
    this->gauntletArmorPieces.clear();
    this->waistArmorPieces.clear();
    this->legArmorPieces.clear();
    this->skills.clear();
    this->decorations.clear();

}
void EquipmentDatabase::LoadData() {
    // First load the skills as they have the IDS and names for everything else
    LoadSkills();
    LoadArmor();
    LoadDecorations();
}

qint16 EquipmentDatabase::LoadSkills() {
    QFile file("./Skills.csv");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug("ERROR: Could not open the skills CSV");
        return -1;
    } else {
        // Read the CSV file
        QTextStream filestream(&file);
        // read the first line into nothing as its just header information
        filestream.readLine();
        // Now loop through and add the data to the database
        while (!filestream.atEnd()) {
            QString line = filestream.readLine();
            // ROW 0: SKill ID
            // ROW 1: Skill name
            // ROW 2: max level TODO:
            QStringList row = line.split(',');
            // Add the skill to the database
            this->skills.push_back(new Skill(row[0].toInt(), row[1]));
        }
        file.close();
        qDebug() << "Successfully loaded " << this->skills.size() << " Skills";
    }
    return 0;
}
qint16 EquipmentDatabase::LoadDecorations() {
    QFile file("./Decorations.csv");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "ERROR: Could not load the decorations CSV.";
        return -1;
    } else {
        QTextStream fs(&file);
        // Skip first line that only has table names
        fs.readLine();
        while (!fs.atEnd()) {
            QString line = fs.readLine();
            // ROW 0: Deco ID
            // ROW 1: Deco name
            // ROW 2: Deco slot level
            // ROW 3: Skill ID corresponding to deco
            QStringList row = line.split(',');
            // Skills should have been loaded already, find the skill corresponding to the deco
            Skill * skill = this->FindSkillById(row[3].toInt());
            // Create a new deco on the heap
            Decoration * deco = new Decoration(row[0].toInt(), row[2].toInt(), *skill, row[1]);
            // Add the skill to the database
            this->decorations.push_back(deco);
        }
        qDebug() << "Successfully loaded " << this->decorations.size() << " Decorations.";
        return 0;
    }
}
qint16 EquipmentDatabase::LoadArmor() {
    QFile file("./HRArmor.csv");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "ERROR. Could not load the HR Armor csv.";
        return -1;
    } else {
        QTextStream fs(&file);
        fs.readLine();
        while (!fs.atEnd()) {
            QString line = fs.readLine();
            /*
             * ROW 0 -- Equipment ID
             * ROW 1 -- Equipment Name
             * ROW 2 -- Equipment Slot
             * ROW 3 -- Equipment Skills (as IDs)
             * ROW 4 -- SKill Levels (corresponding to previous row)
             * ROW 5 -- Decoration Slots
             * ROW 6->12 -- minDef, maxDef, Fire/Water/Light/Ice/Drgn res
            */
            QStringList row = line.split(',');
            // oops
            qint16 skillSize = row[3].split('|').length();

            vector<qint16> skills = this->parseSkills(row[3]);
            vector<qint16> levels = this->parseLevels(row[4]);
            vector<qint16> decoSlots = this->parseSlots(row[5]);

            // evil code copypaste for skill reference vector
            QStringList lst = row[3].split('|');
            vector<Skill *> skillVector = vector<Skill *>();

            for (int i = 0; i < skillSize; i++) {
                skillVector.push_back(this->FindSkillById(lst.at(i).toInt()));
            }

            // Construct the armor piece
            ArmorPiece * piece = new ArmorPiece(row[0].toInt(),
                             row[1],
                             (ArmorPiece::ARMOR_TYPE) row[2].toInt(),
                             skills,
                             levels,
                             decoSlots,
                             skillVector);
            switch(row[2].toInt()) {
            case 0:
                this->headArmorPieces.push_back(piece);
                break;
            case 1:
                this->bodyArmorPieces.push_back(piece);
                break;
            case 2:
                this->gauntletArmorPieces.push_back(piece);
                break;
            case 3:
                this->waistArmorPieces.push_back(piece);
                break;
            case 4:
                this->legArmorPieces.push_back(piece);
            }
        }
        file.close();
        qDebug() << "Loaded " << this->headArmorPieces.size() << " head pieces.";
        qDebug() << "Loaded " << this->bodyArmorPieces.size() << " body pieces.";
        qDebug() << "Loaded " << this->gauntletArmorPieces.size() << " arm pieces.";
        qDebug() << "Loaded " << this->waistArmorPieces.size() << " waist pieces.";
        qDebug() << "Loaded " << this->legArmorPieces.size() << " leg pieces.";
    }
    return 0;
}

vector<qint16> EquipmentDatabase::parseSlots(QString str) {
    QStringList lst = str.split('|');
    vector<qint16> decoVect = vector<qint16>();
    for (int i = 0; i < lst.size(); i++) {
        decoVect.push_back(lst.at(i).toInt());
    }
    return decoVect;
}

vector<qint16> EquipmentDatabase::parseSkills(QString str) {
    QStringList lst = str.split('|');
    vector<qint16> skillVect = vector<qint16>();
    for (int i = 0; i < lst.size(); i++) {
        skillVect.push_back(lst[i].toInt());
    }
    return skillVect;
}

vector<qint16> EquipmentDatabase::parseLevels(QString str) {
    QStringList lst = str.split('|');
    vector<qint16> levelVect = vector<qint16>();
    for (int i = 0; i < lst.size(); i++) {
        levelVect.push_back(lst.at(i).toInt());
    }
    return levelVect;
}

vector<ArmorPiece *> EquipmentDatabase::GetHeadPieces() {
    return this->headArmorPieces;
}
vector<ArmorPiece *> EquipmentDatabase::GetBodyPieces() {
    return this->bodyArmorPieces;
}
vector<ArmorPiece *> EquipmentDatabase::GetArmPieces() {
    return this->gauntletArmorPieces;
}
vector<ArmorPiece *> EquipmentDatabase::GetWaistPieces() {
    return this->waistArmorPieces;
}
vector<ArmorPiece *> EquipmentDatabase::GetLegPieces() {
    return this->legArmorPieces;
}
vector<Talisman *> EquipmentDatabase::getTalismans() {
    return this->talismans;
}

Skill * EquipmentDatabase::FindSkillById(qint16 id) {
    Skill * skill = this->skills.at(id);
    return skill;
}

Decoration * EquipmentDatabase::FindDecoById(qint16 id) {
    return this->decorations.at(id);
}

Decoration * EquipmentDatabase::FindDecoBySkillId(qint16 skillId) {
    for (Decoration * d : decorations) {
        if (d->getDecoSkill()->GetSkillId() == skillId) {
            return d;
        }
    }
    return NULL;
}
