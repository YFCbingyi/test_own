#include "my_share_ptr.h"
#include "mode.h"
my_share_ptr::my_share_ptr()
{
    mode_ptr_ = std::make_shared<NormalMode>();
}

void my_share_ptr::test() {
    int i = 10;
    while(i--) {
        mode_ptr_->operation(this);
    }
}

