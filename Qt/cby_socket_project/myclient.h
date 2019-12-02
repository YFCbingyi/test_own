#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QWidget>

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

private:
    int get_client(std::string &address,int port);

private:
    Ui::myClient *ui;
    int sockfd_;
};

#endif // MYCLIENT_H
