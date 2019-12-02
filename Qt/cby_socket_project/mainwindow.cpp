#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myclient.h"
#include "myserver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete server_;
    delete client_;
    delete ui;
}

void MainWindow::on_server_clicked()
{
    server_ = new myServer;
    server_->show();
    this->hide();
}

void MainWindow::on_client_clicked()
{
    client_ = new myClient;
    client_->show();
    this->hide();
}
