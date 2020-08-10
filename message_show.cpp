#include "message_show.h"

void MessageShow::showMessage(QString qrCodeUrl) {
    QRcode *qrcode = QRcode_encodeString(qrCodeUrl.toStdString().c_str(), 2, QR_ECLEVEL_H, QR_MODE_8, 1);
    QLabel *qLabel = new QLabel();
    qint32 qrcodeWidth = qrcode->width > 0 ? qrcode->width : 1;// 二维码一行有多少个黑白点
    qint32 qrcodeLength = qMax(300, qMin(1000, qrcodeWidth * 5));// 生成二维码的大小
    QMessageBox::information(nullptr, "title", QString::number(qrcodeWidth));
    double scale = (double) qrcodeLength / qrcodeWidth;
    QImage mainimg = QImage(qrcodeLength, qrcodeLength, QImage::Format_ARGB32);
    QPainter painter(&mainimg);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, qrcodeLength, qrcodeLength);
    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    for (qint32 y=0; y < qrcodeWidth; y++) {
        for (qint32 x=0; x < qrcodeWidth; x++) {
            unsigned char b = qrcode->data[y * qrcodeWidth + x];
            if (b & 0x01) {
                QRectF r(x*scale, y*scale, scale, scale);
                painter.drawRects(&r,1);
            }
        }
    }

    QPixmap mainmap=QPixmap::fromImage(mainimg);

    qLabel->setPixmap(mainmap);

    QDialog *qDialog = new QDialog();
    qDialog->setWindowTitle("扫描二维码");
    QVBoxLayout *qVBoxLayout = new QVBoxLayout();
    qVBoxLayout->addWidget(qLabel);

    HttpServer httpserver;

    qDialog->setLayout(qVBoxLayout);

    qDialog->exec();
}
