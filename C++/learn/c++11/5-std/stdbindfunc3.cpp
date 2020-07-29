/*************************************************************************
	> File Name: stdbindfunc3.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月05日 星期五 09时55分58秒
 ************************************************************************/

#include<iostream>
#include<functional>
#include<algorithm>
#include<vector>
#include<sstream>

using namespace std;

double my_divide(double x,double y) {return x/y;}

struct Foo{
    void print_sum(int n1,int n2) {
        cout << n1-n2 << endl;
    }
    int data = 10;
};

ostream & print(ostream &os,const string &str,char c) {
    os << str << c;
    return os;
}

int main() {
   
    cout << "std::bind 绑定普通函数" << endl;
    {
        auto fn_half = std::bind(my_divide,100,std::placeholders::_1);
        cout << fn_half(2) << endl;
    }
    cout << "std::bind 绑定一个成员函数" << endl;
    {
        Foo foo;
        auto f = std::bind(&Foo::print_sum,&foo,95,std::placeholders::_1);
        /*                 bind绑定类成员函数时，第一个参数表示对象的成员函数的指针，第二个参数表示对象的地址。
    必须显示的指定&Foo::print_sum，因为编译器不会将对象的成员函数隐式转换成函数指针，所以必须在Foo::print_sum前添加&；
    使用对象成员函数的指针时，必须要知道该指针属于哪个对象，因此第二个参数为对象的地址 &foo；
* 
        * */
        f(5);
    }
    cout << "std::bind 绑定一个引用参数" << endl;
    {
        vector<string> words{"hello","world","this","is","mmm"};
        ostringstream os;
        char c = ' ';
        for_each(words.begin(),words.end(),[&os,c](const string &s){
            os << s << c;
        });
        cout << "------1------" << endl;
        cout << os.str() << endl;
        
        cout << "------2------" << endl;
        ostringstream os1;
        //ostream 不能拷贝，若希望传递bind一个对象
        //而不拷贝它，就必须使用标准库提供的ref函数
        for_each(words.begin(),words.end(),bind(print,ref(os1),std::placeholders::_1,c));
        cout << os1.str() << endl;
    }
    
    return 0;
}
