#include "mylogin.h"
#include "ui_mylogin.h"

myLogin::myLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myLogin)
{
    ui->setupUi(this);
}

myLogin::~myLogin()
{
    delete ui;
}

void myLogin::on_ui_login_login__clicked()
{

}

void myLogin::on_ui_login_regist__clicked()
{

}
