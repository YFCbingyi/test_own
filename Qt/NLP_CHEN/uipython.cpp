#include "uipython.h"
#include "ui_uipython.h"
#include "QDebug"
#include "debug_log.h"
uipython::uipython(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uipython)
{
    ui->setupUi(this);
}

uipython::~uipython()
{
    delete ui;
}

void uipython::push_button_clicked()
{
    LOG(INFO) << "1";
    QString sourtext = ui->textEdit->toPlainText();
    qDebug() << sourtext ;
}
void uipython::push_button2_clicked()
{
    LOG(INFO) << "2";
    ui->textEdit->setText("");
}
