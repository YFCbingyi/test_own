/*************************************************************************
	> File Name: decode_64.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年07月01日 星期三 12时00分00秒
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

void decode_pic(std::string &name,std::string &str) {
	
	std::string pic = base64_decode(str);
	std::ofstream file;
   file.open(name.c_str(),std::ios_base::out);
//    file.write(reinterpret_cast<const char*>(pic.c_str()),len);
   file << pic;
   file.close();
}

int main(int argc,char **argv) {

	cout << "***************************" << endl;
	cout << "*****1、base64解码转图片*****" << endl;
	cout << "*****2、base64解码转str*****" << endl;
	cout << "***************************" << endl;
	cout << "你的选择：";
	int change;
	cin >> change;
	if(change == 1) {
		std::string pic;
		cout << "请输入图片的base64码:";
		cin >> pic;
		cout << endl;
		std::string name;
		cout << "请输入图片的名字:";
		cin >> name;
		cout << "******请选择图片后缀******" << endl;
		cout << "*********1、jpg ********" << endl;
		cout << "*********1、bmp ********" << endl;
		cout << "************************" << endl;
		cout << "你的选择：";
		int end;
		cin >> end;

		if(end == 1) {
			name = name + ".jpg";
			decode_pic(name,pic);
		} else if(end == 2) {
			name = name + ".bmp";
			decode_pic(name,pic);
		} else ;
	} else if(change == 2) {
		cout << "请输入string:";
		string str;
		cin >> str;
		cout << base64_decode(str) << endl;
	} else
		cout << "输入有误" << endl;
	return 0;
}
