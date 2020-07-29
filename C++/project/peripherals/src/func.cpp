#include "peripherals/func.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int Utf8ToGbk(char *src_str, size_t src_len, char *dst_str, size_t dst_len)
{
    iconv_t cd;
    char **pin = &src_str;
    char **pout = &dst_str;

    cd = iconv_open("gbk", "utf8");
    if (cd == 0)
        return -1;
    memset(dst_str, 0, dst_len);
    if (iconv(cd, pin, &src_len, pout, &dst_len) == -1)
        return -1;
    iconv_close(cd);
    *pout = '\0';

    return 0;
}

int StringToChar(std::string &src,char *des,int length) {
    char str[64] = {0};
    src.copy(str,src.size(),0);
    printf("str %s\n",str);
    Utf8ToGbk(str,strlen(str),des,length);
}


int u2g(char *inbuf,size_t inlen,char *outbuf,size_t outlen) {
    char UTF[] = "utf-8";
    char GBK[] = "gb2312";
    return code_convert(UTF,GBK,inbuf,inlen,outbuf,outlen);
}

int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen) {
    char UTF[] = "utf-8";
    char GBK[] = "gb2312";
    return code_convert(GBK,UTF,inbuf,inlen,outbuf,outlen);
}

int code_convert(char *from_charset,char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen) {
    iconv_t cd;
    int rc;
    char **pin = &inbuf;
    char **pout = &outbuf;

    cd = iconv_open(to_charset,from_charset);
    if (cd==0) return -1;
    memset(outbuf,0,outlen);
    if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
    iconv_close(cd);
    return 0;
}

void SaveBMP(char* dataBMP, int DataLen, std::string& path)
{
//    char fullpath[256] = {0x00};
//    char *dir = getcwd(fullpath, sizeof(fullpath));
    char *conf = getenv(RS_CONF);
    printf("bmp path : %s\n",path.c_str());
//    strcat(fullpath, path.c_str());
    std::string path_ = std::string(conf) + path;
    int fd = open(path_.c_str(), O_RDWR|O_CREAT,0777);

    if(fd != -1){
        int iresult = ftruncate(fd,0);//清理
        if(iresult < 0)
            printf("ftruncate failed\n");
        lseek(fd,0,SEEK_SET);//重新设置文件偏移量
        int iread = write(fd, dataBMP, DataLen);
        if(iread < 0) {
            printf("write failed\n");
        }
        close(fd);
    }
}

enum RobotType robot_type() {
    char *conf = getenv(RS_ROBOT);
    if(conf == nullptr)
        return T_DEFAULT;
    std::string type = std::string(conf);
    if(type.find("chenxing") != std::string::npos)
        return T_XIAORUI;
    else if(type.find("csj_xiaoxue") != std::string::npos)
        return T_XIAOXUE;
    else if(type.find("csj_alice") != std::string::npos)
        return T_ALICE;
    return T_DEFAULT;
}


std::string base64_encode(const char * bytes_to_encode, unsigned int in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
 
    while (in_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if(i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;     
            for(i = 0; (i <4) ; i++)
            {
                ret += base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }
    if(i)
    {
        for(j = i; j < 3; j++)
        {
            char_array_3[j] = '\0';
        }
 
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
 
        for(j = 0; (j < i + 1); j++)
        {
            ret += base64_chars[char_array_4[j]];
        }
 
        while((i++ < 3))
        {
            ret += '=';
        }
 
    }
    return ret;
}
 
std::string base64_decode(std::string const & encoded_string)
{
    int in_len = (int) encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
 
    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);
 
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
 
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
 
        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);
 
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);  
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];  
 
        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];  
    }  
 
    return ret;  
}