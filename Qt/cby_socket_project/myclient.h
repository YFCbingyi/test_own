#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QWidget>
#include <iostream>
#include <thread>
namespace Ui {
class myClient;
}

class myClient : public QWidget
{
    Q_OBJECT

public:
    explicit myClient(QWidget *parent = 0);
    ~myClient();

private slots:
    void on_start_clicked();

    void on_pushButton_clicked();

private:
    int get_client(std::string &address,int port);
    void thd_recv();
private:
    Ui::myClient *ui;
    int sockfd_;
    std::thread recv_thd_;
};

#endif // MYCLIENT_H
