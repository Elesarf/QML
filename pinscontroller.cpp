#include "pinscontroller.h"

#include <QFile>
#include <QVariantList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

PinsController::PinsController(QObject *parent) : QObject(parent)
    ,_pinsDataIn(new PinsModel(this))
    ,_pinsDataOut(new PinsModel(this))
{

}

bool PinsController::load(const QString &fname)
{
    QFile file(fname);
    if(!file.open(QIODevice::ReadOnly)) return false;

    auto doc = QJsonDocument::fromJson(file.readAll());
    if(!doc.isObject()) return false;

    auto object = doc.object().toVariantMap();
    auto pinsIn = object["PinsIn"].toList();
    auto pinsOut = object["PinsOut"].toList();
    return _pinsDataIn->fromVariantList(pinsIn)&&_pinsDataOut->fromVariantList(pinsOut);
}

bool PinsController::save(const QString &fname) const
{
    QFile file(fname);
    if(!file.open(QIODevice::WriteOnly)) return false;

    QVariantMap map;

    map["PinsIn"] = _pinsDataIn->toVariantList();
    map["PinsOut"] = _pinsDataOut->toVariantList();
    auto doc = QJsonDocument::fromVariant(map);
    file.write(doc.toJson());

    return true;
}

void PinsController::initDefault(int size, int sizeOut)
{
    _pinsDataIn->initDefault(size);
    _pinsDataOut->initDefault(sizeOut);
}

PinsModel *PinsController::modelDataIn()
{
    return _pinsDataIn;
}


PinsModel *PinsController::modelDataOut()
{
    return _pinsDataOut;
}
