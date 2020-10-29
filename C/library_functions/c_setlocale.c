/*************************************************************************
	> File Name: c_setlocale.c
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年05月29日 星期五 09时59分20秒
 ************************************************************************/

#include<stdio.h>
#include<locale.h>

int main() {

    setlocale(LC_CTYPE,"zh_CN.utf8");
    
    char str[] = "我爱我家";
    
    printf("%d\n",strlen(str));

    return 0;
}
