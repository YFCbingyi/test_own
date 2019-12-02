#ifndef MYLOGIN_H
#define MYLOGIN_H

#include <QWidget>

namespace Ui {
class myLogin;
}

class myLogin : public QWidget
{
    Q_OBJECT

public:
    explicit myLogin(QWidget *parent = 0);
    ~myLogin();

private slots:
    void on_ui_login_login__clicked();

    void on_ui_login_regist__clicked();

private:
    Ui::myLogin *ui;
};

#endif // MYLOGIN_H
