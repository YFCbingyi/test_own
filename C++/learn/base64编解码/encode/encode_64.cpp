/*************************************************************************
	> File Name: encode_64.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年07月01日 星期三 11时59分46秒
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
using namespace std;

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static inline bool is_base64(const char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
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

void basePic(std::string &path) {
	fstream f;
    f.open(path.c_str(), ios::in|ios::binary);
	if(f.is_open()) {
		f.seekg(0, std::ios_base::end);
        std::streampos sp = f.tellg();
        f.seekg (0, std::ios_base::beg);
        int size = sp;
        char* buffer = (char*)malloc(sizeof(char)*size);
        f.read(buffer,size);
 
        string imgBase64 = base64_encode(buffer, size);
        cout << "img encode:" << imgBase64<< endl;
	} else 
		cout << "no such file or filepath" << endl;
	f.close();
}

void baseStr(std::string &str) {
	string strBase64 = base64_encode(str.c_str(), str.length());
    cout << "str encode:" << strBase64<< endl;
}

int main(int argc,char **argv) {

	cout << "***************************" << endl;
	cout << "*****1、图片转base64编码*****" << endl;
	cout << "*****2、string转base64编码*****" << endl;
	cout << "***************************" << endl;
	cout << "你的选择：";
	int change;
	cin >> change;
	if(change == 1) {
		cout << "请输入图片路径:";
		string path;
		cin >> path;
		basePic(path);
	} else if(change == 2) {
		cout << "请输入string:";
		string str;
		cin >> str;
		baseStr(str);
	} else
		cout << "输入有误" << endl;
	return 0;
}
