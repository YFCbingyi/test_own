/*************************************************************************
	> File Name: base64.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月16日 星期二 12时11分15秒
 ************************************************************************/

#include <iostream>
#include "jpegenc.h"
#include <jpeglib.h>
using namespace std;

/**
 *  转解码过程
 *  3 * 8 = 4 * 6; 3字节占24位, 4*6=24
 *  先将要编码的转成对应的ASCII值
 *  如编码: s 1 3
 *  对应ASCII值为: 115 49 51
 *  对应二进制为: 01110011 00110001 00110011
 *  将其6个分组分4组: 011100 110011 000100 110011
 *  而计算机是以8bit存储, 所以在每组的高位补两个0如下:
 *  00011100 00110011 00000100 00110011对应:28 51 4 51
 *  查找base64 转换表 对应 c z E z
 *  
 *  解码
 *  c z E z
 *  对应ASCII值为 99 122 69 122
 *  对应表base64_suffix_map的值为 28 51 4 51
 *  对应二进制值为 00011100 00110011 00000100 00110011
 *  依次去除每组的前两位, 再拼接成3字节
 *  即: 01110011 00110001 00110011
 *  对应的就是s 1 3
 */

#include "base64.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

// base64 转换表, 共64个
static const char base64_alphabet[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '+', '/'};

// 解码时使用
static const unsigned char base64_suffix_map[256] = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 253, 255,
    255, 253, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 253, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 62, 255, 255, 255, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 255, 255,
    255, 254, 255, 255, 255, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
    19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255, 255,
    255, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
    37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255};

static char cmove_bits(unsigned char src, unsigned lnum, unsigned rnum)
{
    src <<= lnum; // src = src << lnum;
    src >>= rnum; // src = src >> rnum;
    return src;
}

int base64_encode(const char *indata, int inlen, char *outdata, int *outlen)
{

    int ret = 0; // return value
    if (indata == NULL || inlen == 0)
    {
        return ret = -1;
    }

    int in_len = 0;  // 源字符串长度, 如果in_len不是3的倍数, 那么需要补成3的倍数
    int pad_num = 0; // 需要补齐的字符个数, 这样只有2, 1, 0(0的话不需要拼接, )
    if (inlen % 3 != 0)
    {
        pad_num = 3 - inlen % 3;
    }
    in_len = inlen + pad_num; // 拼接后的长度, 实际编码需要的长度(3的倍数)

    int out_len = in_len * 8 / 6; // 编码后的长度

    char *p = outdata; // 定义指针指向传出data的首地址

    //编码, 长度为调整后的长度, 3字节一组
    for (int i = 0; i < in_len; i += 3)
    {
        int value = *indata >> 2;        // 将indata第一个字符向右移动2bit(丢弃2bit)
        char c = base64_alphabet[value]; // 对应base64转换表的字符
        *p = c;                          // 将对应字符(编码后字符)赋值给outdata第一字节

        //处理最后一组(最后3字节)的数据
        if (i == inlen + pad_num - 3 && pad_num != 0)
        {
            if (pad_num == 1)
            {
                *(p + 1) = base64_alphabet[(int)(cmove_bits(*indata, 6, 2) + cmove_bits(*(indata + 1), 0, 4))];
                *(p + 2) = base64_alphabet[(int)cmove_bits(*(indata + 1), 4, 2)];
                *(p + 3) = '=';
            }
            else if (pad_num == 2)
            { // 编码后的数据要补两个 '='
                *(p + 1) = base64_alphabet[(int)cmove_bits(*indata, 6, 2)];
                *(p + 2) = '=';
                *(p + 3) = '=';
            }
        }
        else
        { // 处理正常的3字节的数据
            *(p + 1) = base64_alphabet[cmove_bits(*indata, 6, 2) + cmove_bits(*(indata + 1), 0, 4)];
            *(p + 2) = base64_alphabet[cmove_bits(*(indata + 1), 4, 2) + cmove_bits(*(indata + 2), 0, 6)];
            *(p + 3) = base64_alphabet[*(indata + 2) & 0x3f];
        }

        p += 4;
        indata += 3;
    }

    if (outlen != NULL)
    {
        *outlen = out_len;
    }

    return ret;
}

