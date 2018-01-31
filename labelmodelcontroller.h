#ifndef LABELMODELCONTROLLER_H
#define LABELMODELCONTROLLER_H

#include <QObject>
#include "labelgroupmodel.h"

class LabelModelController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(LabelGroupModel *modelData READ modelData CONSTANT)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

public:
    explicit LabelModelController(QObject *parent = 0);

    Q_INVOKABLE bool save(const QString &modelFileName);
    Q_INVOKABLE bool load(const QString &modelFileName);
    Q_INVOKABLE void initDefault(int size);
    Q_INVOKABLE void add()
    {
        _modelData->add();
        emit sizeChanged(_modelData->rowCount(QModelIndex()));
    }

    Q_INVOKABLE LabelGroupModel *modelData()
    {
        return _modelData;
    }
    Q_INVOKABLE int size()
    {
        return _modelData->rowCount(QModelIndex());
    }

signals:
    void sizeChanged(int size);

private:
    LabelGroupModel *_modelData;
};

#endif // LABELMODELCONTROLLER_H
