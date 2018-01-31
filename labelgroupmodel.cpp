#include "labelgroupmodel.h"

LabelGroupModel::LabelGroupModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int LabelGroupModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return _data.size();
}

QVariant LabelGroupModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > _data.size())
        return QVariant();

    const auto item = _data.at(index.row());

    switch (role) {
    case GroupRole :
        return QVariant::fromValue(item.group);
    case NoteRole:
        return QVariant::fromValue(item.note);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> LabelGroupModel::roleNames() const
{
    return {
        {GroupRole, QByteArrayLiteral("group")},
        {NoteRole, QByteArrayLiteral("note")}
    };
}

bool LabelGroupModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() > _data.size()) return false;

    auto row = index.row();

    switch (role) {
    case GroupRole:
        _data[row].group = value.toInt();
        break;
    case NoteRole:
        _data[row].note = value.toString();
        break;
    default:
        return false;
    }

    emit dataChanged(index,index, {role});
    return false;
}

void LabelGroupModel::add()
{
    beginInsertRows(QModelIndex(),_data.size(),_data.size());
    MyLabelStruct item;
    item.group = _data.size() + 1;
    item.note = QString::number(_data.size() + 1).append(" notes");
    _data.append(MyLabelStruct(item));
    endInsertRows();
}

void LabelGroupModel::initDefault(int size)
{
    beginResetModel();
    _data.clear();
    for (int i=0; i<size; ++i) {
        MyLabelStruct mls;
        mls.group = i+1;
        mls.note = QString::number(i+1).append(" notes");
        _data.append(mls);
    }
    endResetModel();
}

bool LabelGroupModel::fromVariantList(const QVariantList &list)
{
    beginResetModel();
    _data.clear();
    for(const auto & item : list) {
        _data.append(MyLabelStruct(item.toMap()));
    }
    endResetModel();

    return true;
}

QVariantList LabelGroupModel::toVariantList() const
{
    QVariantList list;

    for(const auto & item : _data) {
        list.append(item.toVariant());
    }
    return list;
}

Qt::ItemFlags LabelGroupModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}
