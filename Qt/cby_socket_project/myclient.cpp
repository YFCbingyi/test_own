#include "myclient.h"
#include "ui_myclient.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QDebug>

myClient::myClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myClient)
{
    ui->setupUi(this);
}

myClient::~myClient()
{
    delete ui;
}

void myClient::on_start_clicked()
{
    std::string tx = ui->start->text().toStdString();
    qDebug("tx is %s",tx.c_str());
    if(tx == "start") {
        std::string address = ui->address->text().toStdString();
        int port = ui->port->text().toInt();
        if(sockfd_ = get_client(address,port) > 0) {
            ui->address->setDisabled(true);
            ui->port->setDisabled(true);
            ui->start->setText("stop");
        }
    } else if(tx == "stop") {
        if(sockfd_ > 0)
            ::close(sockfd_);
        ui->address->setDisabled(false);
        ui->port->setDisabled(false);
        ui->start->setText("start");
    }

}

int myClient::get_client(std::string &address,int port) {
        int sockfd;
        struct sockaddr_in serv_addr;

        sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            qDebug() << "Socket error opening socket";
            return -1;
        }
        ::bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        ::inet_aton(address.c_str(), &serv_addr.sin_addr );
        serv_addr.sin_port = htons(port);
        if (::connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
            qDebug("Socket error connecting\n");
            return -1;
        }
        return sockfd;
}
