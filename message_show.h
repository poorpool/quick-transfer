#ifndef MESSAGE_SHOW_H
#define MESSAGE_SHOW_H

#include "qrencode/qrencode.h"
#include "http_server.h"
#include <QString>
#include <QLabel>
#include <QPainter>
#include <QDialog>
#include <QVBoxLayout>
#include <QMessageBox>

class MessageShow {
public:
    static void showMessage(QString qrCodeUrl);
};

#endif // MESSAGE_SHOW_H
