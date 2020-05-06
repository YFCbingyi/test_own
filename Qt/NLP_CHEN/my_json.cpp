#include "my_json.h"
#include "exception"
#include "fstream"

my_json::my_json()
{

}

bool my_json::init_script(const std::string& path) {
    Json::Value root;
    Json::Reader reader;
    std::ifstream ifs(path.c_str(), std::ios::binary);
    try {
        if(!reader.parse(ifs, root)) {
            std::cout << "Gamer::failed to open file:" << path << std::endl;
            return false;
        }
        script_.subject_num = root["subject_num"].asInt();
        script_.alarm = root["alarm"].asInt();
        script_.QRcode = root["QRcode"].asString();
        script_.error_speak = root["error_speak"].asString();
        script_.right_speak = root["right_speak"].asString();
        script_.subjects.clear();

        Json::Value& jaction = root["subjects"];
        for(int i=0; i<jaction.size(); i++) {
            if(!jaction[i]["item"].isNull() && !jaction[i]["option"].isNull() && !jaction[i]["answer"].isNull() && !jaction[i]["time_count"].isNull()){
                const Json::Value option = jaction[i]["option"];
                const Json::Value answer = jaction[i]["answer"];
                Subject subject;
                std::vector<std::string> options;
                std::vector<std::string> answers;
                for(int index=0; index < option.size(); index++){
                    options.push_back(option[index].asString());
                }
                for(int index=0; index < answer.size(); index++){
                    answers.push_back(answer[index].asString());
                }
                subject.item = jaction[i]["item"].asString();
                subject.option = options;
                subject.answer = answers;
                subject.time_count = jaction[i]["time_count"].asInt();
                script_.subjects.push_back(subject);
            }
        }
    } catch (std::exception& ex) {
        return false;
    }

    return true;
}

void my_json::create_json(std::string &path) {
    Json::Value params1;
    params1["name"] = "CCC";
    params1["type"] = "Type";
    params1["aaa"] = "look";
    Json::Value params2;
    params2["name"] = "BBB";
    params2["type"] = "AType";
    params2["aaa"] = "look";
    Json::Value params3;
    params3["name"] = "AAA";
    params3["type"] = "OneType";
    params3["aaa"] = "look";
    Json::Value root;
    root.append(params1);
    root.append(params2);
    root.append(params3);
    Json::StyledWriter jw;
    std::ofstream os;
    os.open(path);
    os<<jw.write(root);
    os.close();
}

Json::Value my_json::create_json() {
    Json::Value root;
    root["res"][0]["name"] = "CCC";
    root["res"][0]["type"] = "ccc";
    root["res"][1]["name"] = "BBB";
    root["res"][1]["type"] = "bbb";
    root["res"][2]["name"] = "AAA";
    root["res"][2]["type"] = "aaa";
    return root;
}
