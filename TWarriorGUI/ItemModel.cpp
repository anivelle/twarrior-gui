#include "ItemModel.h"

ItemModel::ItemModel()
    : taskFile(new QFile("~/.twarriorjson")),
      timeFile(new QFile("~/.tiwarriorjson")) {}
ItemModel::ItemModel(QFile *file, bool datatype) {
    if (datatype)
        this->taskFile = file;
    else
        this->timeFile = file;
    file->open(QIODevice::ReadOnly);
}

ItemModel::~ItemModel() {}

void ItemModel::updateData() {
    taskFile->open(QIODevice::WriteOnly);
    timeFile->open(QIODevice::WriteOnly);
}

void ItemModel::setProcess(const QString &program) {
    this->process->setProgram(program);
}

void ItemModel::setArguments(const QStringList &arguments) {
    this->process->setArguments(arguments);
}

QModelIndex ItemModel::index(int row, int column,
                             const QModelIndex &parent) const {}
QModelIndex ItemModel::parent(const QModelIndex &child) const {}
int ItemModel::rowCount(const QModelIndex &parent) const {}
int ItemModel::columnCount(const QModelIndex &parent) const {}
QVariant ItemModel::data(const QModelIndex &index, int role) const {}
bool ItemModel::setData(const QModelIndex &index, const QVariant &value,
                        int role) {}
Qt::ItemFlags ItemModel::flags(const QModelIndex &index) const {}
QVariant ItemModel::headerData(int section, Qt::Orientation orientation,
                               int role) const {}
bool ItemModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role) {}
bool ItemModel::insertRows(int row, int count, const QModelIndex &parent) {}
bool ItemModel::removeRows(int row, int count, const QModelIndex &parent) {}
