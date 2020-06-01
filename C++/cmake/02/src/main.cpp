/*************************************************************************
	> File Name: main.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年05月29日 星期五 10时19分11秒
 ************************************************************************/

#include<iostream>
using namespace std;

#define STRINGIZE(x) #x
#define STRINGIZE_VALUE_OF(x) STRINGIZE(x)

int main() {
#ifdef BUILD_FACE
    std::cout << "Build face is enable "<<std::endl;   
#endif
    std::cout << "git build with "<<STRINGIZE_VALUE_OF(GIT_COMMIT_HASH) << std::endl;
    return 0;
}
