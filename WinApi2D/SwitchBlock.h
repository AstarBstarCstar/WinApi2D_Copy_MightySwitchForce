#pragma once
#include "CGameObject.h"
class CD2DImage;

class SwitchBlock : public CGameObject
{
public:
	bool SW;
	SwitchBlock();
	~SwitchBlock();

	virtual void update();
	virtual void render();
	void Switch();
};

