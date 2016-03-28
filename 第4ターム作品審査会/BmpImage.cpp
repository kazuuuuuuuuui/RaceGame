#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
#include<Windows.h>
#include"Course.h"
#include"BmpImage.h"
#include"Item.h"

namespace oka
{
	//-------------------------------------
	//拡張子.bmpの画像読み込み
	//戻り値としてunsigned int型のハンドル(ID)を返す
	
	unsigned int LoadImage3f(const char *_fileName)
	{
		FILE *fp;
		fp = fopen(_fileName, "rb");

		assert(fp != NULL);

		BITMAPFILEHEADER bh;
		fread(&bh, sizeof(BITMAPFILEHEADER), 1, fp);

		BITMAPINFOHEADER bih;
		fread(&bih, sizeof(BITMAPINFOHEADER), 1, fp);

		int imageSize = bih.biWidth * bih.biHeight * sizeof(RGB);

		RGB *pixels = (RGB*)malloc(imageSize);

		pixels = (RGB*)malloc(imageSize);

		fread(pixels, imageSize, 1, fp);

		fclose(fp);

		//ピクセル単位でRとBを逆転させる
		for (int i = 0; i < bih.biWidth * bih.biHeight; i++)
		{
			unsigned char tmp;
			tmp = pixels[i].r;
			pixels[i].r = pixels[i].b;
			pixels[i].b = tmp;
		}

		//ピクセル単位で上下反転
		for (int i = 0; i < bih.biWidth; i++)
		{
			for (int n = 0; n < bih.biHeight / 2; n++)
			{
				RGB temp = pixels[bih.biWidth * n + i];
				pixels[bih.biWidth * n + i] = pixels[bih.biWidth*(bih.biHeight - n - 1) + i];
				pixels[bih.biWidth*(bih.biHeight - n - 1) + i] = temp;
			}
		}

		unsigned int handle;

		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,            
			GL_RGB,//生成するテクスチャのフォーマット
			bih.biWidth,
			bih.biHeight,
			0,
			GL_RGB,//ピクセルデータのフォーマット
			GL_UNSIGNED_BYTE,
			pixels
			);

		glTexParameteri(
			GL_TEXTURE_2D,          
			GL_TEXTURE_MIN_FILTER,  
			GL_NEAREST);    

		glTexParameteri(
			GL_TEXTURE_2D,         
			GL_TEXTURE_MAG_FILTER, 
			GL_NEAREST);

		free(pixels);

