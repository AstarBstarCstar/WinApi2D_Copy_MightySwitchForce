#pragma once
#include"CGameObject.h"

class CD2DImage;

class CHooligan:public CGameObject
{
public:
	int Count = 0;
	CHooligan();
	virtual ~CHooligan();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual CHooligan* Clone();
	virtual void render();
	virtual void update();
};

