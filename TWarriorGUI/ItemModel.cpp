#include "ItemModel.h"
#include <iostream>
#include <QDateTime>
#include <QDir>

void ItemModel::updateData() {
    QByteArray arr = process->readAllStandardOutput();
    QJsonDocument doc = QJsonDocument::fromJson(arr);
    *items = doc.array();
    dataFile->open(QIODevice::WriteOnly);
    dataFile->write(doc.toJson());
    dataFile->close();
    process->close();
}

ItemModel::ItemModel(bool taskwarrior) {
    process = new QProcess();
    items = new QJsonArray();
    showCompleted = false;
    if (taskwarrior) {
        setProcess("task");
        dataFile = new QFile(QDir::homePath() + "/.taskwarrior");
    } else {
        setProcess("timew");
        dataFile = new QFile(QDir::homePath() + "/.timewarrior");
    }
    setArguments(QStringList("export"));
    connect(process, &QProcess::readyReadStandardOutput, this,
            &ItemModel::updateData);
    process->open();
    // QJsonDocument doc = QJsonDocument::fromJson(*data);
    // *items = doc.array();
}

ItemModel::~ItemModel() {
    delete dataFile;
    delete process;
}

void ItemModel::toggleShowCompleted() { showCompleted = !showCompleted; }

void ItemModel::setProcess(const QString &program) {
    process->setProgram(program);
}

void ItemModel::setArguments(const QStringList &arguments) {
    process->setArguments(arguments);
}

QModelIndex ItemModel::index(int row, int column,
                             const QModelIndex &parent) const {
    if (!hasIndex(row, column))
        return QModelIndex();

    if (parent.isValid())
        return QModelIndex();

    QJsonValue val = items->at(row);
    QJsonObject obj = val.toObject();
    QJsonValue *ret = new QJsonValue(obj[keyMap[column]]);
    if (!showCompleted && obj["id"].toInt() == 0)
      return QModelIndex();
    if (!QString("recurring").compare(obj["status"].toString())) 
      return QModelIndex();

    return createIndex(row, column, ret);
}

QModelIndex ItemModel::parent(const QModelIndex &child) const {
    return QModelIndex();
}

int ItemModel::rowCount(const QModelIndex &parent) const {
    return items->size();
}

int ItemModel::columnCount(const QModelIndex &parent) const { return sizeof(keyMap) / sizeof(QString); }

QVariant ItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();

    QJsonValue *val = static_cast<QJsonValue *>(index.internalPointer());
    if (index.column() == 3 || index.column() == 4) {
        QDateTime t =
            QDateTime::fromString(val->toString(), "yyyyMMddTHHmmssZ");
        // std::cout << val->toString().toStdString() <<
        //  t.toString().toStdString() << std::endl;
        return QVariant(t.toString());
    }
    return val->toVariant();
}

bool ItemModel::setData(const QModelIndex &index, const QVariant &value,
                        int role) {
  if (!index.isValid())
    return false;

  QJsonValue *val = static_cast<QJsonValue *>(index.internalPointer());
  QJsonValue newVal = QJsonValue::fromVariant(value);
  val->swap(newVal);

  return true;
}

Qt::ItemFlags ItemModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant ItemModel::headerData(int section, Qt::Orientation orientation,
                               int role) const {
    // QJsonValue item = items->first();
    // QJsonObject arr = item.toObject();
    // QJsonValue item2 = arr["description"];
    // QJsonObject obj = item2.toObject();
    // QStringList keys = obj.keys();

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        QString header = keyMap[section];
        header[0] = header[0].toUpper();
        return header;
    }

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
