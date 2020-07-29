
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "jpeglib.h"
#include "jpegenc.h"

void get_now_ms( unsigned long *ms)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    *ms = now.tv_sec * 1000 + now.tv_usec/1000;
}

// Creates a test image for saving. Creates a Mandelbrot Set fractal of size width x height
float *createMandelbrotImage(int width, int height, float xS, float yS, float rad, int maxIteration);

// This takes the float value 'val', converts it to red, green & blue values, then 
// sets those values into the image memory buffer location pointed to by 'ptr'
void setRGB(unsigned char *ptr, float val);

void convertBuffer(unsigned char *buf_b, float *buf_f, int w, int h, int has_alpha);

void makeGrayImg(unsigned char *buf, int w, int h, int sz) {
	unsigned char val = 0;
	// Do not check sz can be dived by w
	unsigned char *p = buf;
	for(int i=0; i< h; i+=sz) {
		memset(p, val, w*sz);
		p += w*sz;
		val = ~val;
	}
}

void test_jpeg_file()
{
    struct JPEG_Enc  *jpeg_enc;
    FILE *fp = NULL;
	int  ch = 3;
	int  has_alpha = 0;

	// Specify an output image size
	int width = 640;
	int height = 480;

	// Create a test image
	printf("Creating Image\n");
	float *buffer_f = createMandelbrotImage(width, height, -0.802, -0.177, 0.011, 110);
	if (buffer_f == NULL) {
		return;
	}
	// Then convert to bytes
	unsigned char *buffer_b = (unsigned char *) malloc((3 + (has_alpha?1:0)) * width * height * sizeof(unsigned char));
	if (buffer_b == NULL) {
		return;
	}
	convertBuffer(buffer_b, buffer_f, width, height, (3 + has_alpha));

	unsigned char *buffer_g = (unsigned char *) malloc( width * height * sizeof(unsigned char));
	if (buffer_g == NULL) {
		return;
	}
	convertBuffer(buffer_g, buffer_f, width, height,  1);

    // JPEG encoding for RGB image
    jpeg_enc = new_jpegenc(width, height, ch);
    if(jpeg_enc == NULL) {
        return;
    }
	// Encoding
	unsigned long t0, t1;
	get_now_ms(&t0);
	jpegenc_compress(jpeg_enc, buffer_b,  60, ch);
	get_now_ms(&t1);
	printf("Compress RGB image to JPEG using %ldms\n", t1-t0);

    printf("Saving JPEG\n");
	fp = fopen("test_rgb.jpg", "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file for writing\n");
		return;
	}
    fwrite(jpegenc_get_enc_buf(jpeg_enc), 1, jpegenc_get_enc_size(jpeg_enc), fp);
	//dispose_jpegenc(jpeg_enc);
    if (fp != NULL)
		fclose(fp);

    // JPEG encoding for Gray image
	// Encoding
	get_now_ms(&t0);
	jpegenc_compress(jpeg_enc, buffer_g,  60, 1);
	get_now_ms(&t1);
	printf("Compress Gray image to JPEG using %ldms\n", t1-t0);

    printf("Saving JPEG\n");
	fp = fopen("test_gray.jpg", "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file for writing\n");
		return;
	}
    fwrite(jpegenc_get_enc_buf(jpeg_enc), 1, jpegenc_get_enc_size(jpeg_enc), fp);
	//dispose_jpegenc(jpeg_enc);
    if (fp != NULL)
		fclose(fp);

	// Free up the memorty used to store the image
	free(buffer_f);
	free(buffer_b);
	free(buffer_g);
	
	
	// Added another example: 20190603
	unsigned char *grayBuf = malloc(640*480 * sizeof(char));
	makeGrayImg(grayBuf, 640, 480, 16);
	
	get_now_ms(&t0);
	jpegenc_compress(jpeg_enc, grayBuf,  60, 1);
	get_now_ms(&t1);
	printf("Compress Gray image to JPEG using %ldms\n", t1-t0);

    printf("Saving JPEG\n");
	fp = fopen("test_gray1.jpg", "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file for writing\n");
		return;
	}
    fwrite(jpegenc_get_enc_buf(jpeg_enc), 1, jpegenc_get_enc_size(jpeg_enc), fp);
	dispose_jpegenc(jpeg_enc);
    if (fp != NULL)
		fclose(fp);
	
}

