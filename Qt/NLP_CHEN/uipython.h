#ifndef uipython_H
#define uipython_H

#include <QWidget>

namespace Ui {
class uipython;
}

class uipython : public QWidget
{
    Q_OBJECT

public:
    explicit uipython(QWidget *parent = 0);
    ~uipython();

private:
    Ui::uipython *ui;

public slots:
    void push_button_clicked();
    void push_button2_clicked();
};

#endif // uipython_H