int base64_decode(const char *indata, int inlen, char *outdata, int *outlen)
{

    int ret = 0;
    if (indata == NULL || inlen <= 0 || outdata == NULL || outlen == NULL)
    {
        return ret = -1;
    }
    if (inlen % 4 != 0)
    { // 需要解码的数据不是4字节倍数
        return ret = -2;
    }

    int t = 0, x = 0, y = 0, i = 0;
    unsigned char c = 0;
    int g = 3;

    while (indata[x] != 0)
    {
        // 需要解码的数据对应的ASCII值对应base64_suffix_map的值
        c = base64_suffix_map[indata[x++]];
        if (c == 255)
            return -1; // 对应的值不在转码表中
        if (c == 253)
            continue; // 对应的值是换行或者回车
        if (c == 254)
        {
            c = 0;
            g--;
        }                 // 对应的值是'='
        t = (t << 6) | c; // 将其依次放入一个int型中占3字节
        if (++y == 4)
        {
            outdata[i++] = (unsigned char)((t >> 16) & 0xff);
            if (g > 1)
                outdata[i++] = (unsigned char)((t >> 8) & 0xff);
            if (g > 2)
                outdata[i++] = (unsigned char)(t & 0xff);
            y = t = 0;
        }
    }
    if (outlen != NULL)
    {
        *outlen = i;
    }
    return ret;
}

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
int main()
{
    std::string str = "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";
    
   // int size = sizeof(str);
   // char str1[10000] = {0};
   // int len = 0;
   // base64_decode(str, (int)strlen(str), str1, &len);
    
    std::string jpg = base64_decode(str);
    
    std::cout << jpg << endl;
//    std::ofstream file;
//    file.open("chen.bmp",std::ios_base::out);
//    file.write(reinterpret_cast<const char*>(str1),len);
//    file << str1;
//    file.close();
    
    int factor = 2;
    /* these are standard libjpeg structures for reading(decompression) */
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    /* libjpeg data structure for storing one row, that is, scanline of an image */
    
    unsigned long location = 0;
    int i = 0;
    /* here we set up the standard libjpeg error handler */
    cinfo.err = jpeg_std_error(&jerr);
    /* setup decompression process and source, then read JPEG header */
    jpeg_create_decompress(&cinfo);
    /* this makes the library read from infile */
    jpeg_mem_src(&cinfo, (unsigned char *)(jpg.c_str()),jpg.length());
    /* reading the image header which contains image information */
    jpeg_read_header(&cinfo, TRUE);
    printf("orig width==%d,height=%d component=%d\n", cinfo.image_width, cinfo.image_height,cinfo.num_components);
    
    jpeg_start_decompress(&cinfo);

    /* allocate memory to hold the uncompressed image */

    //raw_image = (unsigned char *)malloc((cinfo.output_width * cinfo.output_height * cinfo.num_components) + 8);
    /* now actually read the jpeg into the raw buffer */
    int w_bytes = cinfo.output_width / 8;
    if(cinfo.output_width % 8 != 0)
        w_bytes += 1;

    unsigned char raw_image[(w_bytes * cinfo.output_height * factor * factor) + 8] = {0};
    unsigned char* row_pointer = (unsigned char *)malloc(cinfo.output_width * cinfo.output_components);
   
    /* read one scan line at a time */
    raw_image[0] = 0x1D;
    raw_image[1] = 0x76;
    raw_image[2] = 0x30;
    raw_image[3] = 0x00;
    raw_image[4] = 0x10 * factor;
    raw_image[5] = 0x00;
    raw_image[6] = 0x7e * factor;
    raw_image[7] = 0x00;
    //location = 8;
   
    printf("output_width = %d\n", cinfo.output_width);
    printf("output_height = %d\n", cinfo.output_height);
    printf("output color space type: %d\n", cinfo.out_color_space);
    printf("output_components: %d\n", cinfo.output_components);
    printf("output_scanline: %d\n", cinfo.output_scanline);
    
    unsigned char *pimage = &raw_image[8];
    while (cinfo.output_scanline < cinfo.output_height)
    {
        jpeg_read_scanlines(&cinfo, &row_pointer, 1);
        unsigned char mod = 0;
        int count = 0;
        unsigned char *pcurline = pimage;
        for (int i = 0; i < cinfo.output_width * cinfo.output_components; i+=3) {
            unsigned char R = row_pointer[i];
            unsigned char G = row_pointer[i+1];
            unsigned char B = row_pointer[i+2];
            unsigned char Y = 0.30*R+0.59*G+0.11*B;
            Y = (Y>200 ? 0:1);
            //Y = (Y<10 ? 1:0);
            //Y = 1;
            //printf("%d", Y);
            
            int m = factor;
            while(m-- > 0) { 
                mod |= Y; 
                printf("%c", (Y == 1 ? '*':' '));
                count++;
                if(count == 8) {
                    *pimage++ = mod;
                    mod = 0;
                    count = 0;
                } else {
                    mod <<= 1;
                }
            }
        }
        
        if(count != 0) {
            mod <<= (8-count-1);
            *pimage++ = mod;
        }

        printf(";\n");
        //printf("pimage1: %p\n", pimage);
        {
            int m = factor-1;
            int len = pimage-pcurline;
            while(m-- > 0) {
                memcpy(pimage, pcurline, len);
                //pcurline = pimage;
                pimage += len;
            
                //printf("pimage2: %p\n", pimage);
            }
        }
        //printf("\n");
    }


}


int main11()
{

    fstream f;
    f.open("code.jpg", ios::in|ios::binary);
    if(f){
        f.seekg(0, std::ios_base::end);
        std::streampos sp = f.tellg();
        f.seekg (0, std::ios_base::beg);
        int size = sp;
        char* buffer = (char*)malloc(sizeof(char)*size);
        f.read(buffer,size);
 
        string imgBase64 = base64_encode(buffer, size);
        // cout << "img encode:" << imgBase64<< endl;
        string imgdecode64 = base64_decode(imgBase64);
        for( int i = 170; i < size-2 ; i++ ) {
            printf("%x ",(unsigned char)imgdecode64[i]);
        }
    }
 
    return 0;
}
