/*************************************************************************
	> File Name: bmp.h
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月17日 星期三 17时57分13秒
 ************************************************************************/
 /* =====================================================================================
 *
 *       Filename:  bmp.h
 *
 *    Description:  bitmap header
 *
 *        Version:  1.0
 *        Created:  2019年06月21日 14时54分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#ifndef _BMP_H_
#define _BMP_H_

// 文件头 14Bytes
typedef struct 
{
	unsigned char	bfType[2];	 // 2Bytes, 文件类型 "BM"
	unsigned int	bfSize;		     // 4Bytes, 文件size
	unsigned short	bfReserved1; // 2Bytes, 保留1,必须为0
	unsigned short	bfReserved2; // 2Bytes, 保留2,必须为0
	unsigned int	bfOffBits;	 // 4Bytes, 数据偏移量
}__attribute__((packed)) BitMapFileHeader; // 使编译器不优化，其大小为14字节;

// 信息头 40Bytes
typedef struct
{
	unsigned int	biSize;		// 4Bytes, BitMapInfoHeader 信息头字节数;
	int	biWidth;				   // 4Bytes, 宽度
	int	biHeight;				   // 4Bytes, 高度,正数为正向，反之为倒图
	unsigned short biPlanes;	// 2Bytes, 为目标设备说明位面数,表示bmp图片的平面属，显然显示器只有一个平面，所以恒等于1
	unsigned short biBitCount;  // 2Bytes, 像素位bits，1 4 8 16 24 32　　其中值为16,24,32无调色板信息
	unsigned int biCompression; // 4Bytes, 图像是否压缩类型BI_RGB, 0代表不压缩
	unsigned int biImageSize;   // 4Bytes, 图像大小，单位字节 像素数据所占大小, 这个值应该等于上面文件头结构中bfSize-bfOffBits
	unsigned int biXPelsPerMeter;		// 4Bytes, 水平分辨率 说明水平分辨率，用象素/米表示。一般为0
	unsigned int biYPelsPerMeter;		// 4Bytes, 垂直分辨率 说明垂直分辨率，用象素/米表示。一般为0
	unsigned int biClrUsed;				// 4Bytes, 位图实际使用的彩色表中的颜色索引数（设为0的话，则说明使用所有调色板项）。 
	unsigned int biClrImportant;		// 4Bytes, 对图像显示有重要影响的索引数
} __attribute__((packed)) BitMapInfoHeader;

// 像素数据 
// BitCount = 32 BGRA
// BitCount = 24 BGR
// BitCount = 16
typedef struct
{
	unsigned char Blue;
	unsigned char Green;
	unsigned char Red;
	unsigned char Alpha;
} __attribute__((packed)) Pixel;

#endif
