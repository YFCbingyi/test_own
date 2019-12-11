#ifndef MY_SHARE_PTR_H
#define MY_SHARE_PTR_H

#include <iostream>
#include <memory>

class Mode;
class my_share_ptr
{
public:
    my_share_ptr();
    void start();
    void set_mode(std::shared_ptr<Mode> st) {
        if(mode_ptr_ != nullptr)
            mode_ptr_.reset();
        mode_ptr_ = st;
    }

private:
    std::shared_ptr<Mode> mode_ptr_;
};

#endif // MY_SHARE_PTR_H
