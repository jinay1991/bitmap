/*
* bitmap.h
*
*  Created on: 25-Aug-2014
*      Author: jinay.patel
*/

#ifndef BITMAP_H_
#define BITMAP_H_

/*************************************************************************
* Include Header files Definition
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*************************************************************************
 * Default MACRO Values. These can be override in application 
 *************************************************************************/
#define IMAGE_HEIGHT 256
#define IMAGE_WIDTH	 256
#define COLOR_PLANE	 3

/*************************************************************************
 * Structure Definition
 *************************************************************************/
/*! To allow structure to allocate memory with individual attribute size
	and to avoid structure padding. */
#pragma pack(push, 1)

/* Bitmap File Header. This gives main header to BMP file */
typedef struct BMPFileHeader
{
	/*! BMP Header Parameters */
	char			signature[2];
	unsigned int 	filesize;
	unsigned int 	reserved;
	unsigned int 	fileoffset_to_pixeldata;
	
	/*! This will allow structure to allocate individual sizes to each attribute of  this Struct */
	#pragma pack(pop) 
}BMPFileHeader;

/* Bitmap Information Header. This gives additional information to put in BMP Header */
typedef struct BMPInfoHeader
{
	/*! DIB Header Parameters */
	unsigned int 	dibheadersize;
	unsigned int 	width;
	unsigned int 	height;
	unsigned short 	color_planes;
	unsigned short 	bitsperpixel;
	unsigned int 	compression;
	unsigned int 	imagesize;
	unsigned int 	Ypixelpermeter;
	unsigned int 	Xpixelpermeter;
	unsigned int 	nColorsPallette;
	unsigned int 	imp_colors;
}BMPInfoHeader;

/* Main BitMap Header Structure. This is divided further as FileHeader and InformationHeader */
typedef struct BMP_Header
{
	BMPFileHeader*	fileheader;
	BMPInfoHeader*	infoheader;
}BMP_Header;

/* BMP Image Structure */
typedef struct BMP_Image
{
	BMP_Header*		ImageHeader;
	unsigned char* 	ImageData;
}BMP_Image;

/*************************************************************************
 * Function Declarations
 *************************************************************************/

/* Creates BMP Header and creates file of format BMP with NO IMAGE data i.e. 0 will be written for all pixels */
BMP_Image*	CreateBMPImage(unsigned char* filename, int width, int height, int colorplane);
/* Release Image Pointer which had been created for Writing/Reading Image */
void ReleaseBMPImage(unsigned char* pMemPool);
/* Gives Total Image Data Size based on Padding used */
int	GetSizeImageData(int width, int height, int colorplane);

#endif /* BITMAP_H_ */