#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ItemModel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QByteArray>
#include <QFile>
#include <QtDBus/QtDBus>
#include <QVariantList>
#include "Notifications.h"
#include <iostream>

void testFunc() {
  if (true)
    std::cout << "Hello" << std::endl;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QTreeView *tree = ui->treeView;
    QListView *filter = ui->listView;
    ItemModel *model = new ItemModel(true);
    tree->setModel(model);
    // NotificationArgs testNotif = {"twarrior", (unsigned int)0, "", "summary", "body", QList<QString>(), QMap<QString, QVariant>(), -1};
    // QDBusInterface *interface = new QDBusInterface("org.freedesktop.Notifications", "/org/freedesktop/Notifications", "org.freedesktop.Notifications");
    // Notification *notif = new Notification(*interface, testNotif);
    //
    // int r = notif->Send();
    // std::cout << r << std::endl;
}

MainWindow::~MainWindow() { delete ui; }
