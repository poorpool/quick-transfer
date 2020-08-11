#include "http_server.h"

HttpServer::HttpServer() {

}

HttpServer::HttpServer(HttpServer::ServerType serverType, QString &str, QString &qrCodeUrl) {
    if (serverType == HttpServer::ServerType::text) {
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
        QObject::connect(&tcpServer, &QTcpServer::newConnection, this, [str, this](){
            showText(str);
        });
        QMessageBox::information(nullptr, "title", "constructor at " + QString::number(port));
    }
    qrCodeUrl = QString::number(port).prepend("localhost");
}

HttpServer::~HttpServer() {
    tcpServer.close();
    QMessageBox::information(nullptr, "title", "deconstructor");
}

void HttpServer::showText(QString text) {
    QTcpSocket *tcpSocket = tcpServer.nextPendingConnection();
    connect(tcpSocket, &QTcpSocket::readyRead, this, [&](){
        while (tcpSocket->canReadLine()) {
            QByteArray aLine = tcpSocket->readLine();
            if (aLine.left(3).compare("get", Qt::CaseInsensitive) == 0) {
                QList<QByteArray> list = aLine.split(' ');
                inja::Environment env;
                nlohmann::json data;
                if (list[1].compare("/") == 0) {
                    data["text"] = text.toStdString();
                    inja::Template tmpl = env.parse_file("./html/show_text.html");
                    QString str = QString::fromStdString(env.render(tmpl, data));
                    writeHttpAndStr(tcpSocket, str);
                    tcpSocket->close();
                } else if (list[1].startsWith("/static")) {
                    list[1].prepend("./html");
                    inja::Template tmpl = env.parse_file(list[1].toStdString());
                    QString str = QString::fromStdString(env.render(tmpl, data));
                    writeHttpAndStr(tcpSocket, str);
                    tcpSocket->close();
                }
            }
        }
    });
    tcpSocket->waitForReadyRead();
    tcpSocket->close();// 这行代码可能会出现 bug，get 协议不一定能出现，post 大包可能会比较明显
}

void HttpServer::writeHttpAndStr(QTcpSocket *tcpSocket, QString &writeStr) {// add more header
    QString str = "HTTP/1.1 200 OK \r\n";
    str += "\r\n";
    str += writeStr;
    tcpSocket->write(str.toUtf8());
}
