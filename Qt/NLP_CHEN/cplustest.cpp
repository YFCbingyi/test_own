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
#include "my_resolver.h"
#include <python2.7/Python.h>
#include "testbase.h"
#include "cpluselevennewfeaturetest.h"
using namespace mycplus;

void cplustest::test(){
   cplusTest();
}

// C++11 新特性测试
void cplustest::cplusTest() {
    test_ptr_ = std::make_shared<CPlusElevenNewFeatureTest>();
    test_ptr_->test();
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
    test_ptr_ = std::make_shared<my_template>();
    test_ptr_->test();
}

void cplustest::my_thread_test() {
    test_ptr_ = std::make_shared<my_thread>();
    test_ptr_->test();
}

void cplustest::my_theta_test() {
    test_ptr_ = std::make_shared<my_theta>();
    test_ptr_->test();
}

void cplustest::my_time_test() {
    test_ptr_ = std::make_shared<my_time>();
    test_ptr_->test();
}

void cplustest::my_json_test() {
    test_ptr_ = std::make_shared<my_json>();
    test_ptr_->test();
}

void cplustest::my_vector_test() {
    test_ptr_ = std::make_shared<my_vector>();
    test_ptr_->test();
}

void cplustest::my_fstream_test() {
    test_ptr_ = std::make_shared<my_fstream>();
    test_ptr_->test();
}

void cplustest::my_share_ptr_test() {
    test_ptr_ = std::make_shared<my_share_ptr>();
    test_ptr_->test();
}

void cplustest::my_string_test() {
    test_ptr_ = std::make_shared<my_string>();
    test_ptr_->test();
}

void cplustest::my_python_test() {
//    std::string cmd = "python /home/cby/rsData/log/analysisLog.py";
//    run_cmd(cmd);
    Py_Initialize();//使用python之前，要调用Py_Initialize();这个函数进行初始化
        PyRun_SimpleString("import sys");
//        PyRun_SimpleString("sys.argv[20200101,20200110]");
//        PyRun_SimpleString("sys.path.append('.//home/cby/rsData/log/')");
        if (PyRun_SimpleString("execfile('/home/cby/rsData/log/analysisLog.py')") == NULL)
            {
//                return -1;
            }
//        PyObject * pModule = NULL;//声明变量
//        PyObject * pFunc = NULL;// 声明变量
//        pModule =PyImport_ImportModule("analysisLog.py");//这里是要调用的文件名
//        pFunc= PyObject_GetAttrString(pModule, "hello");//这里是要调用的函数名
//        PyEval_CallObject(pFunc, NULL);//调用函数
        Py_Finalize();//调用Py_Finalize，这个根Py_Initialize相对应的。
//        return 0;
}

bool cplustest::run_cmd(std::string &cmd) {
    pid_t status;
    status = ::system(cmd.c_str());
    if(status == -1) {
        return false;
    } else {
        if(WIFEXITED(status)){
            if(0 == WEXITSTATUS(status)){
                return true;
            }else{
                printf("run failed %d \n",WEXITSTATUS(status));
                return false;
            }
        }else{
            printf("exit code %d \n",WEXITSTATUS(status));
            return false;
        }
    }
}

void cplustest::my_resolver_test() {
    test_ptr_ = std::make_shared<my_resolver>();
    test_ptr_->test();
}
