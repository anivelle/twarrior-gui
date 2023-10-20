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
#include <QVariantList>

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
    // QDBusArgument *args = new QDBusArgument();
    QString name = "twarrior";
    unsigned int notif = 0;
    QString icon = "";
    QString summary = "summary";
    QString body = "body";
    QList<QString> actions;
    QMap<QString, QVariant> hints;
    int timeout = -1;
    QList<QVariant> args = {name, notif, icon, summary, body, actions, actions, timeout};
    QDBusReply<unsigned int> r = notify.call("Notify", name, notif, icon, summary, body, actions, hints, timeout);
    qDebug() << notify.lastError();
    qDebug() << r.value();
}

MainWindow::~MainWindow() { delete ui; }
