/*************************************************************************
	> File Name: base64.h
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月16日 星期二 12时11分40秒
 ************************************************************************/

#ifndef _BASE64_H
#define _BASE64_H

#include <stdio.h>

#if __cplusplus
extern "C"{
#endif
    
    int base64_encode(const char *indata, int inlen, char *outdata, int *outlen);
    int base64_decode(const char *indata, int inlen, char *outdata, int *outlen);
            
#if __cplusplus
}
#endif
#endif
