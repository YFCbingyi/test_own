#include "cloudserver.h"
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string.h>
CloudServer::CloudServer()
{
    
}

std::string CloudServer::download_face_data() {
    std::ifstream is("/home/cby/js111",std::ios_base::binary);
    if(!is.is_open()) {
        std::cerr << "open failed" << std::endl;
        return "";
    }
    Json::Value root;
    Json::Reader Reader;
    if(!Reader.parse(is,root)) {
        std::cerr << "wrong json " << std::endl;
        return "";
    }
    return root.toStyledString();
}
