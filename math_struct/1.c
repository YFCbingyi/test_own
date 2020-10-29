/*************************************************************************
	> File Name: 1.c
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月02日 星期二 10时05分00秒
    有一种动物，它出生2天后就开始以每天1只的速度繁衍后代。到第n天，共有
 ************************************************************************/

#include<stdio.h>

int F(int day) {
    if(day <= 0) {
        return 0;
    } else if(day == 1) {
        return 1;
    } else {
        return F(day-1)+F(day-2);
    }
}

int main() {
    for(int i = 0; i< 10 ;i ++) {
        printf("%d\n",F(i));
    }
}
