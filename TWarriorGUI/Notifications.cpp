#include "Notifications.h"
#include <iostream>

Notification::Notification(QDBusInterface &iface) {
    interface = &iface;
    args = {};
}

Notification::Notification(QDBusInterface &iface, NotificationArgs notif,
                           void (*callback)(unsigned int, QString)) {

    interface = &iface;
    args = notif;
    this->callback = callback;

}

Notification::Notification(QDBusInterface &iface, QString processName,
                           unsigned int id,QString icon, QString summary, QString body,
                            QList<QString> actions,
                           QMap<QString, QVariant> hints, int timeout,
                           void (*callback)(unsigned int, QString)) {
    interface = &iface;
    args = {processName, id, icon, summary, body, actions, hints, timeout};
    this->callback = callback;
}

Notification::~Notification() { interface = NULL; }

bool Notification::Ready() { return interface->isValid(); }

int Notification::Send() {
    if (!interface->isValid())
        return -1;

    if (callback == NULL) {
        QDBusReply<unsigned int> reply = interface->callWithArgumentList(
            QDBus::AutoDetect, "Notify", this->args);
        return reply.value();
    } else {
        return interface->callWithCallback("Notify", this->args, this,
                                           "callback");
    }
}

int Notification::Send(QString processName, unsigned int id, QString icon,
                       QString summary, QString body, QList<QString> actions,
                       QMap<QString, QVariant> hints, int timeout,
                       void (*callback)(unsigned int, QString)) {

    args = {processName, id, icon, summary, body, actions, hints, timeout};
    this->callback = callback;
    if (callback == NULL) {
        QDBusReply<unsigned int> reply = interface->callWithArgumentList(
            QDBus::AutoDetect, "Notify", this->args);
        return reply.value();
    } else {
        return interface->callWithCallback("Notify", this->args, this,
                                           "callback");
    }
    return Send();
}
