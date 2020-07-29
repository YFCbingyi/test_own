/*************************************************************************
	> File Name: bmp2bin.c
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月17日 星期三 18时03分32秒
 ************************************************************************/

#include<stdio.h>

/*
 * =====================================================================================
 *
 *       Filename:  bmp2bin.c
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
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>

#include "bmp.h"

#define BIN_HEADER_SIZE (0x400)		// 文件头长度
#define BMP_BIN_NAME "bmp_resource.bin"		// 输出文件名
#define BMP_RESOURCE_NAME "BMP_RESOURCE.h" // 输出头文件名
#define BMP_RESOURCE_ID_NAME "BMP_RESOURCE_ID.h" // 输出头文件名

// 输出头文件保存数据格式
typedef struct _BMP_FORMAT_T {
	uint32_t offset; // bmp 在bmp.bin的偏移量
	uint32_t width;  // bmp 宽度
	uint32_t height; // bmp 高度
	uint32_t size;   // bmp 数据大小
}BMP_FORMAT_T;


static BMP_FORMAT_T bmp;
static int readlen = 0;
static uint32_t bmp_offset = 0;
static BitMapFileHeader FileHead;
static BitMapInfoHeader InfoHead;
static Pixel rgb;
static unsigned char pix[4] = {0};

static FILE *bmpfp = NULL;
static FILE *binfp = NULL;
static FILE *res_headfp = NULL;
static FILE *id_headfp = NULL;

static DIR *dirp;
static struct dirent *dirtp;


void Usage(void)
{
	printf("bmp2hex bmppath xxx.bin\n");
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

uint16_t rgb888_to_rgb565(uint8_t R, uint8_t G, uint8_t B)
{
	uint16_t color = (uint16_t)(R>>3)<<11 | (uint16_t)(G>>2)<< 5 | (uint16_t)(B>>3);
	return  (uint16_t)((color & 0xff00) >> 8) | ((color & 0xff) << 8);
}

int strtoupper(char *str)
{
	int i;
	int len = strlen(str);
	
	for (i=0; i<len; i++)
	{
		str[i] = toupper(str[i]);
	}

	return i;
}


int analy_bmp(char *bmpfile)
{
	int ret = -1;
	int nums = 8;  // 生成的头文件数组每行显示行数;
	int line_size; // 一行图像数据size;

	char buffer[1024] = {0};
	//printf("0x%x  0x%x 0x%x 0x%x\n", bmp[0].offset, bmp[0].width, bmp[0].height, bmp[0].size );
	
	bmpfp = fopen(bmpfile, "rb");
	if (bmpfp == NULL) {
		printf("open bmp file:%s error.\n", bmpfile);
		ret = -1;
		goto exit0;
	}


	printf("sizeof FileHead :%d\n", (int)sizeof(BitMapFileHeader));
	printf("sizeof InfoHead :%d\n", (int)sizeof(BitMapInfoHeader));

	fseek(bmpfp, 0L, SEEK_SET);
	readlen = fread(&FileHead, sizeof(BitMapFileHeader), 1, bmpfp);
	if (readlen < 0) {
		printf("read bitmapfileheader error\n");
		fclose(bmpfp);
		ret = -1;
		goto exit1;
	}
	
	fseek(bmpfp, sizeof(BitMapFileHeader), SEEK_SET);
	readlen = fread(&InfoHead, sizeof(BitMapInfoHeader), 1, bmpfp);
	if (readlen < 0) {
		printf("read bitmapinfoheader error.\n");
		fclose(bmpfp);
		ret = -1;
		goto exit2;
	}

	if (memcmp(FileHead.bfType, "BM", 2) != 0) {
		printf("It's not a BMP file.\n");
		fclose(bmpfp);
		ret = -1;
		goto exit3;
	}


	//printf("BMP Type:%s\n", FileHead.bfType);
	show_filehead(&FileHead);
	show_infohead(&InfoHead);

	// 计算补齐量(这里用更容易理解的除法和求余，效果和位运算相同)
	int offset = (int)((InfoHead.biBitCount * (InfoHead.biWidth/8)) % 4);
	if (offset != 0) {
		offset = 4 - offset;
	}	
	printf("\n\n offset:%d\n\n", offset);

	// InfoHead.biBitCount  1,4,8 :有调色板，16,24,32无调色板;
	if (InfoHead.biBitCount > 8) {
		line_size = InfoHead.biWidth * (InfoHead.biBitCount/8);
	}

	printf("\n line_size:%d\n", line_size);

	//跳转到位图数据区
	//fseek(bmpfp, FileHead.bfOffBits + InfoHead.biImageSize - , SEEK_SET);
	
	rgb.Alpha = 0xFF;
	
	// 循环读取像素数据
	int h, w, j=0;

	for (h=0; h < InfoHead.biHeight; h++) {
		
		// 
		if (InfoHead.biHeight < 0) {
			fseek(bmpfp, (FileHead.bfOffBits + (h+1 * line_size) ), SEEK_SET);
		} else {
			fseek(bmpfp, (FileHead.bfOffBits + (InfoHead.biHeight - h -1) * line_size) , SEEK_SET);
		}

		for (w=0; w < InfoHead.biWidth; w++) {
			
			fread(pix, InfoHead.biBitCount/8, 1, bmpfp);
			if (InfoHead.biBitCount == 24) {
				rgb.Blue = pix[0];
				rgb.Green = pix[1];
				rgb.Red = pix[2];
			}
			
			uint16_t color = rgb888_to_rgb565(rgb.Red, rgb.Green, rgb.Blue);

			//printf("R:0x%02x, G:0x%02x, B:0x%02x\n", rgb.Red, rgb.Green, rgb.Blue);
			//	printf("0x%x ", color);
			
			//if ((j%nums) == 0) {
			//	fwrite((char*)"\n", sizeof(char), strlen("\n"), outfp);
			//}
			
			//memset(buffer, 0, sizeof(buffer));
			//sprintf(buffer, "0x%04x, ", color);
			fwrite(&color, sizeof(char), sizeof(uint16_t) , binfp);
			j++;
		}

		if (offset != 0) {
			fseek(bmpfp, offset, SEEK_CUR);
		}
	}
	
	fclose(bmpfp);
	return 0;

exit3:
exit2:
exit1:
exit0:
	return ret;
}



int main(int argc, char **argv)
{
	int ret = -1;
	int index = 0;
	struct stat sb;

	char bmppath[1024] = {0};
	char outpath[1024] = {0};
	char filepath[1024] = {0};
	char bmpname[64] = {0};
	char buffer[1024*4] = {0};


	// 判断命令参数
	if (argc < 3) {
		Usage();
		exit(1);
	}
	

	sprintf(bmppath, "%s", argv[1]);
	if (access(bmppath, F_OK) != 0) {
		printf("dir not exits :%s \n",bmppath);
		ret = -1;
		goto exit0;
	}
	

	// 打开目录
	if ((dirp=opendir(bmppath)) == NULL) {
		printf("open dir:%s error.\n", bmppath);
		ret = -1;
		goto exit0;
	}

	sprintf(outpath, "%s", argv[2]);
	if (access(outpath, F_OK) != 0) {
		printf("open out dir:%s error.\n", outpath);
		ret = -1;
		goto exit1;
	}

	//　打开输出.bin文件
	memset(outpath, 0, sizeof(outpath));
	sprintf(outpath, "%s/%s", argv[2], BMP_BIN_NAME );
	binfp = fopen(outpath, "wb");
	if (binfp == NULL) {
		printf("open :%s error.\n", outpath);
		ret = -1;
		goto exit1;
	}
	fseek(binfp, BIN_HEADER_SIZE, SEEK_SET);
		


	// 输出BMP_RESOURCE.h文件
	memset(outpath, 0, sizeof(outpath));
	sprintf(outpath, "%s/%s", argv[2], BMP_RESOURCE_NAME );
	res_headfp = fopen(outpath, "wb");
	if (res_headfp == NULL) {
		printf("open :%s error.\n", outpath);
		ret = -1;
		goto exit2;
	}
	
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "%s", "#ifndef BMP_RESOURCE_H\n#define BMP_RESOURCE_H\n\n");
	
	strcat(buffer, "typedef struct _BMP_FORMAT_T {\n");
	strcat(buffer, "\tuint32_t offset;\n");
	strcat(buffer, "\tuint32_t width;\n");
	strcat(buffer, "\tuint32_t height;\n");
	strcat(buffer, "\tuint32_t size;\n");
	strcat(buffer, "}BMP_FORMAT_T;\n\n");
	strcat(buffer, "BMP_FORMAT_T bmp_info [] = {\n");
	strcat(buffer, "//\toffset\t\twidth\t\theight\t\tsize\n");
	fwrite(buffer, sizeof(char), strlen(buffer), res_headfp);
	fflush(res_headfp);

	// 输出BMP_RESOURCE_ID.h文件
	memset(outpath, 0, sizeof(outpath));
	sprintf(outpath, "%s/%s", argv[2], BMP_RESOURCE_ID_NAME);
	id_headfp = fopen(outpath, "wb");
	if (id_headfp == NULL) {
		printf("open :%s error.\n", outpath);
		ret = -1;
		goto exit3;
	}
	memset(buffer, 0, sizeof(buffer));
	strcat(buffer, "#ifndef BMP_RESOURCES_ID_H\n");
	strcat(buffer, "#define BMP_RESOURCES_ID_H\n\n");
	fwrite(buffer, sizeof(char), strlen(buffer), id_headfp);
	fflush(id_headfp);



	bmp_offset += BIN_HEADER_SIZE;


	printf("BMP PATH:%s\n", bmppath);

	// 遍历读取目录
	while((dirtp = readdir(dirp)) != NULL)
	{
		//printf("%s\n", dirtp->d_name);
		
		//拼接完整文件目录
		memset(filepath, 0 , sizeof(filepath));
		sprintf(filepath, "%s%s", bmppath, dirtp->d_name);	
		
		// 过滤目录
		if (stat(filepath, &sb) >=  0 && S_ISDIR(sb.st_mode))
		{
			continue;
		}

		// 过滤文件类型，*.bmp
		int name_len = strlen(filepath);
		if (strcmp(filepath + (name_len -4), ".bmp") != 0)
		{
			continue;
		}	
		
		memset(bmpname, 0, sizeof(bmpname));
		snprintf(bmpname, strlen(dirtp->d_name) - strlen(".bmp")+strlen("BMP_") +1, "BMP_%s", dirtp->d_name);
		strcat(bmpname, "_ID");
		//printf("%s\n", bmpname);
		strtoupper(bmpname);
		printf("%s\n", bmpname);

		// 处理bmp文件
		//printf("%s\n", filepath);
		if (access(filepath, F_OK) != 0) {
			printf("open bmp:%s error.\n", filepath);
			continue;
		}
		
		analy_bmp(filepath);
		
		memset(buffer, 0, sizeof(buffer));
		sprintf(buffer, "    { 0x%x,\t0x%x,\t0x%x,\t0x%x }, // %s\t%d\n", bmp_offset, InfoHead.biWidth, InfoHead.biHeight, InfoHead.biImageSize, bmpname, index);
		fwrite(buffer, sizeof(char), strlen(buffer), res_headfp);
		fflush(res_headfp);
			
		memset(buffer, 0, sizeof(buffer));
		sprintf(buffer, "#define %s\t%d\n", bmpname, index);
		fwrite(buffer, sizeof(char), strlen(buffer), id_headfp);
		fflush(id_headfp);

		bmp_offset += (InfoHead.biWidth * InfoHead.biHeight) * sizeof(uint16_t);
		index++;
		printf("%s \t %d \t %d\n", filepath, index, bmp_offset);
	
	}

		// BMP_RESOURCE.h 写入结尾内容
		memset(buffer, 0, sizeof(buffer));
		strcat(buffer, "\n};\n");
		strcat(buffer, "#endif\n");
		fwrite(buffer, sizeof(char), strlen(buffer), res_headfp);
		fflush(res_headfp);
		
		// BMP_RESOURCE_ID.h 写入结尾内容
		memset(buffer, 0, sizeof(buffer));
		strcat(buffer, "\n#endif\n");
		fwrite(buffer, sizeof(char), strlen(buffer), id_headfp);
		fflush(id_headfp);

		// 程序退出关闭打开的文件描述;
		fclose(res_headfp);
		fclose(id_headfp);
		fclose(binfp);
		closedir(dirp);

		return 0;

exit3:
	fclose(res_headfp);
exit2:
	fclose(binfp);
exit1:
	closedir(dirp);
exit0:
	return ret;
}
