#include "decoration.h"

Decoration::Decoration() {

}
Decoration::Decoration(qint16 decoId, qint16 slotLevel, Skill & skill, QString name) {
    this->decoID = decoId;
    this->decoLevel = slotLevel;
    this->skill = &skill;
    this->name = name;
}

Decoration::~Decoration() {

}

qint16 Decoration::getDecoLevel() {
    return decoLevel;
}

Skill * Decoration::getDecoSkill() {
    return skill;
}

QJsonObject Decoration::ToJSON() {
    QJsonObject obj;
    obj["id"] = this->decoID;
    obj["level"] = this->decoLevel;
    obj["skill"] = this->skill->GetSkillId();
    obj["name"] = this->name;
    return obj;
}

void Decoration::FromJSON(QJsonObject &json, std::vector<Skill*> &skillList) {
    if (json.contains("id") && json["id"].isDouble())
        this->decoID = json["id"].toDouble();
    if (json.contains("level") && json["level"].isDouble())
        this->decoLevel = json["level"].toDouble();
    if (json.contains("skill") && json["skill"].isDouble()) {
        qint16 skillID = json["skill"].toDouble();
        for (auto a : skillList) {
            if (a->GetSkillId() == skillID) {
                this->skill = a;
            }
        }
        if (this->skill == NULL) {
            qWarning() << "Could not match saved skill ID " << json["skill"].toDouble() << " with loaded skill list";
        }
    }
    qDebug() << "Loaded decoration from JSON :: " << this->ToString();
}

QString Decoration::ToString() {
    return QString("Decoration=[decoID=%1, name=%2, skill=%3, decoLevel=%4]").arg(QString::number(this->decoID), this->name, this->skill->ToString(), QString::number(this->decoLevel));
}
