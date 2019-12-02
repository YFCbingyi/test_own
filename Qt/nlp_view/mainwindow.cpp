#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "baidu.h"
#include "tuling.h"
#include "nlpbase.h"
#include "debug_log.h"
#include "unistd.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),baidu_(new Baidu),tuling_(new Tuling)
{
    ui->setupUi(this);
    this->init();
//    this->qus_call_back();
}

MainWindow::~MainWindow()
{
    delete baidu_;
    delete tuling_;
    delete ui;
}

void MainWindow::qus_call_back() {
}

bool MainWindow::init() {
    if(!baidu_->init()) {
        return false;
    }
    tuling_->initial();
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
//    while(true) {
//        sleep(1);
        QString text = ui->lineEdit->text();
        std::string qus = text.toStdString();
        ui->lineEdit->clear();
//        baidu_->start_(qus);
        tuling_->start_(qus);
        std::string end;
        tuling_->get_end_result_msg(end);
//        baidu_->get_end_result_msg(end);
        LOG(INFO) << end;
        ui->textEdit->setText(QString::fromStdString(end));
//    }
    ui->pushButton->setEnabled(true);
}
