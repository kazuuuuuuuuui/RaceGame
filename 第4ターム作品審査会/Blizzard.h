#include"Effect.h"

class Blizzard :public Effect{
public:
	
	void Draw();
	void Update();

	bool isHit(oka::Vec3 _position);

};