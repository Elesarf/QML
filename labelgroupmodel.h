#ifndef LABELGROUPMODEL_H
#define LABELGROUPMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QDebug>
#include <QList>

class LabelGroupModel : public QAbstractListModel
{
    Q_OBJECT

public:

    struct MyLabelStruct {

        MyLabelStruct() {}

        MyLabelStruct(const QVariantMap &item):
            group(item["group"].toInt())
            ,note(item["note"].toString())
        {}

        QVariantMap toVariant() const
        {
            return {
                {"group",QVariant::fromValue(group)},
                {"note",QVariant::fromValue(note)}
            };
        }

        int group{0};
        QString note;
    };

    using MyLabelList = QList<MyLabelStruct>;

    enum Roles {
        GroupRole = Qt::UserRole + 1,
        NoteRole
    };

    explicit LabelGroupModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE void add();
    Q_INVOKABLE void initDefault(int size);

    bool fromVariantList(const QVariantList &list);
    QVariantList toVariantList() const;

private:
    MyLabelList _data;
};

#endif // LABELGROUPMODEL_H
