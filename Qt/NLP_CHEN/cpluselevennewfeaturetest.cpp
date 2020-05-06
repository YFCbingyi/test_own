#include "cpluselevennewfeaturetest.h"
#include "debug_log.h"
#include <stdio.h>
#include <unistd.h>
extern int& func_int_r(int);
extern int&& func_int_rr(void);
extern int func_int(double);
CPlusElevenNewFeatureTest::CPlusElevenNewFeatureTest()
{
    
}

void CPlusElevenNewFeatureTest::test() {
    mapTest();
}

void CPlusElevenNewFeatureTest::auto_decltype() {
    int a = 10;
    float b = 2.5;
    decltype(cby::alltype::int_) num = a;
    LOG(INFO) << "num type is "<< typeid(num).name() << " num is " << num ;
    decltype(cby::alltype::int_) num2 = b;
    LOG(INFO) << "num2 type is "<< typeid(num2).name() << " num2 is " << num2;
    decltype(cby::alltype::float_) num3 = b;
    LOG(INFO) << "num3 type is "<< typeid(num3).name() << " num3 is " << num3;
    decltype(cby::alltype::int_ptr_) num4 = &a;
    LOG(INFO) << "num4 type is "<< typeid(num4).name() << " num4 is " << num4 <<  " *num4 " << &num;

    decltype(func_int(2.5)) func1 = a;
    LOG(INFO) << "func1 type is "<< typeid(func1).name();
    decltype(func_int_r(2)) func2 = a;
    LOG(INFO) << "func2 type is "<< typeid(func2).name();
    
   const int cia = 0;
   decltype(cia) cia2 = 3;
   auto cia3 = cia;
   cia3 = 5;
//   cia2 = 5 error
   LOG(INFO) << "cia type "<< typeid(cia).name() << " cia2 type "<<typeid(cia2).name();
   char str[] = "str";
   char str1[] = "good";
   const char* ccp_ptr = "str";
   decltype(ccp_ptr) ccp_ptr2 = "look"; 
//   *ccp_ptr2 = "good"; error
   auto ccp_ptr3 = ccp_ptr;
//   ccp_ptr3 = str;
   LOG(INFO) << "ccp_ptr2 type "<< typeid(ccp_ptr2).name() << " ccp_ptr3 type "<<typeid(ccp_ptr3).name();
   char* ccp_ptr4 = str;
   ccp_ptr4 = str1;
   LOG(INFO) << "ccp_ptr4 type" << typeid(ccp_ptr4).name();
   /*auto 和 decltype 对 cv 限制符的处理是不一样的。decltype 会保留 cv 限定符，而 auto 有可能会去掉 cv 限定符。
   auto 关键字对 cv 限定符的推导规则：   
   如果表达式的类型不是指针或者引用，auto 会把 cv 限定符直接抛弃，推导成 non-const 或者 non-volatile 类型。
   如果表达式的类型是指针或者引用，auto 将保留 cv 限定符。
   */   
}

void CPlusElevenNewFeatureTest::auto_decltype_return_type() {
    int a = 5; float b = 2.5;
    auto c = add<decltype(a+b)>(a,b);
    
    LOG(INFO) << " type " << typeid(c).name() << " c " << c;
}

void CPlusElevenNewFeatureTest::usingTest() {
    str_vector_t<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);  
    for(auto val : vec1) {
       LOG(INFO) << val;
    }
    
    str_vector_t<std::string> vec2;
    vec2.push_back(std::string("one"));
    vec2.push_back(std::string("two"));
    for(auto val : vec2)
        LOG(INFO) << val ;
}

void CPlusElevenNewFeatureTest::initTest() {
    Foo a1(123);
//        Foo a2 = 123;
    Foo a3 = {123};
    Foo a4{123};
    
    int a5 = {3};
    int a6{3};
    
    int i_arr[3] {1,2,3};
}

