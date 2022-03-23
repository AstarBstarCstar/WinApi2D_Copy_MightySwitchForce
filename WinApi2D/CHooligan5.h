#pragma once
#include"CGameObject.h"

class CD2DImage;

class CHooligan5 :public CGameObject
{
public:
	int Count = 0;
	CHooligan5();
	virtual ~CHooligan5();
	virtual CHooligan5* Clone();
	void OnCollisionEnter(CCollider* pOther);
	virtual void render();
	virtual void update();
};

