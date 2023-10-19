#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ItemModel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QByteArray>
#include <QFile>
#include <QtDBus/QtDBus>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QTreeView *tree = ui->treeView;
    ItemModel *model = new ItemModel(true);
    tree->setModel(model);
    QDBusInterface notify("org.freedesktop.Notifications",
                          "/org/freedesktop/Notifications",
                          "org.freedesktop.Notifications");
    QTextStream(stdout) << notify.isValid();
    QDBusReply<QList<QString>> reply = notify.call("GetCapabilities");
    QList<QString> arr;
    QList<QString> arr2;
    QDBusReply<unsigned int> r = notify.call("Notify", "twarrior", 0, "", "summary", "body", arr, arr2, -1);
    qDebug() << notify.lastError();
    qDebug() << r.value();
}

MainWindow::~MainWindow() { delete ui; }
