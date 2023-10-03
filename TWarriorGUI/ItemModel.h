#ifndef __ITEMMODEL_H
#define __ITEMMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QModelIndex>
#include <QFile>
#include <QProcess>

typedef struct task {

} Task;

class ItemModel : public QAbstractItemModel {
  Q_OBJECT 

  public:
    ItemModel();
    explicit ItemModel(QFile *data);
    ~ItemModel();
    void updateData();
    void setProcess(const QString &program);
    void setArguments(const QStringList &arguments);
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int row, int count,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count,
                    const QModelIndex &parent = QModelIndex()) override;
  private:
    QJsonArray *items;

    QFile *dataFile;
    QProcess *process;
};

#endif
