#include "my_share_ptr.h"
#include "mode.h"
my_share_ptr::my_share_ptr()
{
    mode_ptr_ = std::make_shared<NormalMode>();
}

void my_share_ptr::start() {
    int i = 10;
    while(i--) {
        mode_ptr_->run(this);
    }
}

void report(std::shared_ptr<Mode> ptr)
{
    if (ptr) {
        std::cout << "*ptr=" << ptr. << "\n";
    } else {
        std::cout << "ptr is not a valid pointer.\n";
    }
}
