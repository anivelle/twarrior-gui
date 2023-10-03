#include "ItemModel.h"
#include <iostream>

ItemModel::ItemModel()
    : dataFile(new QFile("~/.twarriorjson")){
    dataFile->open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(dataFile->readAll());
    dataFile->close();
    items = new QJsonArray();
    *items = doc.array();
    process = new QProcess();
}

ItemModel::ItemModel(QFile *data) {
    dataFile = data;
    dataFile->open(QIODevice::ReadOnly);
    QByteArray jsonData = dataFile->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    dataFile->close();
    items = new QJsonArray();
    *items = doc.array();
    process = new QProcess();
    setProcess("task");
}

ItemModel::~ItemModel() {
  delete dataFile;
  delete process;
}

void ItemModel::updateData() {
    dataFile->open(QIODevice::WriteOnly);
}

void ItemModel::setProcess(const QString &program) {
    this->process->setProgram(program);
}

void ItemModel::setArguments(const QStringList &arguments) {
    this->process->setArguments(arguments);
}

QModelIndex ItemModel::index(int row, int column,
                             const QModelIndex &parent) const {
  if (!hasIndex(row, column))
    return QModelIndex();

  QJsonValue *val = new QJsonValue(items->at(row));
  return createIndex(row, column, val);
}

QModelIndex ItemModel::parent(const QModelIndex &child) const {
  return QModelIndex();
}
int ItemModel::rowCount(const QModelIndex &parent) const {
  return items->size();
}
int ItemModel::columnCount(const QModelIndex &parent) const {
  return 1;
}
QVariant ItemModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (role != Qt::DisplayRole)
    return QVariant();

  QJsonValue *val = static_cast<QJsonValue*>(index.internalPointer());
  QJsonObject obj = val->toObject();
  return val->toObject()["description"].toString();
}
bool ItemModel::setData(const QModelIndex &index, const QVariant &value,
                        int role) { }
Qt::ItemFlags ItemModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}
QVariant ItemModel::headerData(int section, Qt::Orientation orientation,
                               int role) const {
  QJsonValue item = items->first();
  QJsonObject arr = item.toObject();
  QJsonValue item2 = arr["description"];
  QJsonObject obj = item2.toObject();
  QStringList keys = obj.keys();

  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return "Temp";

  return QVariant();

}
bool ItemModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role) {}
bool ItemModel::insertRows(int row, int count, const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);
  
  endInsertRows();
  return true;
}
bool ItemModel::removeRows(int row, int count, const QModelIndex &parent) {}
