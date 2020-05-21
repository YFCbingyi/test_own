/*************************************************************************
	> File Name: errno.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月21日 星期四 10时08分08秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<errno.h>

int main() {
    errno = 0;
    FILE *fp = fopen("test.txt","r");
    if(errno != 0) {
        printf("errno value %d\n",errno);
        printf("errno info %s\n",strerror(errno));
    }
    return 0;
 }
