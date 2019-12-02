#include "form.h"
#include "ui_form.h"
#include <QDebug>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    initial();
    qDebug() << "start form" <<endl;
//    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::initial()
{
    this->setFixedSize(660,660);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background,QColor("#B1723C"));
    this->setPalette(palette);

    QPainter painter;
    painter.setRenderHint(QPainter::Antialiasing,true);

    QPen pen = painter.pen();
    pen.setColor(QColor("#8D5822"));
    pen.setWidth(7);
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(QColor("EEC085"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(20,40,600,600);

    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    for(int i = 0 ; i < 15 ; i ++)
    {
        painter.drawLine(40+i*40,60,40+i*40,620);
        painter.drawLine(40,60+i*40,600,60+i*40);
    }
}
