/*************************************************************************
    > File Name: src/Expression.cpp
    > Author: chen bingyi
    > Mail:
    > Created Time: 2019年09月25日 星期三 11时48分11秒
 ************************************************************************/
#include "peripherals/Expression.h"
#include <iostream>
#include "utils/socketUtils.h"
#include "sys/types.h"
#include "sys/socket.h"
Expression* Expression::instance_ = NULL;

Expression::Expression() : serial_ready_(false),mode_(""),socket_(-1),type_(-1){
    unsigned char data[12] = {0x6A, 0x61, 0x30, 0x2E, 0x76, 0x61, 0x6C, 0x3D, 0x30, 0xFF, 0xFF, 0xFF};
    memcpy(data_, data, sizeof(data));
    this->init();
}

Expression::~Expression(){
    serial_dev_.close();
    serial_ready_ = false;
    if(socket_ > 0)
        netClientUnInit(socket_);
}

int Expression::init() {
    robottype_ = robot_type();
    if(robottype_ == T_XIAORUI) {
        serial_dev_.close();
        if(RET_OK != serial_dev_.open("/dev/expression")) {
            printf("serial dev open fail: /dev/expresssion.\n");
            return -1;
        } else
            printf("serial dev open success.\n");

        if(RET_OK != serial_dev_.init(115200, 8, 'n', 1)) { //todo:
            printf("serial dev init fail.\n");
            return -1;
        } else
            printf("serial dev init success.\n");

        serial_ready_ = true;
    } else if(robottype_ == T_XIAOXUE) {
        socket_ = netClientInit(EX_PORT);
        if(socket_ < 0)
            loge("Expression socket connect error");
    }
    return 0;
}

int Expression::display(EXPTYPES type) {
    int type_ = static_cast<int>(type);
    if(robottype_ == T_XIAORUI) {
        if(serial_ready_) {
            data_[8] = 0x30+type_;
            serial_dev_.write((void*)data_, sizeof(data_)/sizeof(char));
            return 0;
        }
    } else if(robottype_ == T_XIAOXUE) {
        std::string msg("");
        switch (type) {
        case EXP_CONFIDENCE:
            msg = "normal";
            break;
        case EXP_HAPPY:
            msg = "happy";
            break;
        case EXP_CRY:
            msg = "sad";
            break;
        case EXP_BLOWBUBBLE:
        case EXP_LICKLIPS:
            msg = "smile";
            break;
        case EXP_SHUTUP:
        case EXP_ANGRY:
            msg = "angry";
            break;
        case EXP_SUPRISE:
            msg = "surprise";
            break;
        default:
            break;
        }
        if(socket_ > 0)
            return send(this->socket_, msg.c_str(), msg.length(), 0);
        else
            return -1;
    } else {
        printf("serial dev is not initialized.\n");
        return -1;
    }
}

bool Expression::show_express(std::string mode) {
    if(!mode.compare("standby")) {
        if(mode_.empty()) {
            this->display(EXP_LICKLIPS);
            type_ = 4;
        } else if(!mode_.compare("visit")) {
            this->display(EXP_HAPPY);
            type_ = 1;
        } else if(!mode_.compare("server")) {
            this->display(EXP_LICKLIPS);
            type_ = 4;
        } else if(!mode_.compare("charge")) {
            this->display(EXP_CONFIDENCE);
            type_ = 0;
        }
    } else {
        this->display(EXP_CONFIDENCE);
        type_ = 0;
    }
    mode_ = mode;
    return true;
}

bool Expression::show_perform(std::string &type) {
    try{
        int t = std::stoi(type,nullptr,0);
        if(mode_.compare("server"))
            return false;
        if(type_ != t){
            type_ = t;
            this->display(static_cast<EXPTYPES>(t));
        }
        return true;
    }catch(std::exception &e) {

    }
}

bool Expression::show_perform(int type){
    if(type_ != type){
        type_ = type;
        this->display(static_cast<EXPTYPES>(type));
    }
    return true;
}
