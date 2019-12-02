#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Baidu;
class Tuling;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool init();
    void qus_call_back();
private:
    Ui::MainWindow *ui;
    Baidu *baidu_;
    Tuling *tuling_;

private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
