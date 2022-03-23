#pragma once
#include"CGameObject.h"

class CD2DImage;

class CHooligan3 :public CGameObject
{
public:
	int Count = 0;
	CHooligan3();
	virtual ~CHooligan3();
	void OnCollisionEnter(CCollider* pOther);
	virtual CHooligan3* Clone();
	virtual void render();
	virtual void update();
};

