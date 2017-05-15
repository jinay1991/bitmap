/*
* bitmap.c
*
*  Created on: 25-Aug-2014
*      Author: jinay.patel
* 
*/

/*! This file contains all the function definition for generating Bitmap Image */

#include "../include/bitmap.h"

int width;
int height;
int colorplane;

/*! Gives Total Image Data Size based on Padding used */
int GetSizeImageData(int img_width, int img_height, int img_colorplane)
{
	int		padding;
	int		imageDataSize;
	float	x;
	int		ceilingValue;

	/* Calculate Padding Bytes and total Image Pixel Data Size*/
	x = (float) img_width / 4;
	ceilingValue = x > (int)x ? (int)(x + 1) : (int)x;
	padding = (img_width % 4) ? (ceilingValue * 4) - img_width : 0;
	
	imageDataSize = img_width * img_height * img_colorplane + img_height * padding;

	return imageDataSize;
}

/*! Creates BMP Header and creates file of format BMP with NO IMAGE data i.e. 0 will be written for all pixels */
BMP_Image* CreateBMPImage(unsigned char* filename,int img_width, int img_height, int img_colorplane)
{
	BMP_Image*	img;
	int			iTotalMemSize;
	char*		pMemPool;
	FILE*		fBitmap;
	int			imageDataSize;
	
	width = img_width;
	height = img_height;
	colorplane = img_colorplane;

	imageDataSize = GetSizeImageData(width, height, colorplane);

	/*! Creating Memory Pool for Image and allocating Memories to structure */
	iTotalMemSize = sizeof(BMP_Image) + sizeof(BMP_Header) + sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + imageDataSize;
	pMemPool = (char *)malloc(sizeof(char) * iTotalMemSize);
	if (!pMemPool)
		return (BMP_Image*)-1;

	img = (BMP_Image*)pMemPool; //Main BMP Image Pointer 
	pMemPool += sizeof(BMP_Image);

	img->ImageHeader = (BMP_Header*)pMemPool; //BMP Header Pointer 
	pMemPool += sizeof(BMP_Header);

	img->ImageHeader->fileheader = (BMPFileHeader*)pMemPool; //BMP File Header Pointer
	pMemPool += sizeof(BMPFileHeader);

	img->ImageHeader->infoheader = (BMPInfoHeader*)pMemPool; //BMP Info Header pointer
	pMemPool += sizeof(BMPInfoHeader);

	img->ImageData = (unsigned char*)pMemPool; //BMP Image Pixel Data Pointer
	pMemPool += imageDataSize;

	/* Writing BMP Header */
	/* Byte 0     */	img->ImageHeader->fileheader->signature[0] = 'B';
	/* Byte 1     */	img->ImageHeader->fileheader->signature[1] = 'M';
	/* Byte 2-5   */	img->ImageHeader->fileheader->filesize = imageDataSize + sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
	/* Byte 6-9   */	img->ImageHeader->fileheader->reserved = 0;
	/* Byte 10-13 */	img->ImageHeader->fileheader->fileoffset_to_pixeldata = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

	/* Byte 14-17 */	img->ImageHeader->infoheader->dibheadersize = sizeof(BMPInfoHeader);
	/* Byte 18-21 */	img->ImageHeader->infoheader->width = width;
	/* Byte 22-25 */	img->ImageHeader->infoheader->height = height;
	/* Byte 26-27 */	img->ImageHeader->infoheader->color_planes = 1; 	//always 1 for all Colors
	/* Byte 28-29 */	img->ImageHeader->infoheader->bitsperpixel = 24; 	//8bits each Color
	/* Byte 30-33 */	img->ImageHeader->infoheader->compression = 0;		//No Compression
	/* Byte 34-37 */	img->ImageHeader->infoheader->imagesize = imageDataSize;
	/* Byte 38-41 */	img->ImageHeader->infoheader->Ypixelpermeter = 2835;		//72 DPI
	/* Byte 42-45 */	img->ImageHeader->infoheader->Xpixelpermeter = 2835;		//72 DPI
	/* Byte 46-49 */	img->ImageHeader->infoheader->nColorsPallette = 0;
	/* Byte 50-53 */	img->ImageHeader->infoheader->imp_colors = 0;		//All colors are important

	/* Writing Image Data */
	memset(img->ImageData, 0x00, imageDataSize);//Writing Zero Data to Created Image

	/*! Creating BMP File and writing Data to it
	*   Note that, CreateBMPImage will write only Image header to FILE, Image Data will not be written. It is left for Application to write
	*   at later stage of Application.
	*/
	fBitmap = fopen((const char*) (const char*) (const char*) (const char*) (const char*) (const char*) (const char*) (const char*) (const char*) filename, "wb");
	if (!fBitmap)
	{
		printf("Error: Can not Open to file to write header \n");
		return (BMP_Image*)-1;
	}
	fwrite(img->ImageHeader->fileheader, sizeof(char), sizeof(BMPFileHeader), fBitmap);
	fwrite(img->ImageHeader->infoheader, sizeof(char), sizeof(BMPInfoHeader), fBitmap);
	fclose(fBitmap);

	return (BMP_Image*)img;
}

/*! Release Image Pointer which had been created for Writing/Reading Image */
void ReleaseBMPImage(unsigned char* pMemPool)
{
	if (pMemPool)
		free(pMemPool);
}

/*************************************************************************
* E N D   O F  F I L E
*************************************************************************/
