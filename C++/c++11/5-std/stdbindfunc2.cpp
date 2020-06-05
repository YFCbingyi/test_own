/*************************************************************************
	> File Name: stdbindfunc2.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月04日 星期四 16时09分21秒
 ************************************************************************/

#include<iostream>

#include<algorithm>
using namespace std;

/*
 * class A 模拟equal_to的实现
 * 
template <class T> struct equal_to {
  bool operator() (const T& x, const T& y) const {return x==y;}
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};
* */
class A{
public:
    bool operator()(const int& a,const int& b) const{
        return b > a ? true : false;
    }
    typedef int first_argument_type;
    typedef int second_argument_type;
    typedef bool result_type;
};

bool great(int a,int b) {
    return b > a ? true : false;
}

int main() {

    cout << "-----------bind1st  bind2nd-----------------" << endl;
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    int cx = count_if(a,a+sizeof(a)/sizeof(int),bind1st(A(),6));
    cout << cx << endl;
    int cxx = count_if(a,a+sizeof(a)/sizeof(int),bind2nd(A(),6));
    cout << cxx << endl;


    return 0;

}
