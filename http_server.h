#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "inja/inja.hpp"
#include <QString>
#include <QMessageBox>
#include <QTcpServer>
#include <QHostInfo>
#include <QWidget>

class HttpServer : public QObject
{
    Q_OBJECT
private:
    QTcpServer tcpServer;
    int port;
private slots:
    void onNewConnection();
public:
    HttpServer();
    ~HttpServer();
    void showText(QString text);
};

#endif // HTTP_SERVER_H
