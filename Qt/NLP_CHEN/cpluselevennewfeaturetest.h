#ifndef CPLUSELEVENNEWFEATURETEST_H
#define CPLUSELEVENNEWFEATURETEST_H
#include "testbase.h"
#include "comdata.h"
#include "comm.h"
#include "timer.h"
class CPlusElevenNewFeatureTest : public TestBase
{
public:
    CPlusElevenNewFeatureTest();
    void test();
    
private:
    void auto_decltype();
    
    ///////////
    void auto_decltype_return_type();
    int returnValue(int a, int b) {return a+b;}
    float returnValue(int a,float b) {return a+b;}
    template<typename B,typename C>
    auto add(B b,C c) -> decltype(returnValue(b,c))
    {
        return returnValue(b,c);
    }
    /////////// using 代替 typedef
    template<typename T>
    using str_vector_t = std::vector<T>;
    void usingTest();
    //////////  函数模板
   
    ///////// 对象初始化
    /// 如果我们实在不想编写拷贝构造函数和赋值函数，又不允许别人使用编译器生成的缺省函数，怎么办？
    /// 偷懒的办法是：只需将拷贝构造函数和赋值函数声明为私有函数，不用编写代码。
    /// 
    class Foo{
      public:
        Foo(int){}
    private:
        Foo(const Foo &) {} //私有的拷贝构造函数
    };
    void initTest();
    //////// for 
    void forTest();
    ////////lambda 表达式
    void lambdaTest();
    /////// 超时计算
    void condition_variableTest();
    ///////Timer类测试
    void timeoutTest();
    std::shared_ptr<OmClock> time_;
    ///////std::map 测试
    void mapTest();
};

#endif // CPLUSELEVENNEWFEATURETEST_H