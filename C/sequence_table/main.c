/*************************************************************************
	> File Name: main.c
	> Author:YFC_chen 
	> Mail: lighty_chen@163.com
	> Created Time: 2019年12月09日 星期一 17时42分41秒
 ************************************************************************/

#ifndef _FUNC_H
#define _FUNC_H

#include<stdlib.h>
#include<stdio.h>

#define Size 5


typedef struct Table{
    int * head; //声明一个动态数组
    int length;
    int size;
}table;

table initTable() {
    table t;
    t.head=(int*)malloc(Size*sizeof(int)); 
    if(!t.head) {
        printf("初始化失败");
        exit(0);
    }
    t.length = 0;
    t.size = Size;
    return t;
}

void display(table t) {
    for(int i = 0 ; i < t.size; i++) {
        printf("%d\t",t.head[i]);
    }
    printf("\n");
}

int main(){
    table t = initTable();
    for(int i=0;i<Size;i++) {
        t.head[i] = i;
        t.length++;
    }
    printf("顺序表中存储的元素为 : \n");
    display(t);
    return 0;
}
#endif
