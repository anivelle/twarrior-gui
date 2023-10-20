#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QObject>
#include <QtDBus/QtDBus>

typedef struct Notification {
    QString processName;
    unsigned int id;
    QString icon;
    QString summary;
    QString body;
    QList<QString> actions;
    QMap<QString, QVariant> hints;
    int timeout;
    void (*callback)(unsigned int, QString);
} Notification_t;

class NotificationHandler {
  Q_OBJECT;

  private:
    QList<Notification> *notifs;
    QDBusInterface *interface;

  public:
    NotificationHandler();
    ~NotificationHandler();
    bool Start();
    bool Close();
    int AddNotification(Notification notif);
    int AddNotification(QString processName, unsigned int id, QString icon,
                         QString summary, QString body, QList<QString> actions,
                         QMap<QString, QVariant> hints, int timeout, void (*callback)(unsigned int, QString));
    bool SendNotification();
    bool SendNotification(int num);
};

#endif
