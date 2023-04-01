#include "armorpiece.h"

ArmorPiece::ArmorPiece()
{
    this->defenseMin = 0;
    this->defenseMax = 0;
    this->fireRes = 0;
    this->waterRes = 0;
    this->lightRes = 0;
    this->iceRes = 0;
    this->dragonRes = 0;
}
ArmorPiece::ArmorPiece(qint16 id,
                       QString name,
                       ARMOR_TYPE type,
                       vector<qint16> skillLevels,
                       vector<qint16> decoSlots,
                       vector<Skill *> skills) {
    this->armorID = id;
    this->name = name;
    this->armorType = type;

    // Load skill values into map
    for (int i = 0; i < (int) skills.size(); i++) {
        this->armorSkills[skills.at(i)] = skillLevels.at(i);
    }

    this->decoSlotLevelA = decoSlots[0];
    this->decoSlotLevelB = decoSlots[1];
    this->decoSlotLevelC = decoSlots[2];
    this->skillList = skills;

    this->defenseMin = 0;
    this->defenseMax = 0;
    this->fireRes = 0;
    this->waterRes = 0;
    this->lightRes = 0;
    this->iceRes = 0;
    this->dragonRes = 0;
}

qint16 ArmorPiece::GetId() {
    return this->armorID;
}

bool ArmorPiece::ContainsSkill(Skill * s) {
    if (this->armorSkills.count(s) > 0) {
        return true;
    }
    return false;
}
QString ArmorPiece::GetName() {
    return this->name;
}

std::map<Skill *, qint16> ArmorPiece::getSkills() {
    return this->armorSkills;
}

qint16 ArmorPiece::getSlotLevelA() {
    return this->decoSlotLevelA;
}

qint16 ArmorPiece::getSlotLevelB() {
    return this->decoSlotLevelB;
}

qint16 ArmorPiece::getSlotLevelC() {
    return this->decoSlotLevelC;
}

QJsonObject ArmorPiece::ToJSON() {
    QJsonObject obj;
    obj["defenseMin"] = this->defenseMin;
    obj["defenseMax"] = this->defenseMax;
    obj["fireRes"] = this->fireRes;
    obj["waterRes"] = this->waterRes;
    obj["lightningRes"] = this->lightRes;
    obj["dragonRes"] = this->dragonRes;
    obj["armorID"] = this->armorID;
    obj["name"] = this->name;
    obj["armorType"] = this->armorType;
    obj["decoSlotLevelA"] = this->decoSlotLevelA;
    obj["decoSlotLevelB"] = this->decoSlotLevelB;
    obj["decoSlotLevelC"] = this->decoSlotLevelC;
    if (this->skillList.size() > 0) {
        QJsonArray arr;
        // Create a new json object for each skill/skill level
        for (Skill * s : this->skillList) {
            QJsonObject obj2;
            obj2["skillID"] = s->GetSkillId();
            obj2["skillLevel"] = this->armorSkills[s];
            arr.append(obj2);
        }
        obj["skillList"] = arr;
    }
    return obj;
}

void ArmorPiece::FromJSON(QJsonObject &json, std::vector<Skill *> &skills) {
    if (json.contains("defenseMin") && json["defenseMin"].isDouble())
        this->defenseMin = json["defenseMin"].toDouble();
    if (json.contains("defenseMax") && json["defenseMax"].isDouble())
        this->defenseMax = json["defenseMax"].toDouble();
    if (json.contains("fireRes") && json["fireRes"].isDouble())
        this->fireRes = json["fireRes"].toDouble();
    if (json.contains("waterRes") && json["waterRes"].isDouble())
        this->waterRes = json["waterRes"].toDouble();
    if (json.contains("lightningRes") && json["lightningRes"].isDouble())
        this->lightRes = json["lightningRes"].toDouble();
    if (json.contains("dragonRes") && json["dragonRes"].isDouble())
        this->dragonRes = json["dragonRes"].toDouble();
    if (json.contains("armorID") && json["armorID"].isDouble())
        this->armorID = json["armorID"].toDouble();
    if (json.contains("name") && json["name"].isString())
        this->name = json["name"].toString();
    if (json.contains("armorType") && json["armorType"].isDouble())
        this->armorType = (ArmorPiece::ARMOR_TYPE) json["armorType"].toDouble();
    if (json.contains("decoSlotLevelA") && json["decoSlotLevelA"].isDouble())
        this->decoSlotLevelA = json["decoSlotLevelA"].toDouble();
    if (json.contains("decoSlotLevelB") && json["decoSlotLevelB"].isDouble())
        this->decoSlotLevelB = json["decoSlotLevelB"].toDouble();
    if (json.contains("decoSlotLevelC") && json["decoSlotLevelC"].isDouble())
        this->decoSlotLevelC = json["decoSlotLevelC"].toDouble();
    if (json.contains("skillList") && json["skillList"].isArray()) {
        vector<Skill *> skillVect = vector<Skill*>();
        map<Skill *, qint16> skillMap = map<Skill *, qint16>();
        QJsonArray skillList = json["skillList"].toArray();
        for (auto a : skillList) {
            QJsonObject skill = a.toObject();
            if (skill.contains("skillID") && skill["skillID"].isDouble()) {
                Skill * s = findSkill(skill["skillID"].toDouble(), skills);
                if (s == NULL) qWarning() << "Skill " << skill["skillID"] << "not found in loaded skills!";
                else {
                    skillVect.push_back(s);
                    if (skill.contains("skillLevel") && skill["skillLevel"].isDouble()) {
                        skillMap[s] = skill["skillLevel"].toDouble();
                    }
                }
            }
        }
        this->skillList = skillVect;
        this->armorSkills = skillMap;
        qInfo() << "Loaded " << this->skillList.size() << " skills for armor piece " << this->armorID;
    }
}

Skill * ArmorPiece::findSkill(qint16 id, vector<Skill *> skillList) {
    for (auto a : skillList) {
        if (a->GetSkillId() == id) return a;
    }
    return NULL;
}
