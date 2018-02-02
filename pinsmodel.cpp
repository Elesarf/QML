#include "pinsmodel.h"

PinsModel::PinsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int PinsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return _data.size();
}

QVariant PinsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > _data.size())
        return QVariant();

    auto item = _data.at(index.row());

    switch (role) {
    case GroupRole:
        return QVariant::fromValue(item.group);
    case AddressRole:
        return QVariant::fromValue(item.address);
    case MaxValueRole:
        return QVariant::fromValue(item.maxValue);
    case MinValueRole:
        return QVariant::fromValue(item.minValue);
    case NotesRole:
        return QVariant::fromValue(item.notes);
    case PinTypeRole:
        return QVariant::fromValue(item.pinType);
    default:
        return  QVariant();
    }
}

QHash<int, QByteArray> PinsModel::roleNames() const
{
    return {
        {GroupRole,QByteArrayLiteral( "group")},
        {AddressRole,QByteArrayLiteral("address")},
        {MaxValueRole, QByteArrayLiteral("maxValue")},
        {MinValueRole,QByteArrayLiteral("minValue")},
        {PinTypeRole,QByteArrayLiteral("pinType")},
        {NotesRole,QByteArrayLiteral("notes")}
    };
}

bool PinsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.row() > _data.size()) return false;

    auto row = index.row();

    switch (role) {
    case GroupRole:
        _data[row].group  = value.toInt();
        break;
    case AddressRole:
        _data[row].address = value.toInt();
        break;
    case NotesRole:
        _data[row].notes = value.toString();
        break;
    case PinTypeRole:
        _data[row].pinType = value.toInt();
        break;
    default:
        return false;
    }
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

Qt::ItemFlags PinsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

bool PinsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return false;
}

bool PinsModel::fromVariantList(const QVariantList &list)
{
    beginResetModel();
    _data.clear();

    for (const auto &item:list) {
        _data.append(Pins(item.toMap()));
    }
    endResetModel();
    return true;
}

QVariantList PinsModel::toVariantList() const
{
    QVariantList list;
    for (const auto &item:_data) {
        list.append(item.toVariant());
    }
    return list;
}

void PinsModel::initDefault(int size)
{
    beginResetModel();
    _data.clear();
    for (int i = 0; i < size; ++i) {
        Pins p;
        p.address = i;
        _data.append(p);
    }
    endResetModel();
}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
