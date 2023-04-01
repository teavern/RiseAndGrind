#include "skill.h"

Skill::Skill()
{
    this->name = "";
    this->skillID = 0;
    this->maxSkillLevel = 0;
    this->description = "";
}

Skill::Skill(qint16 id, qint16 maxLevel, QString name, QString description) {
    this->name = name;
    this->skillID = id;
    this->maxSkillLevel = maxLevel;
    this->description = description;
}

Skill::Skill(qint16 id, qint16 maxLevel, QString name) {
    this->name = name;
    this->skillID = id;
    this->maxSkillLevel = maxLevel;
}

Skill::Skill(qint16 id, QString name) {
    this->name = name;
    this->skillID = id;
    this->maxSkillLevel = 7;
}

Skill::Skill(qint16 id) {
    this->name = "";
    this->skillID = id;
    this->maxSkillLevel = 7;
}

Skill::Skill(QJsonObject &json) {
    this->FromJSON(json);
}

qint16 Skill::GetMaxSkillLevel() {
    return this->maxSkillLevel;
}

QString Skill::GetSkillName() {
    return this->name;
}

qint16 Skill::GetSkillId() {
    return this->skillID;
}

QJsonObject Skill::ToJSON() {
    QJsonObject obj;
    obj["name"] = this->name;
    obj["skillID"] = this->skillID;
    obj["maxSkillLevel"] = this->maxSkillLevel;
    obj["description"] = this->description;
    return obj;
}

void Skill::FromJSON(QJsonObject &json) {
    if (json.contains("name") && json["name"].isString()) {
        this->name = json["name"].toString();
    }

    if (json.contains("skillID") && json["skillID"].isDouble()) {
        this->skillID = json["skillID"].toDouble();
    }

    if (json.contains("maxSkillLevel") && json["maxSkillLevel"].isDouble()) {
        this->maxSkillLevel = json["maxSkillLevel"].toDouble();
    }

    if (json.contains("description") && json["description"].isString()) {
        this->description = json["description"].toString();
    }
    qDebug() << "Loaded single skill from JSON :: " << this->ToString();
}

QString Skill::ToString() {
    return QString("Skill=[skillID=%1, name=%2 maxSkillLevel=%3, description=%4]").arg(QString::number(this->skillID), this->name, QString::number(this->maxSkillLevel), this->description);
}
