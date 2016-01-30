#ifndef LOADIMAGE_H_
#define LOADIMAGE_H_

#include<stdlib.h>
#include"Course.h"
#include"glut.h"

//“§‰ß“x–³‚µ
class RGB{
public:
	unsigned char r, g, b;
};

class RGBA{
public:
	unsigned char r, g, b, a;
};

class BmpImage{
public:
	GLuint m_handle;
	RGB m_pixel;

	static GLuint loadImage(const char *_fileName);

	static void makeBuffer(const char *_bufferName, int _buffer[][COURSE_WIDTH]);

	static GLuint loadImage_alpha(const char *_Filename);

	static GLuint loadImage_smoke(const char *_Filename);


};


extern GLuint handle;



#endif