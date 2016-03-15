#include"Effect.h"

class Blizzard :public Effect{
public:
	
	void draw();
	void update();

	bool isHit(oka::Vec3 _position);

};