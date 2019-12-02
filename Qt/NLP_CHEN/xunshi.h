#ifndef XUNSHI_H
#define XUNSHI_H
#include <string>
#include <vector>
class xunshi
{
    typedef struct
    {
        int id;
        double x;
        double y;
    }st_msg;

    typedef struct
    {
        std::vector<std::string> push_speech;
        int follow;
        int expression;
        int show;
        std::vector<std::string> leave_speech;
    }st_regionType_msg;
public:
    xunshi();
    void run();

    bool get_area_msg();
    bool set_every_area_msg(std::string &str_);
    bool get_next_node(st_msg &msg);
    static void* move_func_(void *ptr);
    static void* view_func_(void *ptr);
    void set_value(int i);
    int get_id(){return id;}
    void set_id(int i){id = i;}
    void show_msg(std::string msg="govhall");
    bool start_;
    bool view_finished;
    bool move_finished;
    st_msg msg;
private:
    int id;
};

#endif // XUNSHI_H
