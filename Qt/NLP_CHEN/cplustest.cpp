#include "cplustest.h"
#include <array>
#include <functional>
#include <unistd.h>
#include <typeinfo>
#include "debug_log.h"
#include "my_template.h"
#include "my_thread.h"
#include "my_theta.h"
#include "my_time.h"
#include "my_json.h"
#include "my_vector.h"
#include "my_fstream.h"
#include "my_share_ptr.h"
#include "my_string.h"

using namespace mycplus;

void cplustest::test(){
    my_string_test();
}

void cplustest::bind_test() {
    mbind_ = mybind::getInstance(std::bind(&cplustest::show_word,this,std::placeholders::_1,std::placeholders::_2));
    mbind_->regist_Json_ontime_cb(std::bind(&cplustest::show_json,this,std::placeholders::_1));
    mbind_->regist_string_ontime_cb(std::bind(&cplustest::show_string,this,std::placeholders::_1));
    mbind_->regist_time(std::bind(&cplustest::show_timeout,this));
    mbind_->run();

}

void cplustest::show_word(const std::string& text,Json::Value &res) {
    res["good"] = "lasss";
    res["nlp"] = "nlp";
    std::cout << " ++++++++ " << text << "----------" << std::endl;
}

void cplustest::cplusarray() {
    std::array<int,3> arr;
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    std::cout <<" size :" <<arr.size()
             <<" arr[1] :" << arr.at(1)
            <<std::endl;
    for(int i : arr)
        std::cout << i << std::endl;
    std::array<std::string,3> str = {"I","LOVE","CHINA"};
    std::cout <<" size :" <<str.size()
             <<" str[1] :" << str.at(1)
            <<std::endl;
    for(std::string s : str)
        std::cout << s << std::endl;
}

void cplustest::BlockTest() {
    thd1_ = std::thread(&cplustest::send111111, this);
    thd2_ = std::thread(&cplustest::recv111111, this);
    thd1_.join();
    thd2_.join();
}

void cplustest::send111111() {
    int i = 0;
    while(true) {
        Event evt;
        evt.cmd = i;
        bq_.push(evt);
        std::cout << "send "<<i <<std::endl;
//        sleep(1);
        i++;
    }
}

void cplustest::recv111111() {
    while(true) {
        Event evt;
        evt = bq_.pop();
        std::cout << "recv "<<evt.cmd << std::endl;
    }
}

void cplustest::cplusarray_auto(int size) {
    struct student
    {
        std::string name;
        int id;
    };
    std::array<struct student, 2> nursery;//必须常量表达式
    struct student st;
    st.id = 11;
    st.name = "chen";
    nursery[0] = st;
    st.id = 1;
    st.name = "bingyi";
    nursery[1] = st;
    for(struct student n : nursery)
        std::cout << n.id << "  " << n.name <<std::endl;
}

void cplustest::array_test(unsigned int length) {
    unsigned char str[8+length] = {0x1d,0x28,0x6b,static_cast<unsigned char>(length),0x00,0x31,0x50,0x30};
    for(int i = 0;i < static_cast<int>(length);i++) {
        str[8+i] = i;
    }
    for(int i = 0 ; i < sizeof(str); i++) {
        printf("%d : %x\n",i,str[i]);
    }
}

void cplustest::split_str() {
    std::string str = "陈炳邑|男|汉|19951110|山西省原平市西镇乡阳房村4队21号|142202199511100618|原平市公安局|20120611-20220611";
    std::size_t found  = str.find_first_of("|");
    std::string name = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    std::string sex = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    std::string nation = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    std::string birthday = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    std::string address = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    std::string cardid = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    std::string issuing_authority = str.substr(0,found);
    str = str.substr(found+1,str.length());
    std::string useful_life = str;
    std::cout << name << sex << nation << birthday << address << cardid << issuing_authority << useful_life << std::endl;
}

void cplustest::compare_str() {
    std::string str = "chenbingyi";
    if(str == "chenbingyi") {
        std::cout << " == " << std::endl;
    } else {
        std::cout << " != " << std::endl;
    }
}

void cplustest::type_info_test() {
    const std::type_info &tinfo = typeid(this);
    std::cout << "this type: "<<tinfo.name() <<"|"<<tinfo.hash_code()<<std::endl;
    Event event;
    const std::type_info &einfo = typeid(event);
    std::cout << "event type: "<<einfo.name() <<"|"<<einfo.hash_code()<<std::endl;
}

void cplustest::oprator_test() {
    Add A(3,3);
    A.display();
    Add B(1,5);
    B.display();
    Add C(2,4);
    C = C+B;
    C.display();
    C+=A;
    C.display();
}

void cplustest::myjson_test() {
    Json::Value root;
    std::string test = "notnull";
    root["test"] = "";
    if(root["test"].asString().empty()) {
        LOG(INFO) << "test is empty";
    } else {
        LOG(INFO) << "test is not empty";
    }
    if(root["nlp"].asString().empty()) {
        LOG(INFO) << "nlp is empty";
    } else {
        LOG(INFO) << "nlp is not empty";
    }
}

void cplustest::my_template_test() {
    mtemplate_ = new my_template;
    mtemplate_->run();
}

void cplustest::my_thread_test() {
    mthd_ = new my_thread;
    mthd_->start();
}

void cplustest::my_theta_test() {
    mthe_ = new my_theta;
    mthe_->start();
}

void cplustest::my_time_test() {
    mtime_ = new my_time;
    mtime_->start();
}

void cplustest::my_json_test() {
    mjson_ = new my_json;
    mjson_->start();
}

void cplustest::my_vector_test() {
    mvec_ = new my_vector;
    mvec_->start();
}

void cplustest::my_fstream_test() {
    mfeam_ = new my_fstream;
    mfeam_->start();
}

void cplustest::my_share_ptr_test() {
    msptr_ = new my_share_ptr;
    msptr_->start();
}

void cplustest::my_string_test() {
    mstr_ = new my_string;
    mstr_->start();
}
