/*************************************************************************
	> File Name: bmp2hex.c
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月17日 星期三 17时59分03秒
 ************************************************************************/

#include <stdio.h>

/*
 * =====================================================================================
 *
 *       Filename:  bmp2hex.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019年06月21日 15时37分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "bmp.h"

int readlen = 0;
BitMapFileHeader FileHead;
BitMapInfoHeader InfoHead;
Pixel rgb;
unsigned char pix[4] = {0};

FILE *bmpfp = NULL;
FILE *outfp = NULL;

void Usage(void)
{
	printf("bmp2hex xxx.bmp xxx.h\n");
}

void show_filehead(BitMapFileHeader *FileHead)
{
	char Type[3];
	Type[0] = FileHead->bfType[0];
	Type[1] = FileHead->bfType[1];
	Type[2] = '\0';

	printf("BMP Type \t :%s\n", Type);
	printf("BMP Size \t :%d\n", FileHead->bfSize);
	printf("BMP Reserved1 \t :%d\n", FileHead->bfReserved1);
	printf("BMP Reserved2 \t :%d\n", FileHead->bfReserved2);
	printf("BMP OffBits \t :%d\n", FileHead->bfOffBits);
}

void show_infohead(BitMapInfoHeader *InfoHead)
{
	printf("BMP FileHeader Size \t:%d\n", InfoHead->biSize);
	printf("BMP Width \t:%d\n", InfoHead->biWidth);
	printf("BMP Height \t:%d\n", InfoHead->biHeight);
	printf("BMP Planes \t:%d\n", InfoHead->biPlanes);
	printf("BMP BitCount \t:%d\n", InfoHead->biBitCount);
	printf("BMP Compression \t:%d\n", InfoHead->biCompression);
	printf("BMP ImageSize \t:%d\n", InfoHead->biImageSize);
	printf("BMP XPelsPerMeter \t:%d\n", InfoHead->biXPelsPerMeter);
	printf("BMP YPelsPerMeter \t:%d\n", InfoHead->biYPelsPerMeter);
	printf("BMP ClrUsed \t:%d\n", InfoHead->biClrUsed);
	printf("BMP ClrImportant \t:%d\n", InfoHead->biClrImportant);
}

// uint16_t rgb888_to_rgb565(uint8_t R, uint8_t G, uint8_t B)
// {
// 	uint16_t color = (uint16_t)(R>>3)<<11 | (uint16_t)(G>>2)<< 5 | (uint16_t)(B>>3);
// 	return  (uint16_t)((color & 0xff00) >> 8) | ((color & 0xff) << 8);
// }
uint16_t rgb888_to_rgb565(uint8_t R, uint8_t G, uint8_t B)
{
	if (R > 220 && G > 220 && B > 220)
	{
		return 0xff;
	}
	else if (R < 30 && G < 30 && B < 30)
	{
		return 0x0;
	}
	else
	{
		return (299 * R + 587 * G + 114 * B) / 1000;
	}
}

int main(int argc, char **argv)
{
	int nums = 8;  // 生成的头文件数组每行显示行数;
	int line_size; // 一行图像数据size;

	char buffer[8] = {0};

	if (argc < 3)
	{
		Usage();
		exit(1);
	}

	bmpfp = fopen(argv[1], "rb");
	if (bmpfp == NULL)
	{
		printf("open bmp file:%s error.\n", argv[1]);
		exit(1);
	}

	outfp = fopen(argv[2], "wb");
	if (outfp == NULL)
	{
		printf("open output file:%s error.\n", argv[2]);
		exit(1);
	}

	printf("sizeof FileHead :%d\n", (int)sizeof(BitMapFileHeader));
	printf("sizeof InfoHead :%d\n", (int)sizeof(BitMapInfoHeader));

	fseek(bmpfp, 0L, SEEK_SET);
	readlen = fread(&FileHead, sizeof(BitMapFileHeader), 1, bmpfp);
	if (readlen < 0)
	{
		printf("read bitmapfileheader error\n");
		fclose(bmpfp);
		exit(2);
	}

	fseek(bmpfp, sizeof(BitMapFileHeader), SEEK_SET);
	readlen = fread(&InfoHead, sizeof(BitMapInfoHeader), 1, bmpfp);
	if (readlen < 0)
	{
		printf("read bitmapinfoheader error.\n");
		fclose(bmpfp);
		exit(3);
	}

	if (memcmp(FileHead.bfType, "BM", 2) != 0)
	{
		printf("It's not a BMP file.\n");
		fclose(bmpfp);
		exit(3);
	}

	//printf("BMP Type:%s\n", FileHead.bfType);
	show_filehead(&FileHead);
	show_infohead(&InfoHead);

	// 计算补齐量(这里用更容易理解的除法和求余，效果和位运算相同)
	int offset = (int)((InfoHead.biBitCount * (InfoHead.biWidth / 8)) % 4);
	if (offset != 0)
	{
		offset = 4 - offset;
	}
	printf("\n\n offset:%d\n\n", offset);

	// InfoHead.biBitCount  1,4,8 :有调色板，16,24,32无调色板;
	if (InfoHead.biBitCount > 8)
	{
		line_size = InfoHead.biWidth * (InfoHead.biBitCount / 8);
	}

	printf("\n line_size:%d\n", line_size);

#if 1
	//跳转到位图数据区
	//fseek(bmpfp, FileHead.bfOffBits + InfoHead.biImageSize - , SEEK_SET);

	rgb.Alpha = 0xFF;

	// 循环读取像素数据
	int h, w, j = 0;
	uint8_t colorg[InfoHead.biHeight * InfoHead.biWidth];
	int locc = 0;
	for (h = 0; h < InfoHead.biHeight; h++)
	{

		//
		if (InfoHead.biHeight < 0)
		{
			fseek(bmpfp, (FileHead.bfOffBits + (h + 1 * line_size)), SEEK_SET);
		}
		else
		{
			fseek(bmpfp, (FileHead.bfOffBits + (InfoHead.biHeight - h - 1) * line_size), SEEK_SET);
		}

		for (w = 0; w < InfoHead.biWidth; w++)
		{

			fread(pix, InfoHead.biBitCount / 8, 1, bmpfp);
			if (InfoHead.biBitCount == 24)
			{
				rgb.Blue = pix[0];
				rgb.Green = pix[1];
				rgb.Red = pix[2];
			}

			// uint16_t color = rgb888_to_rgb565(rgb.Red, rgb.Green, rgb.Blue);
			uint8_t color = rgb888_to_rgb565(rgb.Red, rgb.Green, rgb.Blue);
			colorg[locc++] = rgb888_to_rgb565(rgb.Red, rgb.Green, rgb.Blue);
			//printf("R:0x%02x, G:0x%02x, B:0x%02x\n", rgb.Red, rgb.Green, rgb.Blue);

			//	printf("0x%x ", color);

			if ((j % nums) == 0)
			{
				fwrite((char *)"\n", sizeof(char), strlen("\n"), outfp);
			}

			memset(buffer, 0, sizeof(buffer));
			// sprintf(buffer, "0x%04x, ", color);
			sprintf(buffer, "0x%02x, ", color);
			fwrite(buffer, sizeof(char), strlen(buffer), outfp);
			j++;
		}

		if (offset != 0)
		{
			fseek(bmpfp, offset, SEEK_CUR);
		}
	}

	int sset = 8;
	uint8_t colorgg[locc / 3];
	int j = 0;
	int myweight = 126;
	int mysize = 16;
	int mymod = 16 - 126 % 16;
	int myindex = 1;
	for (int i = 0; i < locc; i++) {
		sset--;
		colorg[j] += colorg[i] << sset;
		if (sset == 0)
		{
			sset = 8;
			j++;
		}
		if(i%126 == 0) {
			sset = 8;
			j++;
		}
	}
#else
	//跳转到位图数据区
	fseek(bmpfp, FileHead.bfOffBits, SEEK_SET);

	rgb.Alpha = 0xFF;

	// 循环读取像素数据
	int h, w, j = 0;

	for (h = 0; h < InfoHead.biHeight; h++)
	{

		for (w = 0; w < InfoHead.biWidth; w++)
		{

			fread(pix, InfoHead.biBitCount / 8, 1, bmpfp);
			if (InfoHead.biBitCount == 24)
			{
				rgb.Blue = pix[0];
				rgb.Green = pix[1];
				rgb.Red = pix[2];
			}

			uint16_t color = rgb888_to_rgb565(rgb.Red, rgb.Green, rgb.Blue);

			//printf("R:0x%02x, G:0x%02x, B:0x%02x\n", rgb.Red, rgb.Green, rgb.Blue);

			//	printf("0x%x ", color);

			if ((j % nums) == 0)
			{
				fwrite((char *)"\n", sizeof(char), strlen("\n"), outfp);
			}

			memset(buffer, 0, sizeof(buffer));
			sprintf(buffer, "0x%04x, ", color);
			fwrite(buffer, sizeof(char), strlen(buffer), outfp);
			j++;
		}

		if (offset != 0)
		{
			fseek(bmpfp, offset, SEEK_CUR);
		}
	}
#endif

	fclose(bmpfp);

	return 0;
}
