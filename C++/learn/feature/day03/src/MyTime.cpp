#include "MyTime.h"

#include <iostream>

MyTime::MyTime() {
    hour = 1;
    min = 2;
    sec = 3;
}

MyTime::~MyTime() {

}

void MyTime::add() {
    hour++;
    min++;
    sec++;
}

void MyTime::dele() const{
    // sec = 1;
    std::cout << hour <<"--"<< min <<"--"<< sec << std::endl;;
}

MyTime& MyTime::add_hour(int hour) {
    this->hour += hour;
    return *this;
}


MyTime& MyTime::add_min(int min) {
    this->min += min;
    return *this;
}