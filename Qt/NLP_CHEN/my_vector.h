#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include "debug_log.h"
#include "testbase.h"
#define STR(R) #R
class my_vector : public TestBase
{
public:
    my_vector();
    void test() {
        find();
//        create_items();
//        find_items();
    }
private:
    struct Item
    {
        std::string name;
        int id;
    };
    std::vector<struct Item> items_;
    void create_items() {
        struct Item it;
        it.id = 2;
        it.name = "chen";
        items_.push_back(it);
        struct Item it1;
        it1.id = 12;
        it1.name = "bingyi";
        items_.push_back(it1);
    }
    void find_items() {
        for(auto t = items_.begin();t != items_.end();t++) {
            if(t->id == 12) {
                LOG(INFO) << "id " <<t->id << " name "<< t->name;
            }
        }
    }
private:
    //找到vector中是否有某个num
    void find();

private:
    void get_new_plan() {
        plan_ = plan_list_[0];
    }
    typedef struct{
        std::string mode;
        int num;
        std::string time;
    }ExecPlan;
    ExecPlan plan_;
    std::vector<ExecPlan> plan_list_;

private:
    void string_split_test() {
        std::vector<std::string> gspeech_;
        std::string str = "跟着我///发起进攻///请求集合";

        gspeech_ = s_split(str,"///");
        std::cout << "1" << std::endl;
        show_vec(gspeech_);
    }

    //遍历vector
    void show_vec(std::vector<std::string>& list) {
        //1
        for(std::vector<std::string>::const_iterator iter = list.cbegin(); iter != list.cend();iter ++)
            LOG(INFO) << (*iter);
        //2
        for(auto iter = list.cbegin(); iter != list.cend();iter ++)
            LOG(INFO) << (*iter);
    }
    int get_random_number(int min,int max) const {
        return rand() % static_cast<int>(max + 1 - min) + min;
    }

    /*
       用delim指定的正则表达式将字符串in分割，返回分割后的字符串数组
       delim 分割字符串的正则表达式
     */
    std::vector<std::string> s_split(const std::string& in, const std::string& delim) {
        std::regex re{ delim };
        // 调用 std::vector::vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type())
        // 构造函数,完成字符串分割
        return std::vector<std::string> {
            std::sregex_token_iterator(in.begin(), in.end(), re, -1),
                std::sregex_token_iterator()
        };
    }

private:
    void my_float32_vector();

};

#endif // MY_VECTOR_H
