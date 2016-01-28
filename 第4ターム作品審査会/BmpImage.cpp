#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
#include<Windows.h>
#include"Course.h"
#include"BmpImage.h"
#include"Item.h"

//-------------------------------------
//bmp�摜����A���t�@�l�t���̃e�N�X�`���쐬

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

	//�s�N�Z���P�ʂ�R��B���t�]������
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

		//���Ȃ�A���t�@�l0�Ƃ���
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
		GL_RGBA,          //GLint internalformat(��������e�N�X�`���̃t�H�[�}�b�g)
		bmpInfoHeader.biWidth,               //GLsizei width
		bmpInfoHeader.biHeight,               //GLsizei height
		0,               //GLint border
		GL_RGBA,          //GLenum format(�s�N�Z���f�[�^�̃t�H�[�}�b�g)
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

/*�g���q.bmp�̉摜�ǂݍ���*/
GLuint BmpImage::loadImage(const char *_fileName){
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

	//�s�N�Z���P�ʂ�R��B���t�]������
	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	//�s�N�Z���P�ʂŏ㉺���]
	for (int i = 0; i < bmpInfoHeader.biWidth; i++){
		for (int n = 0; n < bmpInfoHeader.biHeight / 2; n++){
			RGB temp = pixels[bmpInfoHeader.biWidth * n + i];
			pixels[bmpInfoHeader.biWidth * n + i] = pixels[bmpInfoHeader.biWidth*(bmpInfoHeader.biHeight - n - 1) + i];
			pixels[bmpInfoHeader.biWidth*(bmpInfoHeader.biHeight - n - 1) + i] = temp;
		}
	}

	GLuint handle;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);

	//pixcel
	glTexImage2D(
		GL_TEXTURE_2D,   //GLenum target
		0,               //GLint level
		GL_RGB,          //GLint internalformat(��������e�N�X�`���̃t�H�[�}�b�g)
		bmpInfoHeader.biWidth,               //GLsizei width
		bmpInfoHeader.biHeight,               //GLsizei height
		0,               //GLint border
		GL_RGB,          //GLenum format(�s�N�Z���f�[�^�̃t�H�[�}�b�g)
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


//-------------------------------------
//���G�t�F�N�g�ǂݍ��ݐ�p

GLuint BmpImage::loadImage_smoke(const char *_Filename){
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

	fread(
		pixels,
		imageSize,
		1,
		pBinMapFile
		);
	fclose(pBinMapFile);


	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	int texDataSize = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * sizeof(RGBA);
	RGBA *pixelsData = (RGBA*)malloc(texDataSize);

	//RGB�𔒂ŏ�����
	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
		pixelsData[i].r = 0xff;
		pixelsData[i].g = 0xff;
		pixelsData[i].b = 0xff;
	}

	//�e�s�N�Z����R�̒l���A�e�N�X�`���p�s�N�Z���̃A���t�@�l�ɏ������ށB
	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
		pixelsData[i].a = pixels[i].r;
	}

	GLuint textures;

	glGenTextures(
		1,        //GLsizei n
		&textures);//GLuint *textures


	//pixceldata
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target
		textures//GLuint texture
		);

	glTexImage2D(
		GL_TEXTURE_2D,   //GLenum target
		0,               //GLint level
		GL_RGBA,          //GLint internalformat(��������e�N�X�`���̃t�H�[�}�b�g)
		bmpInfoHeader.biWidth,               //GLsizei width
		bmpInfoHeader.biHeight,               //GLsizei height
		0,               //GLint border
		GL_RGBA,          //GLenum format(�s�N�Z���f�[�^�̃t�H�[�}�b�g)
		GL_UNSIGNED_BYTE,//GLenum type
		pixelsData          //const GLvoid *pixels
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
	free(pixelsData);

	return textures;
}

//-------------------------------------
//�g���qbmp����R�[�X�p�̃o�b�t�@���쐻����

void BmpImage::makeBuffer(const char *_bufferName, int _buffer[][COURSE_WIDTH]){
	FILE *pBinMapFile;
	pBinMapFile = fopen(_bufferName, "rb");

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

	//�s�N�Z���P�ʂ�R��B���t�]������
	for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	//�s�N�Z���P�ʂŏ㉺���]
	for (int i = 0; i < bmpInfoHeader.biWidth; i++){
		for (int n = 0; n < bmpInfoHeader.biHeight / 2; n++){
			RGB temp = pixels[bmpInfoHeader.biWidth * n + i];
			pixels[bmpInfoHeader.biWidth * n + i] = pixels[bmpInfoHeader.biWidth*(bmpInfoHeader.biHeight - n - 1) + i];
			pixels[bmpInfoHeader.biWidth*(bmpInfoHeader.biHeight - n - 1) + i] = temp;
		}
	}

	//�R�[�X����p�̃o�b�t�@�쐬
	for (int i = 0; i < bmpInfoHeader.biHeight; i++){
		for (int t = 0; t < bmpInfoHeader.biWidth; t++){

			//���Ȃ瓹
			if (pixels[t + i*bmpInfoHeader.biWidth].r >= 250 &&
				pixels[t + i*bmpInfoHeader.biWidth].g >= 250 &&
				pixels[t + i*bmpInfoHeader.biWidth].b >= 250){

				_buffer[i][t] = PATH;
			}

			//���Ȃ�_�[�g
			else if (pixels[t + i*bmpInfoHeader.biWidth].r <= 5 &&
				pixels[t + i*bmpInfoHeader.biWidth].g <= 5 &&
				pixels[t + i*bmpInfoHeader.biWidth].b <= 5){
				_buffer[i][t] = DART;
			}

			//�ԂȂ�X�^�[�g
			else if (pixels[t + i*bmpInfoHeader.biWidth].r == 255 &&
				pixels[t + i*bmpInfoHeader.biWidth].g == 0 &&
				pixels[t + i*bmpInfoHeader.biWidth].b == 0){

				_buffer[i][t] = START;
			}

			//�Ȃ�S�[��
			else if (pixels[t + i*bmpInfoHeader.biWidth].r == 0 &&
				pixels[t + i*bmpInfoHeader.biWidth].g == 0 &&
				pixels[t + i*bmpInfoHeader.biWidth].b == 255){

				_buffer[i][t] = GOAL;
			}

			//�΂Ȃ�A�C�e���̏ꏊ
			else if (pixels[t + i*bmpInfoHeader.biWidth].r == 0 &&
				pixels[t + i*bmpInfoHeader.biWidth].g == 255 &&
				pixels[t + i*bmpInfoHeader.biWidth].b == 0){
				_buffer[i][t] = ITEMPOSITION;
			}
		}

	}

	free(pixels);

}