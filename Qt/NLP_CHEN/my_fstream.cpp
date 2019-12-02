#include "my_fstream.h"
#include "debug_log.h"

my_fstream::my_fstream()
{

}

void my_fstream::my_fstream_test() {
    request_new_mode(MD_LINE,2);
    if(bq_.size() > 0) {
        EventData* eq;
        eq = bq_[0];
        LOG(INFO) <<"mode " <<eq->mode;
        LOG(INFO) <<"id "<<static_cast<InitData*>(eq->data)->id;
    }
}

int my_fstream::read_fstream_int() {
    std::fstream f;
    int mode = 5;
    f.open("/tmp/.mode",std::ios::in);
    if(!f.is_open()) {
        LOG(INFO) << "open failed";
    } else {
        LOG(INFO) << "open succ";
        f >> mode;
        LOG(INFO) <<"mode" <<mode;
    }
    f.close();
    return mode;
}

void my_fstream::write_fstream_int(int mode) {
    std::fstream f;
    f.open("/tmp/.mode",std::ios::out);
    if(!f.is_open()) {
        LOG(INFO) << "open failed";
    } else {
        LOG(INFO) << "open succ";
        f << mode;
    }
    f.close();
}

Json::Value my_fstream::read_fstream_str() {
    std::fstream f;
    Json::Value str;
    f.open("/tmp/.params",std::ios::in);
    if(!f.is_open()) {
        LOG(INFO) << "open failed";
    } else {
        LOG(INFO) << "open succ";
        f >> str;
        LOG(INFO) <<"str" <<str;
    }
    f.close();
    return str;
}

void my_fstream::write_fstream_str(Json::Value &str)
{
    std::fstream f;
    f.open("/tmp/.params",std::ios::out);
    if(!f.is_open()) {
        LOG(INFO) << "open failed";
    } else {
        LOG(INFO) << "open succ";
        f << str;
    }
    f.close();
}

void my_fstream::request_new_mode(Mode mode, int id){
    InitData* idata = new InitData();
    idata->id = id;

    EventData* ed = new EventData;
    ed->mode = mode;
    ed->data = static_cast<void*>(idata);
    bq_.push_back(ed);
}
