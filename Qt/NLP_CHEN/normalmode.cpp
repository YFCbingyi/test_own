#include "mode.h"
#include "debug_log.h"
#include "my_share_ptr.h"
void NormalMode::operation(my_share_ptr *handle) {
    while (true) {
        LOG(INFO) << "2";
        handle->set_mode(std::make_shared<PlanMode>());
        break;
    }
}
