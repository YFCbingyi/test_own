#ifndef MY_FSTREAM_H
#define MY_FSTREAM_H
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

class my_fstream
{
public:
    my_fstream();
    enum Mode {
        MD_NONE = 0,
        MD_VISIT,
        MD_LINE,
        MD_PATROL,
        MD_GREETING,
        MD_STANDBY,
        MD_CHARGE,
        MD_RECALL,
        MD_VISION_DEMO,
    };
    typedef struct {
        Mode mode;
        void* data;
    } EventData;

    typedef struct {
        int id;
    }InitData;
    void start() {
        my_fstream_test();
    }
private:
    void my_fstream_test();
private:
    Json::Value read_fstream_str();
    void write_fstream_str(Json::Value &str);
private:
    int read_fstream_int();
    void write_fstream_int(int mode);
    void request_new_mode(Mode mode, int id);

    std::vector<EventData*> bq_;
};

#endif // MY_FSTREAM_H
