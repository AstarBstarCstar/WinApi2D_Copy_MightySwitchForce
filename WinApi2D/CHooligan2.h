#pragma once
#include"CGameObject.h"

class CD2DImage;

class CHooligan2 :public CGameObject
{
public:
	int Count = 0;
	CHooligan2();
	virtual ~CHooligan2();
	void OnCollisionEnter(CCollider* pOther);
	virtual CHooligan2* Clone();
	virtual void render();
	virtual void update();
};

