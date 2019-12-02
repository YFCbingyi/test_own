#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPainter>
#include <QPen>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void initial();

private:
    Ui::Form *ui;
};

#endif // FORM_H
