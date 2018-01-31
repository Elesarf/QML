#ifndef PINSMODEL_H
#define PINSMODEL_H

#include <QAbstractListModel>

class PinsModel : public QAbstractListModel
{
    Q_OBJECT

public:

    struct Pins {
        Pins() {}
        Pins(const QVariantMap &item):
            group(item["group"].toInt())
            ,address(item["address"].toInt())
            ,maxValue(item["maxValue"].toInt())
            ,minValue(item["minValue"].toInt())
            ,pinType(item["pinType"].toInt())
            ,notes(item["notes"].toString())
        {}

        QVariantMap toVariant() const
        {
            return {
                {"group",QVariant::fromValue(group)},
                {"address",QVariant::fromValue(address)},
                {"maxValue",QVariant::fromValue(maxValue)},
                {"minValue", QVariant::fromValue(minValue)},
                {"pinType", QVariant::fromValue(pinType)},
                {"notes", QVariant::fromValue(notes)}
            };
        }

        enum PinType {
            INPUT,
            OUTPUT
        };

        int group{0};
        int address{0};
        int maxValue{0};
        int minValue{0};
        int pinType{0};
        QString notes;
    };

    using PinsList = QList<Pins>;

    enum Roles {
        GroupRole = Qt::UserRole + 1,
        AddressRole,
        MaxValueRole,
        MinValueRole,
        PinTypeRole,
        NotesRole
    };

    explicit PinsModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE bool fromVariantList(const QVariantList & items);
    Q_INVOKABLE QVariantList toVariantList() const;

    Q_INVOKABLE void initDefault(int size);

private:
    PinsList _data;
};

#endif // PINSMODEL_H
