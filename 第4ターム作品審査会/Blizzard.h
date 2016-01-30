#include"Effect.h"

class Blizzard :public Effect{
public:
	
	void draw();
	void update();

	bool isHit(glm::vec3 _position);

};