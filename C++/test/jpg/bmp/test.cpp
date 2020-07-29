/*************************************************************************
	> File Name: test.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月17日 星期三 17时39分22秒
 ************************************************************************/

#include <iostream>
extern "C"
{
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
}
using namespace std;
/* BmpFormat.h * 存放上述几个结构体 */ // 文件头结构体
typedef struct tagBITMAPFILEHEADER
{
	unsigned short bfType;		// 19778，必须是BM字符串，对应的十六进制为0x4d42,十进制为19778，否则不是bmp格式文件
	unsigned int bfSize;		// 文件大小
	unsigned short bfReserved1; // 保留，必须设置为0
	unsigned short bfReserved2; // 保留，必须设置为0
	unsigned int bfOffBits;		// 从文件头到像素数据的偏移
} BITMAPFILEHEADER;

//图像信息头结构体
typedef struct tagBITMAPINFOHEADER
{
	unsigned int biSize;		 // 此结构体的大小
	int biWidth;				 // 图像的宽
	int biHeight;				 // 图像的高
	unsigned short biPlanes;	 // 表示bmp图片的平面属，显然显示器只有一个平面，所以恒等于1
	unsigned short biBitCount;	 // 一像素所占的位数，一般为24
	unsigned int biCompression;	 // 说明图象数据压缩的类型，0为不压缩。
	unsigned int biSizeImage;	 // 像素数据所占大小, 这个值应该等于上面文件头结构中bfSize-bfOffBits
	int biXPelsPerMeter;		 // 说明水平分辨率，用象素/米表示。一般为0
	int biYPelsPerMeter;		 // 说明垂直分辨率，用象素/米表示。一般为0
	unsigned int biClrUsed;		 // 说明位图实际使用的彩色表中的颜色索引数（设为0的话，则说明使用所有调色板项）。
	unsigned int biClrImportant; // 说明对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。
} BITMAPINFOHEADER;

//24位图像素信息结构体
typedef struct _PixelInfo
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
} PixelInfo;

int main()
{
	FILE *fp;
	fp = fopen("code.bmp", "rb"); //读取同目录下的image.bmp文件。
	if (fp == NULL)
	{
		printf("打开'image.bmp'失败！\n");
		return -1;
	}
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;

	//从文件里读取信息
	fread(&fileHeader, sizeof(fileHeader), 1, fp);
	fread(&infoHeader, sizeof(infoHeader), 1, fp);

	//解析头信息
	if (fileHeader.bfType != 19778)
	{
		printf("'image.bmp'不是一个bmp格式的文件。\n");
		return -1;
	}

	//输出文件信息
	printf("大小：%dkb\n", fileHeader.bfSize);
	printf("尺寸：宽%d 高%d\n", infoHeader.biWidth, infoHeader.biHeight);
	printf("位数：%d\n", infoHeader.biBitCount);
	printf("偏移量：%d\n", fileHeader.bfOffBits);

	if (infoHeader.biBitCount != 24 || fileHeader.bfOffBits != 54)
	{
		printf("\n暂时只支持24位图片。\n");
		return -1;
	}

	//计算补齐量(这里用更容易理解的除法和求余，效果和位运算相同)
	int offset = (infoHeader.biBitCount * infoHeader.biWidth / 8) % 4;
	if (offset != 0)
	{
		offset = 4 - offset;
	}

	//动态创建一块内存以存储像素信息
	int size = infoHeader.biHeight * (infoHeader.biWidth + offset);
	PixelInfo *pixel = (PixelInfo *)malloc(size);

	//循环读取
	for (int i = 0; i < infoHeader.biHeight; i++)
	{
		for (int j = 0; j < infoHeader.biWidth; j++)
		{
			fread(pixel, sizeof(PixelInfo), 1, fp);
		}
		if (offset != 0)
		{
			for (int j = 0; j < offset; j++)
			{
				fread(pixel, sizeof(unsigned char), 1, fp);
			}
		}
	}

	//可以在这里对像素进行处理//比如输出左下角的像素信息
	printf("\n左下角的像素的RGB为：%d\t%d\t%d\n", pixel[0].r, pixel[0].g, pixel[0].b);

	//释放内存
	free(pixel);

	return 0;
}