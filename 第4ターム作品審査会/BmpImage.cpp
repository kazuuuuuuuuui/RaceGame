#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
#include<Windows.h>
#include"BmpImage.h"

//-------------------------------------
//bmp画像からアルファ値付きのテクスチャ作成

GLuint  BmpImage::loadImage_alpha(const char *_Filename){
	FILE *pBinMapFile;
	pBinMapFile = fopen(_Filename, "rb");

	assert(pBinMapFile != NULL);

	BITMAPFILEHEADER bmpHeader;
	fread(
		&bmpHeader,
		sizeof(BITMAPFILEHEADER),
		1,
		pBinMapFile
		);

	BITMAPINFOHEADER bmpInfoHeader;
	fread(
		&bmpInfoHeader,
		sizeof(BITMAPINFOHEADER),
		1,
		pBinMapFile
		);

	int imageSize = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * sizeof(RGB);
	RGB *pixels = (RGB*)malloc(imageSize);

	int imageSize_alpha = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * sizeof(RGBA);
	RGBA *pixels_alpha = (RGBA*)malloc(imageSize_alpha);

	fread(
		pixels,
		imageSize,
		1,
		pBinMapFile
		);
	fclose(pBinMapFile);

	//ピクセル単位でRとBを逆転させる
	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
		pixels_alpha[i].r = pixels[i].r;
		pixels_alpha[i].g = pixels[i].g;
		pixels_alpha[i].b = pixels[i].b;

		//白ならアルファ値0とする
		if (pixels_alpha[i].r == 255 && pixels_alpha[i].g == 255 && pixels_alpha[i].b == 255){
			pixels_alpha[i].a = 0;
		}
		else{
			pixels_alpha[i].a = 255;
		}
	}

	GLuint handle;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);

	//pixcel
	glTexImage2D(
		GL_TEXTURE_2D,   //GLenum target
		0,               //GLint level
		GL_RGBA,          //GLint internalformat(生成するテクスチャのフォーマット)
		bmpInfoHeader.biWidth,               //GLsizei width
		bmpInfoHeader.biHeight,               //GLsizei height
		0,               //GLint border
		GL_RGBA,          //GLenum format(ピクセルデータのフォーマット)
		GL_UNSIGNED_BYTE,//GLenum type
		pixels_alpha          //const GLvoid *pixels
		);

	glTexParameteri(
		GL_TEXTURE_2D,          // GLenum target
		GL_TEXTURE_MIN_FILTER,  // GLenum pname
		GL_NEAREST);            // GLint param

	glTexParameteri(
		GL_TEXTURE_2D,          // GLenum target
		GL_TEXTURE_MAG_FILTER,  // GLenum pname
		GL_NEAREST);

	free(pixels);
	free(pixels_alpha);

	return handle;
}

/*拡張子.bmpの画像読み込み*/
GLuint BmpImage::loadImage(const char *_fileName/*, RGB *_pixels*/){
	FILE *pBinMapFile;
	pBinMapFile = fopen(_fileName, "rb");

	assert(pBinMapFile != NULL);

	BITMAPFILEHEADER bmpHeader;
	fread(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, pBinMapFile);

	BITMAPINFOHEADER bmpInfoHeader;
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, pBinMapFile);

	int imageSize = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * sizeof(RGB);
	RGB *pixels = (RGB*)malloc(imageSize);
	pixels = (RGB*)malloc(imageSize);

	fread(pixels, imageSize, 1, pBinMapFile);

	fclose(pBinMapFile);

	//ピクセル単位でRとBを逆転させる
	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	GLuint handle;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);

	//pixcel
	glTexImage2D(
		GL_TEXTURE_2D,   //GLenum target
		0,               //GLint level
		GL_RGB,          //GLint internalformat(生成するテクスチャのフォーマット)
		bmpInfoHeader.biWidth,               //GLsizei width
		bmpInfoHeader.biHeight,               //GLsizei height
		0,               //GLint border
		GL_RGB,          //GLenum format(ピクセルデータのフォーマット)
		GL_UNSIGNED_BYTE,//GLenum type
		pixels          //const GLvoid *pixels
		);

	glTexParameteri(
		GL_TEXTURE_2D,          // GLenum target
		GL_TEXTURE_MIN_FILTER,  // GLenum pname
		GL_NEAREST);            // GLint param

	glTexParameteri(
		GL_TEXTURE_2D,          // GLenum target
		GL_TEXTURE_MAG_FILTER,  // GLenum pname
		GL_NEAREST);

	free(pixels);

	return handle;
}