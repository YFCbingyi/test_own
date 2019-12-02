#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mylogin.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    form_login_ = new myLogin;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_clicked()
{
    check_box_.setUserAgree(true);
}

void MainWindow::on_commandLinkButton_clicked()
{
    if(check_box_.isAgreeConsent()) {

        form_login_->show();
        this->hide();
    } else {
        QMessageBox::warning(NULL, "warning", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}
