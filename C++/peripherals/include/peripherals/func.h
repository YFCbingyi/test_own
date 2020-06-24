#ifndef FUNC_H
#define FUNC_H
#include <iconv.h>
#include <cstring>
#include <iostream>


#include "utils/rs_log.h"
#define RS_CONF "RS_CONF"
#define RS_ROBOT "RS_ROBOT"

enum RobotType {
    T_XIAORUI,
    T_XIAOXUE,
    T_ALICE,
    T_DEFAULT
};

int Utf8ToGbk(char *src_str, size_t src_len, char *dst_str, size_t dst_len);

int StringToChar(std::string &src,char *des,int length);

//UNICODE码转为GB2312码
int u2g(char *inbuf,size_t inlen,char *outbuf,size_t outlen);
//GB2312码转为UNICODE码
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen);

int code_convert(char *from_charset,char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen);

//保存BMP图片到工作目录path
void SaveBMP(char* dataBMP, int DataLen, std::string& path);

enum RobotType robot_type();

#endif // FUNC_H
