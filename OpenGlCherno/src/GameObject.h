#ifndef _GAMEOBJ
#define _GAMEOBJ

#include "util/Vec3d.h"

class GameObject {
private:
	Vec3d pos;
public:
	GameObject();
	virtual ~GameObject();
};

#endif