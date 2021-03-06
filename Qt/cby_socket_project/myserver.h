﻿#ifndef MYSERVER_H
#define MYSERVER_H

#include <QWidget>
#include <atomic>
#include <thread>
#define BACKLOG 10 /*多少等待连接控制*/
#include <queue>

namespace Ui {
class myServer;
}

class myServer : public QWidget
{
    Q_OBJECT

public:
    explicit myServer(QWidget *parent = 0);
    ~myServer();
private:
    bool get_socket(int port);

    void get_date(const std::string cmd,std::string params = "",int timeout = 5);

    void print_json_data(std::string &str);

    void thd_recv();
    void parse(std::string &data);
    void compose(std::string &param);
    
    void Connect();
    void DisConnect();
    
    void run();
    
    void sendmsg(std::string msg);
    size_t send_with_pkg(std::string msg);
private slots:
    void on_start_clicked();

    void on_send_clicked();

private:
    Ui::myServer *ui;
    int socketfd_;
    std::atomic<bool> is_connected_;
    std::thread recv_thd_;
    
    
    std::thread main_thd_;
    enum class EVENT{
        ET_CONNECT,
    };
    
    std::queue<EVENT> bq_;
};

#endif // MYSERVER_H
