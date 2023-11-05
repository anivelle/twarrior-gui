#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QObject>
#include <QtDBus/QtDBus>

typedef QList<QVariant> NotificationArgs;

class Notification : QObject {
    Q_OBJECT;

  private:
    NotificationArgs args;
    void (*callback)(unsigned int, QString);
    QDBusInterface *interface;

  public:
    Notification(QDBusInterface &iface);
    Notification(QDBusInterface &iface, NotificationArgs notif,
                 void (*callback)(unsigned int, QString) = NULL);
    Notification(QDBusInterface &iface, QString processName, unsigned int id,
                 QString icon, QString summary, QString body,
                 QList<QString> actions, QMap<QString, QVariant> hints,
                 int timeout = -1,
                 void (*callback)(unsigned int, QString) = NULL);
    ~Notification();
    bool Ready();

    int Send();
    int Send(QString processName, unsigned int id, QString icon,
             QString summary, QString body, QList<QString> actions,
             QMap<QString, QVariant> hints, int timeout,
             void (*callback)(unsigned int, QString) = NULL);
};

#endif
