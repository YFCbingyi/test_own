/*************************************************************************
	> File Name: operator3.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月04日 星期四 10时12分47秒
    函数对象的函数适配器
************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
#include<functional>
using namespace std;

void func() {
    cout << "func" << endl;
}

int main() {
    int a[] = {1,2,3,4,5,6};
    vector<int> vec(a,a+sizeof(a)/sizeof(int));
    for(auto t = vec.begin();t != vec.end();t++) {
        cout << *t << endl;
    }
    int l = 6;
    for_each(vec.begin(),vec.end(),[&](int d){cout << l + d << endl;});
   

    cout << "----------2----------"<<endl;

    vector<int> v{1,3,4,5,6,7,8,9,10};
    {
    auto it = count_if(v.begin(),v.end(),bind2nd(less_equal<int>(),5));
    cout << "vector v 中<= 5的数共有 " <<it << endl;    
    }
    {
    auto it = count_if(v.begin(),v.end(),not1(bind2nd(less_equal<int>(),5)));
    cout << "vector v 中不<=5的数共有 " <<it << endl;    
    }
    
    return 0;
}

