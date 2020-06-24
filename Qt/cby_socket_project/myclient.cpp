#include "myclient.h"
#include "ui_myclient.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>

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
        while(true) {
            sockfd_ = get_client(address,port);
            if(sockfd_ > 0) {
                ui->address->setDisabled(true);
                ui->port->setDisabled(true);
                ui->start->setText("stop");
                recv_thd_ = std::thread(&myClient::thd_recv, this);
                break;
            }    
        }
    } else if(tx == "stop") {
        if(sockfd_ > 0)
            ::close(sockfd_);
        ui->address->setDisabled(false);
        ui->port->setDisabled(false);
        ui->start->setText("start");
    }

}

int myClient::get_client(std::string &ip,int port) {
        int sockfd;
            struct sockaddr_in serv_addr;
        
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0) {
                qDebug("Socket error opening socket");
                goto bail;
            }
            bzero((char *) &serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            if (inet_aton(ip.c_str(), &serv_addr.sin_addr) == 0)
            {
                struct hostent *he;
                he = gethostbyname(ip.c_str());
                if (he == NULL)
                    return -1;
                memcpy(&serv_addr.sin_addr, he->h_addr, sizeof(struct in_addr));
            }
            serv_addr.sin_port = htons(port);
            if (::connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
                qDebug("%s Socket error connecting",ip.c_str());
                goto bail;
            }
            return sockfd;
        bail:
            deleteClient();
            return -1;
}

void myClient::deleteClient() {
    if (sockfd_ > 0)
        ::close(sockfd_);
}

void myClient::on_pushButton_clicked()
{
    std::string data = ui->lineEdit->text().toStdString();
    std::cout << "send "<<data <<" sockfd " << sockfd_ << std::endl;
    if(send(sockfd_, data.c_str(), data.length(), 0) == -1)
        qDebug("send error");
    ui->lineEdit->clear();
}
void myClient::thd_recv() {
    char buf[1024];
    while (true) {
        bzero(buf,sizeof(buf));
        int size = ::recv(sockfd_,buf,sizeof(buf)-1,0);
        if(size > 0) {
            std::string msg = buf;
            std::cout <<"recv msg : " <<msg << std::endl;
        }
    }
}
