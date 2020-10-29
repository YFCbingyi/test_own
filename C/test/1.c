/*************************************************************************
	> File Name: 1.c
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月05日 星期五 15时01分32秒
 ************************************************************************/

#include<stdio.h>

#include<float.h>

int main() {

    float a = 0.000001;
    float b = 0.000001;
    printf("%f  %f\n ",a,b);
    printf("%f \n",FLT_EPSILON);
    printf("%f \n",DBL_EPSILON);
    return 0;
}