		return handle;
	}

	//-------------------------------------
	//bmp画像からアルファ値付きのテクスチャ作成

	unsigned int LoadImage4f(const char *_filename)
	{
		FILE *fp;
		fp = fopen(_filename, "rb");

		assert(fp != NULL);

		BITMAPFILEHEADER bh;
		fread(&bh,sizeof(BITMAPFILEHEADER),1,fp);

		BITMAPINFOHEADER bih;
		fread(&bih,sizeof(BITMAPINFOHEADER),1,fp);

		int imageSize3f = bih.biWidth * bih.biHeight * sizeof(RGB);
		RGB *pixels3f = (RGB*)malloc(imageSize3f);

		int imageSize4f = bih.biWidth * bih.biHeight * sizeof(RGBA);
		RGBA *pixels4f = (RGBA*)malloc(imageSize4f);

		fread(pixels3f,imageSize3f,1,fp);
		fclose(fp);

		//ピクセル単位でRとBを逆転させる
		for (int i = 0; i < bih.biWidth * bih.biHeight; i++) {
			unsigned char tmp;
			tmp = pixels3f[i].r;
			pixels3f[i].r = pixels3f[i].b;
			pixels3f[i].b = tmp;
		}

		//ピクセル単位で上下反転
		for (int i = 0; i < bih.biWidth; i++) 
		{
			for (int n = 0; n < bih.biHeight / 2; n++) 
			{
				RGB temp = pixels3f[bih.biWidth * n + i];
				pixels3f[bih.biWidth * n + i] = pixels3f[bih.biWidth*(bih.biHeight - n - 1) + i];
				pixels3f[bih.biWidth*(bih.biHeight - n - 1) + i] = temp;
			}
		}


		for (int i = 0; i < bih.biWidth * bih.biHeight; i++)
		{
			pixels4f[i].r = pixels3f[i].r;
			pixels4f[i].g = pixels3f[i].g;
			pixels4f[i].b = pixels3f[i].b;

			//白ならアルファ値0とする
			if (pixels4f[i].r == 255 && pixels4f[i].g == 255 && pixels4f[i].b == 255)
			{
				pixels4f[i].a = 0;
			}
			else 
			{
				pixels4f[i].a = 255;
			}
		}

		unsigned int handle;

		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);

		glTexImage2D(
			GL_TEXTURE_2D,  
			0,             
			GL_RGBA,          //生成するテクスチャのフォーマット
			bih.biWidth,             
			bih.biHeight,             
			0,              
			GL_RGBA,          //ピクセルデータのフォーマット
			GL_UNSIGNED_BYTE,
			pixels4f         
			);

		glTexParameteri(
			GL_TEXTURE_2D,         
			GL_TEXTURE_MIN_FILTER, 
			GL_NEAREST);            

		glTexParameteri(
			GL_TEXTURE_2D,         
			GL_TEXTURE_MAG_FILTER,  
			GL_NEAREST);

		free(pixels3f);
		free(pixels4f);

		return handle;
	}

	//-------------------------------------
	//拡張子bmpからコース用のバッファを作製する

	void MakeBuffer(const char *_bufferName, int _buffer[][COURSE_WIDTH]) 
	{
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

		//ピクセル単位でRとBを逆転させる
		for (int i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++) {
			unsigned char tmp;
			tmp = pixels[i].r;
			pixels[i].r = pixels[i].b;
			pixels[i].b = tmp;
		}

		//ピクセル単位で上下反転
		for (int i = 0; i < bmpInfoHeader.biWidth; i++) {
			for (int n = 0; n < bmpInfoHeader.biHeight / 2; n++) {
				RGB temp = pixels[bmpInfoHeader.biWidth * n + i];
				pixels[bmpInfoHeader.biWidth * n + i] = pixels[bmpInfoHeader.biWidth*(bmpInfoHeader.biHeight - n - 1) + i];
				pixels[bmpInfoHeader.biWidth*(bmpInfoHeader.biHeight - n - 1) + i] = temp;
			}
		}

		//コース判定用のバッファ作成
		for (int i = 0; i < bmpInfoHeader.biHeight; i++) {
			for (int t = 0; t < bmpInfoHeader.biWidth; t++) {

				//白なら道
				if (pixels[t + i*bmpInfoHeader.biWidth].r == 255 &&
					pixels[t + i*bmpInfoHeader.biWidth].g == 255 &&
					pixels[t + i*bmpInfoHeader.biWidth].b == 255) {

					_buffer[i][t] = PATH;
				}

				//黒ならダート
				else if (pixels[t + i*bmpInfoHeader.biWidth].r == 0 &&
					pixels[t + i*bmpInfoHeader.biWidth].g == 0 &&
					pixels[t + i*bmpInfoHeader.biWidth].b == 0) {
					_buffer[i][t] = DART;
				}

				//赤ならスタート
				else if (pixels[t + i*bmpInfoHeader.biWidth].r == 255 &&
					pixels[t + i*bmpInfoHeader.biWidth].g == 0 &&
					pixels[t + i*bmpInfoHeader.biWidth].b == 0) {

					_buffer[i][t] = START;
				}

				//青ならゴール
				else if (pixels[t + i*bmpInfoHeader.biWidth].r == 0 &&
					pixels[t + i*bmpInfoHeader.biWidth].g == 0 &&
					pixels[t + i*bmpInfoHeader.biWidth].b == 255) {

					_buffer[i][t] = GOAL;
				}

				//緑ならアイテムの場所
				else if (pixels[t + i*bmpInfoHeader.biWidth].r == 0 &&
					pixels[t + i*bmpInfoHeader.biWidth].g == 255 &&
					pixels[t + i*bmpInfoHeader.biWidth].b == 0) {
					_buffer[i][t] = ITEMPOSITION;
				}
			}

		}

		free(pixels);

	}

}