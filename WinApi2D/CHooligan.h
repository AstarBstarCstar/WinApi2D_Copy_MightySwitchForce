#pragma once
#include"CGameObject.h"

class CD2DImage;

class CHooligan:public CGameObject
{
public:
	static CHooligan* instance;
	CHooligan();

	virtual ~CHooligan();

	virtual CHooligan* Clone();
	virtual void render();
	virtual void update();
};

