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
#include "cloudserver.h"

uint32_t get_crc32(const char *buf,uint32_t len) {
    static const uint32_t crc32tab[] = {
        0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL,
        0x076dc419L, 0x706af48fL, 0xe963a535L, 0x9e6495a3L,
        0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L,
        0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L, 0x90bf1d91L,
        0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
        0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L,
        0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL,
        0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L,
        0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L, 0xa2677172L,
        0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
        0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L,
        0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L,
        0x26d930acL, 0x51de003aL, 0xc8d75180L, 0xbfd06116L,
        0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
        0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
        0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL,
        0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL,
        0x71b18589L, 0x06b6b51fL, 0x9fbfe4a5L, 0xe8b8d433L,
        0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L,
        0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
        0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL,
        0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L,
        0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL, 0xfcb9887cL,
        0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L,
        0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
        0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL,
        0x4369e96aL, 0x346ed9fcL, 0xad678846L, 0xda60b8d0L,
        0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L,
        0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L,
        0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
        0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L,
        0x59b33d17L, 0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL,
        0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL,
        0xead54739L, 0x9dd277afL, 0x04db2615L, 0x73dc1683L,
        0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
        0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L,
        0xf00f9344L, 0x8708a3d2L, 0x1e01f268L, 0x6906c2feL,
        0xf762575dL, 0x806567cbL, 0x196c3671L, 0x6e6b06e7L,
        0xfed41b76L, 0x89d32be0L, 0x10da7a5aL, 0x67dd4accL,
        0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
        0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L,
        0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
        0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L,
        0xdf60efc3L, 0xa867df55L, 0x316e8eefL, 0x4669be79L,
        0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
        0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL,
        0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L,
        0xc2d7ffa7L, 0xb5d0cf31L, 0x2cd99e8bL, 0x5bdeae1dL,
        0x9b64c2b0L, 0xec63f226L, 0x756aa39cL, 0x026d930aL,
        0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
        0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L,
        0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L,
        0x86d3d2d4L, 0xf1d4e242L, 0x68ddb3f8L, 0x1fda836eL,
        0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L,
        0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
        0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
        0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L,
        0xa7672661L, 0xd06016f7L, 0x4969474dL, 0x3e6e77dbL,
        0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L, 0x37d83bf0L,
        0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
        0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L,
        0xbad03605L, 0xcdd70693L, 0x54de5729L, 0x23d967bfL,
        0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L,
        0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL
    };

    uint32_t i, crc;
    crc = 0xFFFFFFFF;
    for (i = 0; i < len; i++)
        crc = crc32tab[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
    return crc^0xFFFFFFFF;
}


myServer::myServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myServer),is_connected_(false)
{
    ui->setupUi(this);
    main_thd_ = std::thread(&myServer::run,this);
}

myServer::~myServer()
{
    delete ui;
    if(recv_thd_.joinable())
        recv_thd_.join();
}

void myServer::Connect() {
    ui->start->setDisabled(true);
    is_connected_ = true;
}
void myServer::DisConnect() {
    ui->start->setEnabled(true);
    is_connected_ = false;
}

void myServer::run() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(bq_.empty())
            continue;
        EVENT event = bq_.front();
        bq_.pop();
        switch (event) {
        case EVENT::ET_CONNECT:
            if(recv_thd_.joinable())
                recv_thd_.join();
            recv_thd_ = std::thread(&myServer::thd_recv, this);
            break;
        default:
            break;
        }
    }
}

void myServer::on_start_clicked()
{
    bq_.push(EVENT::ET_CONNECT);
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
    get_date(ui->cmd->text().toStdString(),ui->params->text().toStdString());
    
}

void myServer::get_date(const std::string cmd, std::string params,int timeout) {
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
        sendmsg(root.toStyledString());
    } else if(!cmd.compare("speed")) {
        root["speed"] = params; 
        sendmsg(root.toStyledString());
    } else if(!cmd.compare("audio_play")) {
        root["text"] = params;
        sendmsg(root.toStyledString());
    } else if(cmd == "download") {
        CloudServer cloud;
        send_with_pkg(cloud.download_face_data());
    } else {
        sendmsg(root.toStyledString());
    }
}

