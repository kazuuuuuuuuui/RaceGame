#ifndef _OKA_BMPIMAGE_H_
#define _OKA_BMPIMAGE_H_

#include<stdlib.h>
#include"Course.h"

namespace oka 
{
	//-------------------------------------
	//画像ファイルのピクセル構造体
	//RGB   透過度無し
	//RGBA　透過度有り

	struct RGB{
		unsigned char r, g, b;
	};

	struct RGBA{
		unsigned char r, g, b, a;
	};

	//-------------------------------------
	//

	class BmpImage
	{
	public:

		static unsigned int LoadImage3f(const char *_fileName);
		static unsigned int LoadImage4f(const char *_filename);

		static void makeBuffer(const char *_bufferName, int _buffer[][COURSE_WIDTH]);
	};

}

#endif