#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <atomic>


namespace Ui {
class MainWindow;
}

class myLogin;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void show_home() {this->show();}

private slots:
    void on_checkBox_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::MainWindow *ui;

    class checkBox
    {
    public:
        checkBox() {ui_checkBox_ = false;}
        void setUserAgree(bool flag) {ui_checkBox_ = flag;}
        bool isAgreeConsent() {return ui_checkBox_;}
        std::atomic<bool> ui_checkBox_;
    }check_box_;

    myLogin *form_login_;
};

#endif // MAINWINDOW_H
