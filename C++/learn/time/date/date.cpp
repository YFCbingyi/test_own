/*************************************************************************
	> File Name: date.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月28日 星期日 14时23分51秒
 ************************************************************************/

#include <cstdio>
#include <ctime>

int main() {

    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = ltm->tm_year + 1900;
    int day = ltm->tm_mday;
    int month = ltm->tm_mon+1;

    printf("GetNumber::getVirtualBusinessResult --> print time %d %d %d",year,month,day);
    return 0;
}
