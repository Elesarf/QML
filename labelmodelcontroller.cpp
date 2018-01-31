#include "labelmodelcontroller.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

LabelModelController::LabelModelController(QObject *parent):
    QObject(parent)
    ,_modelData(new LabelGroupModel(this))
{
}

bool LabelModelController::save(const QString &modelFileName)
{
    QFile file(modelFileName);

    if(!file.open(QIODevice::WriteOnly)) return false;

    QVariantMap map;

    map["Notes"] = _modelData->toVariantList();
    auto doc = QJsonDocument::fromVariant(map);
    file.write(doc.toJson());

    return true;
}

bool LabelModelController::load(const QString &modelFileName)
{
    QFile file(modelFileName);

    if(!file.open(QIODevice::ReadOnly)) return false;

    auto doc = QJsonDocument::fromJson(file.readAll());

    if(!doc.isObject()) return false;

    auto object = doc.object().toVariantMap();
    auto data = object["Notes"].toList();
    emit sizeChanged(data.size());
    return _modelData->fromVariantList(data);
}

void LabelModelController::initDefault(int size)
{
    _modelData->initDefault(size);
    emit sizeChanged(size);
}
