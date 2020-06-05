/*************************************************************************
	> File Name: stdfunc3.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月04日 星期四 11时08分15秒
 ************************************************************************/

#include<iostream>
#include<algorithm>

#define PP(x) cout<< x <<endl;

using namespace std;

int main() {
    int num = 1;
    cout << "------------算术函数对象类型------------" << endl;
    cout << "------"<< num++ << "-------"<<endl;
    {
        PP("plus");
        plus<int> a;
        int sum = a(10,20);
        PP(sum);
        plus<string> b;
        string sums = b("hello","world");
        PP(sums);
    }
    cout << "------"<< num++ << "-------"<<endl;
    {
        PP("minus");
        int sum = minus<int>()(20,10);
        PP(sum);
    }
    cout << "------"<< num++ << "-------"<<endl;
    {
        PP("multiplies");
        multiplies<int> a;
        int sum = a(2,3);
        PP(sum);
    } 
    cout << "------"<< num++ << "-------"<<endl;
    {
        PP("divides");
        float sum = divides<float>()(3,2);
        PP(sum);
    }
    cout << "------"<< num++ << "-------"<<endl;
    {
        PP("modulus");
        int sum = modulus<int>()(7,2);
        cout << modulus<int>()(7,2) << endl;
    }
    cout << "------"<< num++ << "-------"<<endl;
    {
        PP("negate");
        cout << negate<int>()(10) << endl;
    }

    cout << "--------关系函数对象类型----------" <<endl;
    num = 1;
    {
        int a = 5;
        int b = 0;
        equal_to<int> eq;
        not_equal_to<int> neq;
        greater<int> gr;
        greater_equal<int> gre;
        less<int> le;
        less_equal<int> lee;
        for(;b < 10;b++) {
            if(eq(a,b)) {
                cout << a << " == " << b << endl;
            }
            if(neq(a,b)) {
                cout << a << " != " << b << endl;
                
            }
            if(gr(a,b)) {
                cout << a << " > " << b << endl;

            }
            if(gre(a,b)) {
                cout << a << " >= " << b << endl;
                
            }
            if(le(a,b)) {
                cout << a << " < " << b << endl;

            }
            if(lee(a,b)) {
                cout << a << " <= " << b << endl;
                
            }
        }
    }
     
    cout << "-------------逻辑函数对象类型-------------"<< endl;
    {
        bool a = true;
        bool b = false;
        if(logical_and<bool>()(a,b)) {
            cout << "a && b is true"<<endl;
        } else {
            cout << "a && b is false"<<endl;
        } 
        if(logical_or<bool>()(a,b)) {
            cout << "a || b is true" << endl;
        } else {
            cout << "a || b is false" << endl;
        }
        if(logical_not<bool>()(a)) {
            cout << "!a is true" << endl;
        } else {
            cout << "!a is false" << endl;
        }
    }
    
}
