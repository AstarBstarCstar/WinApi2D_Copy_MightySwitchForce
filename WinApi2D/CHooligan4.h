#pragma once
#include"CGameObject.h"

class CD2DImage;

class CHooligan4:public CGameObject
{
public:
	int Count = 0;
	CHooligan4();
	virtual ~CHooligan4();
	virtual CHooligan4* Clone();
	void OnCollisionEnter(CCollider* pOther);
	virtual void render();
	virtual void update();
};

