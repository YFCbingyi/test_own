#include "mode.h"
#include "debug_log.h"
#include "my_share_ptr.h"
void PlanMode::operation(my_share_ptr *handle) {
    while(true) {
        LOG(INFO) << "1";
        handle->set_mode(std::make_shared<NormalMode>());
        break;
    }
}