void setGray(unsigned char *ptr, float val)
{
	int v = (int)(val * 767);
	if (v < 0) v = 0;
	if (v > 767) v = 767;
	int offset = v % 256;

	if (v<256) {
		ptr[0] = offset;
	}
	else if (v<512) {
		ptr[0] = 255-offset;
	}
	else {
		ptr[0] = 0;
	}
}

// ch can be '1', '3', '4'
void convertBuffer(unsigned char *buf_b, float *buf_f, int w, int h, int ch) 
{
	int x, y;
	int line_sz = w*(ch);
	int pixel_sz = (ch);
	int has_alpha = (ch == 4);
	if(ch == 1) {
		for (y=0 ; y<h ; y++) {
			//printf("%d\n", y);
			for (x=0 ; x<w ; x++) 
			{
				setGray(&(buf_b[y*line_sz + x*pixel_sz ]), buf_f[y*w + x]);
			}
		}
	}
	else {
		for (y=0 ; y<h ; y++) {
			//printf("%d\n", y);
			for (x=0 ; x<w ; x++) 
			{
				setRGB(&(buf_b[y*line_sz + x*pixel_sz ]), buf_f[y*w + x]);
				if(has_alpha)
					buf_b[y*line_sz + x*pixel_sz +3] = 255;
			}
		}
	}

}

void setRGB(unsigned char *ptr, float val)
{
	int v = (int)(val * 767);
	if (v < 0) v = 0;
	if (v > 767) v = 767;
	int offset = v % 256;

	if (v<256) {
		ptr[0] = 0; ptr[1] = 0; ptr[2] = offset;
	}
	else if (v<512) {
		ptr[0] = 0; ptr[1] = offset; ptr[2] = 255-offset;
	}
	else {
		ptr[0] = offset; ptr[1] = 255-offset; ptr[2] = 0;
	}
}

float *createMandelbrotImage(int width, int height, float xS, float yS, float rad, int maxIteration)
{
	float *buffer = (float *) malloc(width * height * sizeof(float));
	if (buffer == NULL) {
		fprintf(stderr, "Could not create image buffer\n");
		return NULL;
	}

	// Create Mandelbrot set image

	int xPos, yPos;
	float minMu = maxIteration;
	float maxMu = 0;

	for (yPos=0 ; yPos<height ; yPos++)
	{
		float yP = (yS-rad) + (2.0f*rad/height)*yPos;

		for (xPos=0 ; xPos<width ; xPos++)
		{
			float xP = (xS-rad) + (2.0f*rad/width)*xPos;

			int iteration = 0;
			float x = 0;
			float y = 0;

			while (x*x + y*y <= 4 && iteration < maxIteration)
			{
				float tmp = x*x - y*y + xP;
				y = 2*x*y + yP;
				x = tmp;
				iteration++;
			}

			if (iteration < maxIteration) {
				float modZ = sqrt(x*x + y*y);
				float mu = iteration - (log(log(modZ))) / log(2);
				if (mu > maxMu) maxMu = mu;
				if (mu < minMu) minMu = mu;
				buffer[yPos * width + xPos] = mu;
			}
			else {
				buffer[yPos * width + xPos] = 0;
			}
		}
	}

	// Scale buffer values between 0 and 1
	int count = width * height;
	while (count) {
		count --;
		buffer[count] = (buffer[count] - minMu) / (maxMu - minMu);
	}

	return buffer;
}

int main(void)
{
    test_jpeg_file();
 }
 
