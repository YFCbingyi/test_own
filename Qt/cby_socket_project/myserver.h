#ifndef MYSERVER_H
#define MYSERVER_H

#include <QWidget>
#include <atomic>
#define BACKLOG 10 /*多少等待连接控制*/

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

    std::string get_date(const std::string cmd,std::string params = "",int timeout = 5);

    void print_json_data(std::string &str);

private slots:
    void on_start_clicked();

    void on_send_clicked();

private:
    Ui::myServer *ui;
    int socketfd_;
    std::atomic<bool> is_connected_;
};

#endif // MYSERVER_H
