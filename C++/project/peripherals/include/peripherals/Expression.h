/*************************************************************************
    > File Name: include/peripherals/Expression.h
    > Author: chen bingyi
    > Mail:
    > Created Time: 2019年09月25日 星期三 11时48分23秒
 ************************************************************************/

#ifndef _EXPRESSION_H
#define _EXPRESSION_H

#include "SerialDev.h"
#include <string.h>
#include <iostream>
#include <atomic>
#include "func.h"

#define EX_PORT 10100

class Expression {
public:
    enum EXPTYPES{
        EXP_CONFIDENCE = 0,
        EXP_HAPPY,
        EXP_CRY,
        EXP_BLOWBUBBLE,
        EXP_LICKLIPS,
        EXP_SHUTUP,
        EXP_ANGRY,
        EXP_SUPRISE
    };
    static Expression* getInstance() {
        if(instance_ == nullptr) {
            instance_ = new Expression();
        }
        return instance_;
    }
    int init();
    int display(EXPTYPES type);
    bool show_express(std::string mode);
    bool show_perform(std::string &type);
    bool show_perform(int type);


private:
    Expression();
    ~Expression();

    unsigned char data_[12];
    SerialDev serial_dev_;
    std::atomic<bool> serial_ready_;
    static Expression *instance_;
    std::string mode_;
    RobotType robottype_;
    int socket_;

    int type_;
};
#endif