void CPlusElevenNewFeatureTest::forTest() {
    str_vector_t<std::string> vec;
    vec.push_back(std::string("祖冲之"));
    vec.push_back(std::string("王羲之"));
    for(auto n : vec)
        LOG(INFO) << n;
    for(auto &n : vec) {
        if(n == "祖冲之")
            n = "刁四缸";
    }
    for(auto n : vec)
        LOG(INFO) << n;
    
    std::map<std::string,int> mm = {
        {"one",1},{"two",2},{"three",3}
    };
    for(auto &n : mm) {
        LOG(INFO) << n.first << " " << n.second;
    }
    for(auto n = mm.begin(); n != mm.end(); n++) {
        LOG(INFO) << n->first <<" "<< n->second;
    }
    
    std::set<int> ss = {1,2,3};
    for(auto &n : ss) {
        LOG(INFO) << n;
    }
}

void CPlusElevenNewFeatureTest::lambdaTest() {
    auto f = [](int a) -> int{return a + 1;};
    LOG(INFO) << f(1) ;
    int a = 0;
//    auto f1 = []{return a;};
//    LOG(INFO) << f;
    auto f2 = [=]{return a;};
    LOG(INFO) << f;
    auto f3 = [&]{return a++;};
    LOG(INFO) << f;
    auto f4 = [a]{return a;};
    LOG(INFO) << f;
    auto f5 = [a](int i) ->int{return a+i;};
    LOG(INFO) << f(2);
}

void CPlusElevenNewFeatureTest::condition_variableTest() {
    std::mutex cvm;
    std::condition_variable cv;
    while(true) {
        std::unique_lock<std::mutex> lk(cvm);
        if(cv.wait_for(lk,std::chrono::seconds(3)) == std::cv_status::no_timeout) {
            LOG(INFO) << "timeout" ;
//            break;
        } else {
            LOG(INFO) << "no timeout";
        }       
    }
}

void CPlusElevenNewFeatureTest::timeoutTest() {
    time_ = std::make_shared<OmClock>(1500);
    time_->restart();
    int i = 5;
    while(1) {
        i--;
        sleep(1);
        if(i > 0) {
           std::cout << time_->duration() << std::endl;
        }
    }
}

void CPlusElevenNewFeatureTest::mapTest() {
    try{
        std::map<std::string,std::vector<std::string>> map;
        std::vector<std::string> a;
        std::string aa = "first";
        auto aaa = std::make_pair(aa,a);
        int size = map.begin()->second.size();
//        std::string pos = map.begin()->first;
        std::cout << size << std::endl;           
    }catch(std::exception &e) {
        std::cout << "excpteion "<<e.what() << std::endl;
    }
//    std::vector<std::string> a;
//    std::string aa = "first";
//    auto aaa = std::make_pair(aa,a);
//    map.insert(aaa);
//    for(auto &all : map)
//    {
//        if(all.first == "first") {
//            all.second.push_back("good");
//            all.second.push_back("god");
//        }
//    }
    
//    for(auto &all : map) {
//        std::cout << all.first << std::endl;
//        for(auto &t : all.second)
//            std::cout << t;
//        std::cout << std::endl;
//    }
//    std::vector<std::string> b;
//    b.push_back("gool");
//    b.push_back("bbbbb");
//    b.push_back("bbbbb");
//    std::string bb = "second";
//    auto bbb = std::make_pair(bb,b);
//    map.insert(bbb);
//    std::vector<std::string> c;
//    c.push_back("gool");
//    c.push_back("bbbbb");
//    c.push_back("bbbbb");
//    std::string cc = "third";
//    auto ccc = std::make_pair(cc,c);
//    map.insert(ccc);
//    int size = map.begin()->second.size();
//    std::string pos = map.begin()->first;
//    for(auto &all : map) {
//        if(size > all.second.size()) {
//            size = all.second.size();
//            pos = all.first;
//        }
//    }
    
//    auto xx = map.at(pos);
//    for(auto x : xx) {
//        std::cout << x << std::endl;
//    }
//    std::cout << std::endl;
//    std::cout << " size " << size << " "<< pos << std::endl;
}