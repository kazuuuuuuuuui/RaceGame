#ifndef _OKA_BMPIMAGE_H_
#define _OKA_BMPIMAGE_H_

#include<stdlib.h>
#include"Course.h"

namespace oka 
{
	//-------------------------------------
	//�摜�t�@�C���̃s�N�Z���\����
	//RGB   ���ߓx����
	//RGBA�@���ߓx�L��

	struct RGB
	{
		unsigned char r, g, b;
	};

	struct RGBA
	{
		unsigned char r, g, b, a;
	};

	//-------------------------------------
	//

	unsigned int LoadImage3f(const char *_fileName);
	unsigned int LoadImage4f(const char *_filename);

}

#endif