void myServer::sendmsg(std::string str) {
    if(send(socketfd_, str.c_str(), str.length(), 0) == -1)
        qDebug("send error");
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
    if(get_socket(ui->port->text().toInt())) {
        this->Connect();
    } else {
        this->DisConnect();
    }    
    char buf[1024];
    unsigned int recvlength, length;
        bool first = true;
        std::string msg;
    while (is_connected_) {
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//        bzero(buf,sizeof(buf));
//        int size = ::recv(socketfd_,buf,sizeof(buf)-1,0);
//        if(size > 0) {
//            std::string msg = buf;
//            std::cout <<"recv msg : " <<msg << std::endl;
//            parse(msg);
//        } else if(size == 0) {
//            this->DisConnect();
//        }
    
            char data[10000];
                    int bytenums = recv(socketfd_, data, sizeof(data), 0);
                    if (bytenums == 0)
                    {
                        printf("disconnected");
                        return;
                    }
                    else if (bytenums > 0)
                    {
                        recvlength += bytenums;
                        std::cout << "recv data "<<  bytenums;
                        data[bytenums] = '\0';
                        if (first)
                        {
                            unsigned int header = (unsigned char)data[0] << 24 | (unsigned char)data[1] << 16 | (unsigned char)data[2] << 8 | (unsigned char)data[3];
                            if (header == 0x5aa55aa5)
                            {
                                first = false;
                                printf("this is first\n");
                            }
                            length = (unsigned char)data[4] << 24 | (unsigned char)data[5] << 16 | (unsigned char)data[6] << 8 | (unsigned char)data[7];
                            std::cout << "length "<< length<<std::endl;
                            std::string a = std::string(data + 12);
                            msg += a;
                        }
                        else
                        {
                            std::cout << "recvlength "<< recvlength<< std::endl;
                            std::string a = std::string(data);
                            msg += a;
                        }
                        if (recvlength >= length)
                        {
                            unsigned int crc = (unsigned char)data[bytenums - 4] << 24 | (unsigned char)data[bytenums - 3] << 16 | (unsigned char)data[bytenums - 2] << 8 | (unsigned char)data[bytenums - 1];
                            printf("recv crc %x\n", crc);
                            std::cout << " recv finished " << std::endl;
                            msg = msg.substr(0, msg.length() - 4);
                            std::cout << msg << std::endl;
                            uint32_t c = get_crc32(msg.c_str(), msg.length());
                            printf("get crc %x\n", c);
                            if (c == crc)
                            {
                                std::cout << " check success" << std::endl;
                            }
                            else
                            {
                                std::cout << " check failed" << std::endl;
                            }
                            return;
                        }
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

size_t myServer::send_with_pkg(std::string msg) {
    uint32_t crc = get_crc32(msg.data(), msg.length());
        printf("%x\n", crc);
        unsigned char crc32[4] = {0};
        crc32[0] = (crc >> 24) & 0xff;
        crc32[1] = (crc >> 16) & 0xff;
        crc32[2] = (crc >> 8) & 0xff;
        crc32[3] = crc & 0xff;
        unsigned char header[12] = {0x5a, 0xa5, 0x5a, 0xa5, 0, 0, 0, 0, 0x00, 0xa1, 0xa1, 0xa1};
        header[4] = ((msg.length() + 16) >> 24) & 0xff;
        header[5] = ((msg.length() + 16) >> 16) & 0xff;
        header[6] = ((msg.length() + 16) >> 8) & 0xff;
        header[7] = (msg.length() + 16) & 0xff;
        char *info = (char *)malloc(msg.length() + 16);
        memcpy(info, (char *)header, 12);
        memcpy(info + 12, msg.c_str(), msg.length());
        memcpy(info + 12 + msg.length(), (char *)crc32, 4);
        size_t len = send(socketfd_, info, msg.length() + 16, 0);
        free(info);
        return len;
}