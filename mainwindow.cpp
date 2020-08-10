#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "message_show.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->plainTextEdit->toPlainText();
    if (str != nullptr && str.length() > 0) {
        MessageShow::showMessage(str);
    }
}
