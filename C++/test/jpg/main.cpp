/*************************************************************************
	> File Name: maim.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月17日 星期三 11时44分21秒
 ************************************************************************/

#include <iostream>
using namespace std;

#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>

/* we will be using this uninitialized pointer later to store raw, uncompressd image */
unsigned char *raw_image = NULL;

/* dimensions of the image we want to write */
int width = 385;
int height = 243;

/**
    * read_jpeg_file Reads from a jpeg file on disk specified by filename and saves into the
    * raw_image buffer in an uncompressed format.
    *
    * \returns positive integer if successful, -1 otherwise
    * \param *filename char string specifying the file name to read from
    *
    */

int read_jpeg_file(char *filename)
{
	/* these are standard libjpeg structures for reading(decompression) */
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	/* libjpeg data structure for storing one row, that is, scanline of an image */
	JSAMPROW row_pointer[1];

	FILE *infile = fopen(filename, "rb");
	unsigned long location = 0;
	int i = 0;

	if (!infile)
	{
		printf("Error opening jpeg file %s\n!", filename);
		return -1;
	}
	/* here we set up the standard libjpeg error handler */
	cinfo.err = jpeg_std_error(&jerr);
	/* setup decompression process and source, then read JPEG header */
	jpeg_create_decompress(&cinfo);
	/* this makes the library read from infile */
	jpeg_stdio_src(&cinfo, infile);
	/* reading the image header which contains image information */
	jpeg_read_header(&cinfo, TRUE);
	printf("orig width==%d,height=%d component=%d\n", cinfo.image_width, cinfo.image_height,cinfo.num_components);
	/* Uncomment the following to output image information, if needed. */
	/*--
    printf( "JPEG File Information: \n" );
    printf( "Image width and height: %d pixels and %d pixels.\n", cinfo.image_width, cinfo.image_height );
    printf( "Color components per pixel: %d.\n", cinfo.num_components );
    printf( "Color space: %d.\n", cinfo.jpeg_color_space );
    --*/
	/* Start decompression jpeg here */
	
	jpeg_start_decompress(&cinfo);

	/* allocate memory to hold the uncompressed image */
	
	raw_image = (unsigned char *)malloc(cinfo.output_width * cinfo.output_height * cinfo.num_components);
	/* now actually read the jpeg into the raw buffer */
	
	row_pointer[0] = (unsigned char *)malloc(cinfo.output_width * cinfo.num_components);
	/* read one scan line at a time */
	
	while (cinfo.output_scanline < cinfo.image_height)
	{
		jpeg_read_scanlines(&cinfo, row_pointer, 1);
		for (i = 0; i < cinfo.image_width * cinfo.num_components; i+=3) {
            raw_image[location++] = row_pointer[0][i] > 0x0 ? 1 : 0;
			printf("%x ",raw_image[location-1]);	
		}
	}
    int sizell = location%3 == 0 ? location/3 : location/3+1;
    unsigned char res[sizell];
    int residx = 0;
    for(int i = 0; i < location; i+=8) {
        printf("0b%d %d %d %d %d %d %d %d\n",raw_image[i],raw_image[i+1],raw_image[i+2],raw_image[i+3],raw_image[i+4],raw_image[i+5],raw_image[i+6],raw_image[i+7]);
        res[residx++] = raw_image[i] << 7 + raw_image[i+1] << 6 + raw_image[i+2] << 5 + raw_image[i+3] << 4 + raw_image[i+4] << 3 + raw_image[i+5] << 2 + raw_image[i+6] << 1 + raw_image[i+7];
    }
    printf("---------------\n");
    for(int i = 0; i < sizeof(res) ; i++) {
        printf("%x\t",res[i]);
    }

	printf("location %ud\n",location);
	/* wrap up decompression, destroy objects, free pointers and close open files */
	jpeg_finish_decompress(&cinfo);
	// printf("%x ",cinfo.);
	
	jpeg_destroy_decompress(&cinfo);
	
	free(row_pointer[0]);
	
	fclose(infile);
	/* yup, we */
	
	return 1;
}

/**
    * write_jpeg_file Writes the raw image data stored in the raw_image buffer
    * to a jpeg image with default compression and smoothing options in the file
    * specified by *filename.
    *
    * \returns positive integer if successful, -1 otherwise
    * \param *filename char string specifying the file name to save to
    *
    */
int write_jpeg_file(char *filename)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	/* this is a pointer to one row of image data */
	JSAMPROW row_pointer[1];
	FILE *outfile = fopen(filename, "wb");

	if (!outfile)
	{
		printf("Error opening output jpeg file %s\n!", filename);
		return -1;
	}
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);

	/* Setting the parameters of the output file here */
	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;
	/* default compression parameters, we shouldn't be worried about these */

	jpeg_set_defaults(&cinfo);
	cinfo.num_components = 3;
	//cinfo.data_precision = 4;
	cinfo.dct_method = JDCT_FLOAT;
	jpeg_set_quality(&cinfo, 15, TRUE);
	/* Now do the compression .. */
	jpeg_start_compress(&cinfo, TRUE);
	/* like reading a file, this time write one row at a time */
	while (cinfo.next_scanline < cinfo.image_height)
	{
		row_pointer[0] = &raw_image[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	fclose(outfile);

	return 1;
}

int main()
{
	char *infilename = "code.jpg", *outfilename = "test_out.jpg";

	if (read_jpeg_file(infilename) > 0)
	{
		// if (write_jpeg_file(outfilename) < 0)
		// 	return -1;
	}
	else
		return -1;
	return 0;
}
