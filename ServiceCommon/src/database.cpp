#include "database.h"

Database::Database()
{
    this->headArmorPieces = *new vector<ArmorPiece *>();
    this->bodyArmorPieces = *new vector<ArmorPiece *>();
    this->gauntletArmorPieces = *new vector<ArmorPiece *>();
    this->waistArmorPieces = *new vector<ArmorPiece *>();
    this->legArmorPieces = *new vector<ArmorPiece *>();

    this->skills = *new vector<Skill *>();
    this->decorations = *new vector<Decoration *>();
}

Database::~Database() {
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
void Database::LoadData(QString directory) {
    // load priority :: skill >> decos >> armor >> user equipment
    qint16 items = 0;
    items += LoadSkills(directory);
    items += LoadDecorations(directory);
    items += LoadArmor(directory);
    items += LoadTalismans(directory);
    qInfo() << "Loaded " << items << " total entries";
}

void Database::SaveData(QString directory) {
    qDebug() << "Saving database";
    try {
        QJsonObject out = ToJSON();
        QFile file = QFile(directory);
        if (!file.open(QIODevice::WriteOnly)) {
            throw (RiseException("Failed to open file " + directory.toStdString()));
        }
        int i = file.write(QJsonDocument(out).toJson());
        if (i == -1) {
            file.close();
            throw (RiseException("Could not write to file " + directory.toStdString()));
        }
        qInfo() << "Saved database to " << directory;
        file.close();
    } catch (RiseException e) {
        qCritical() << "Failed to save database file :: " << e.what();
        throw (RiseException("Failed to save database file"));
    }
}

qint16 Database::LoadSkills(QString dir) {

    return 0;
}

qint16 Database::LoadDecorations(QString dir) {

    return 0;
}

qint16 Database::LoadArmor(QString dir) {

    return 0;
}

qint16 Database::LoadTalismans(QString dir) {

    return 0;
}

vector<qint16> Database::parseSlots(QString str) {
    QStringList lst = str.split('|');
    vector<qint16> decoVect = vector<qint16>();
    for (int i = 0; i < lst.size(); i++) {
        decoVect.push_back(lst.at(i).toInt());
    }
    return decoVect;
}

vector<qint16> Database::parseSkills(QString str) {
    QStringList lst = str.split('|');
    vector<qint16> skillVect = vector<qint16>();
    for (int i = 0; i < lst.size(); i++) {
        skillVect.push_back(lst[i].toInt());
    }
    return skillVect;
}

vector<qint16> Database::parseLevels(QString str) {
    QStringList lst = str.split('|');
    vector<qint16> levelVect = vector<qint16>();
    for (int i = 0; i < lst.size(); i++) {
        levelVect.push_back(lst.at(i).toInt());
    }
    return levelVect;
}

vector<ArmorPiece *> Database::GetHeadPieces() {
    return this->headArmorPieces;
}
vector<ArmorPiece *> Database::GetBodyPieces() {
    return this->bodyArmorPieces;
}
vector<ArmorPiece *> Database::GetArmPieces() {
    return this->gauntletArmorPieces;
}
vector<ArmorPiece *> Database::GetWaistPieces() {
    return this->waistArmorPieces;
}
vector<ArmorPiece *> Database::GetLegPieces() {
    return this->legArmorPieces;
}
vector<Talisman *> Database::getTalismans() {
    return this->talismans;
}

Skill * Database::FindSkillById(qint16 id) {
    Skill * skill = this->skills.at(id);
    return skill;
}

Decoration * Database::FindDecoById(qint16 id) {
    return this->decorations.at(id);
}

Decoration * Database::FindDecoBySkillId(qint16 skillId) {
    for (Decoration * d : decorations) {
        if (d->getDecoSkill()->GetSkillId() == skillId) {
            return d;
        }
    }
    return NULL;
}

QJsonObject Database::ToJSON() {
    QJsonObject obj;
    QJsonArray armorList;
    for (auto i : this->headArmorPieces) {
        QJsonObject armorPiece = i->ToJSON();
        armorList.append(armorPiece);
    }
    for (auto i : this->bodyArmorPieces) {
        QJsonObject armorPiece = i->ToJSON();
        armorList.append(armorPiece);
    }
    for (auto i : this->gauntletArmorPieces) {
        QJsonObject armorPiece = i->ToJSON();
        armorList.append(armorPiece);
    }
    for (auto i : this->waistArmorPieces) {
        QJsonObject armorPiece = i->ToJSON();
        armorList.append(armorPiece);
    }
    for (auto i : this->legArmorPieces) {
        QJsonObject armorPiece = i->ToJSON();
        armorList.append(armorPiece);
    }
    qDebug("Converted all armor pieces");
    obj["armor"] = armorList;

    QJsonArray skillList;
    for (auto i : this->skills) {
        QJsonObject skill = i->ToJSON();
        skillList.append(skill);
    }
    obj["skills"] = skillList;
    qDebug("Converted skill list to JSON");

    QJsonArray decoList;
    for (auto i : this->decorations) {
        QJsonObject deco = i->ToJSON();
        decoList.append(deco);
    }
    obj["decorations"] = decoList;
    qDebug("Converted deco list to JSON");
    return obj;
}
