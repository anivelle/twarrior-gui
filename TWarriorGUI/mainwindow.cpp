#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ItemModel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QByteArray>
#include <QFile>

QJsonDocument *taskData;

void readJson() {
    QByteArray jsonData;

    *taskData = QJsonDocument::fromJson(jsonData);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QTreeView *tree = ui->treeView;
    taskData = new QJsonDocument();
    // QFile file("/home/alex/.twarriorjson");
    ItemModel *model = new ItemModel(true);
    //model->setArguments({"export", ">", "~/.twarriorjson"});
    tree->setModel(model);

}

MainWindow::~MainWindow() { delete ui; }
