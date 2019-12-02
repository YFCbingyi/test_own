#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class myServer;
class myClient;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_server_clicked();

    void on_client_clicked();

private:
    Ui::MainWindow *ui;
    myServer *server_;
    myClient *client_;
};

#endif // MAINWINDOW_H
