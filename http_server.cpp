#include "http_server.h"

void HttpServer::showText(QString text) {

}

HttpServer::HttpServer() {
    QString hostName = QHostInfo::localHostName();
    QMessageBox::information(nullptr, "title", hostName);
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QList<QHostAddress> hostList = hostInfo.addresses();
    for (int i=0; i<hostList.length(); i++) {
        QHostAddress hostAddress = hostList[i];
        QMessageBox::information(nullptr, "title", hostAddress.toString());
    }
    tcpServer.listen(QHostAddress::LocalHost, 0);
    port = tcpServer.serverPort();
    QObject::connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    QMessageBox::information(nullptr, "title", "constructor at " + QString::number(port));
}

HttpServer::~HttpServer() {
    tcpServer.close();
    QMessageBox::information(nullptr, "title", "deconstructor");
}

void HttpServer::onNewConnection() {
    QMessageBox::information(nullptr, "title", " new connection");
}
