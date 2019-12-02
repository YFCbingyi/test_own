#ifndef CPLUSTEST_H
#define CPLUSTEST_H
#include <iostream>
#include "mybind.h"
#include <jsoncpp/json/json.h>
#include "BlockQueue.h"
#include <thread>
#include <cmath>
#include "debug_log.h"

class my_theta;
class my_thread;
class my_template;
class my_time;
class my_json;
class my_vector;
class my_fstream;
class my_share_ptr;
namespace mycplus {
//    class cplustest;
    class cplustest
    {
    public:
        cplustest(){std::cout << "构造函数" << std::endl;}
        ~cplustest(){std::cout << "析构函数" << std::endl;}
        void test();

    private:
        void my_bool_test(bool &flag) {
            flag = !flag;
        }

    private:
        void set_bool_test(bool flag) {
        bool is_bool = false;
            if(is_bool == flag)
                LOG(INFO) << "一样";
            else
                LOG(INFO) << "不一样";
        }

    private:
        void my_template_test();

    private:
        void myjson_test();

    private:
        class Add{
        public:
            Add() : a_(0),b_(0) {}
            Add(int a,int b):a_(a),b_(b) {}

            Add operator+(const Add &A) const {
                Add B;
                B.a_ = this->a_ + A.a_;
                B.b_ = this->b_ + A.b_;
                return B;
            }

            Add & operator+=(const Add &A){
                this->a_ += A.a_;
                this->b_ += A.b_;
                return *this;
            }

            void display() const {
                std::cout << a_ << " : " << b_ << std::endl;
            }
        private:
            int a_;
            int b_;
        };

        void oprator_test(); //运算符重载

    private:
        void type_info_test();

    private:
        void cplusarray_auto(int size);

    private:
        void split_str();

    private:
        void compare_str();

    private:
        my_theta *mthe_;
        void my_theta_test();

    private:
        my_thread *mthd_;
        void my_thread_test();

    private:
        my_time *mtime_;
        void my_time_test();

    private:
        my_json *mjson_;
        void my_json_test();

    private:
        my_vector *mvec_;
        void my_vector_test();

    private:
        my_fstream *mfeam_;
        void my_fstream_test();

    private:
        my_share_ptr *msptr_;
        void my_share_ptr_test();

    private:
        void cplusarray();
        void bind_test();
        void array_test(unsigned int length);
        void show_word(const std::string& text,Json::Value &res);
        void show_string(const std::string& text){std::cout << text << std::endl;}
        void show_json(const Json::Value& text){std::cout <<text.toStyledString()<<std::endl;}
        void show_timeout(){std::cout << " It is time out "<<std::endl;}

        mybind *mbind_;
        my_template *mtemplate_;
    private:
        typedef struct {
            int cmd;
            std::string data;
        }Event;
        void BlockTest();
        void send111111();
        void recv111111();
        BlockQueue<Event>  bq_;
        std::thread thd1_;
        std::thread thd2_;
    };
}



#endif // CPLUSTEST_H
