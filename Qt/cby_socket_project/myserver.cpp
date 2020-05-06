#include "myserver.h"
#include "ui_myserver.h"
#include <QDebug>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <unistd.h>

myServer::myServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myServer),is_connected_(false)
{
    ui->setupUi(this);
}

myServer::~myServer()
{
    delete ui;
}
void myServer::on_start_clicked()
{
    ui->start->setDisabled(true);
    if(get_socket(ui->port->text().toInt())) {
        is_connected_  = true;
        recv_thd_ = std::thread(&myServer::thd_recv, this);
    } else {
        ui->start->setEnabled(true);
    }
}

bool myServer::get_socket(int port) {
    struct sockaddr_in my_addr; /* my address information */
    struct sockaddr_in their_addr; /* connector's address information */
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        qDebug()<< "socket error";
    }
    qDebug() << "get sockfd";
    my_addr.sin_family = AF_INET; /* host byte order */
    my_addr.sin_port = htons(port); /* short, network byte order */
    my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
    bzero(&(my_addr.sin_zero),0); /* zero the rest of the struct */
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
        qDebug("bind");
    }
    qDebug() << "bing success" ;
    if (listen(sockfd, BACKLOG) == -1) {
        qDebug("listen");
    }
    qDebug() << "listen success";
    socklen_t sin_size;
    sin_size = sizeof(struct sockaddr_in);
    if ((socketfd_ = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
        qDebug("accept");
    if(socketfd_ > 0) {
        qDebug() << "accept success";
        return true;
    }
    return false;
}

void myServer::on_send_clicked()
{
    if(!is_connected_) {
        qDebug() << "socket is not connect,please wait connect";
        return;
    }
    std::string data = get_date(ui->cmd->text().toStdString(),ui->params->text().toStdString());
    if(send(socketfd_, data.c_str(), data.length(), 0) == -1)
        qDebug("send error");
}

std::string myServer::get_date(const std::string cmd, std::string params,int timeout) {
    Json::Value root;
    root["sender"] = "cloud";
    root["ts"] = 10022;
    root["id"] = "16001001";
    root["cmd"] = cmd;
    if(!cmd.compare("audio_control")) {
        Json::Value param;
        param["state"] = params;
        param["timeout"] = timeout;
        root["params"] = param;
    } else if(!cmd.compare("speed")) {

    } else if(!cmd.compare("audio_play")) {
        root["text"] = params;
    }
    std::string str = root.toStyledString();
    std::cout << str << std::endl;
    return str;
}

void myServer::print_json_data(std::string &str) {
    Json::Value root;
    Json::Reader reader;
    try {
        if(reader.parse(str, root)) {
            std::cout << root["cmd"].asString() << std::endl;
            std::cout << root["params"]["state"].asString() << std::endl;
            std::cout << root["params"]["timeout"].asInt() << std::endl;
        }
    } catch(std::exception &e) {
        qDebug("CLOUD_CLIENT : exception : %s",e.what());
    }
}

void myServer::thd_recv() {
    char buf[1024];
    while (is_connected_) {
        bzero(buf,sizeof(buf));
        int size = ::recv(socketfd_,buf,sizeof(buf)-1,0);
        if(size > 0) {
            std::string msg = buf;
            std::cout <<"recv msg : " <<msg << std::endl;
            parse(msg);
        }
    }
}

void myServer::parse(std::string &data) {
    Json::Value root;
    Json::Reader reader;
    try {
        if(reader.parse(data, root)) {
            if(root["cmd"].asString().compare("change_page") == 0) {
                std::string param = root["res"]["param"].asString();
                compose(param);
            }
        }
    } catch(std::exception &e) {
        qDebug("CLOUD_CLIENT : exception : %s",e.what());
    }
}

void myServer::compose(std::string &param) {
    Json::Value root;
    root["sender"] = "ui";
    root["ts"] = 0;
    root["id"] = "100001";
    root["cmd"] = "get_number";
    Json::Value content;
    if(param == "major") {
        content["action"] = "opt_major";
        content["id"] = 1;
//        content["subname"] = "社会保险";
        root["params"] = content;
    } else if (param == "minor") {
        content["action"] = "opt_minor";
        content["id"] = 2;
//        content["subname"] = "事业保险";
        root["params"] = content;
    } else if (param == "read_identity"){
        content["action"] = "opt_input_identity";
        root["params"] = content;
    } else if (param == "input_identity") {
        content["action"] = "get_identity";
        content["number"] = "142202199511100628";
        root["params"] = content;
    } else if (param == "input_phone") {
        content["action"] = "get_phone";
        content["number"] = "15611769175";
        root["params"] = content;
    } else if (param == "success") {
        content["action"] = "cancel";
        root["params"] = content;
    } else if (param == "error") {
        content["action"] = "cancel";
        root["params"] = content;
    }
    Json::FastWriter jwriter;
    std::string msg = jwriter.write(root);
    ::sleep(2);
    std::cout << " send msg "<< msg << std::endl;
    if(send(socketfd_, msg.c_str(), msg.length(), 0) == -1)
        std::cout << "send error" << std::endl;
}
