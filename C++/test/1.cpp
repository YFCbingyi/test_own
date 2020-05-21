/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年05月19日 星期二 15时42分37秒
 ************************************************************************/

#include<iostream>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <string.h>
#include <exception>
#include <string>

using namespace std;

bool sync_feature_info(std::string &info) {
    Json::Value root;
    Json::Reader reader;
    try {
        if(!reader.parse(info,root)) {
            return false;
        }
        int num = root["FeatureInfo"].size();
        std::cout << "num " << num << std::endl;
        for(int i = 0 ; i < num ; i++) {
            int userid = root["FeatureInfo"][i]["UserId"].asInt();
            int faceid = root["FeatureInfo"][i]["FaceId"].asInt();
            std::cout << "face id "<< faceid << "  userid" << userid << std::endl;
            std::string RobotID = root["FeatureInfo"][i]["robotID"].asString();
            std::string imagepath = root["FeatureInfo"][i]["ImagePath"].asString();
            std::string facefeature = root["FeatureInfo"][i]["FaceFeature"].asString();
            std::string date = root["FeatureInfo"][i]["Date"].asString();
            std::string type = root["FeatureInfo"][i]["Type"].asString();

            std::string update = "insert into FeatureInfo (RobotId,UserId, FaceId, ImagePath, FaceFeature, Date, Type,upload) values('"+RobotID+"',"+std::to_string(userid)+","+std::to_string(faceid)+",'"+imagepath+"','"+facefeature+"','"+date+"','"+type+"',5)";
            std::cout << update << std::endl; 
        }
    } catch(std::exception &e) {
    }
    return true;
}

std::string download_face_data() {
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

int main() {
    std::string data = download_face_data();
    std::cout << data << std::endl;
    sync_feature_info(data);

    return 0;
}
