/*************************************************************************
	> File Name: Assert.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月21日 星期四 10时29分20秒
 ************************************************************************/

#include<stdio.h>
#include<assert.h>

int chu(int a,int b) {
    assert(b != 0);
    return a/b;
}

int main() {
    chu(2,0);
}
