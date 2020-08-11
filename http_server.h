#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "inja/inja.hpp"
#include <QString>
#include <QMessageBox>
#include <QTcpServer>
#include <QHostInfo>
#include <QWidget>
#include <QTcpSocket>

class HttpServer : public QObject
{
    Q_OBJECT
private:
    QTcpServer tcpServer;
    int port;
    void writeHttpAndStr(QTcpSocket *tcpSocket, QString &str);
    void showText(QString str);
public:
    enum ServerType{
      text, file
    };
    HttpServer();
    HttpServer(ServerType, QString &str, QString &qrCodeUrl);
    ~HttpServer();
};

#endif // HTTP_SERVER_H
