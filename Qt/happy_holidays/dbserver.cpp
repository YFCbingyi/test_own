#include "dbserver.h"

bool DBserver::init(string &path) {
    db_path_ = path;
    return 0;
}

