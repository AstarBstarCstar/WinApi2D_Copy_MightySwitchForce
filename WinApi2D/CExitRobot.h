#pragma once
#include"CGameObject.h"


class CD2DImage;

class CExitRobot :public CGameObject
{
public:
	int Count = 0;
	CExitRobot();
	virtual ~CExitRobot();
	virtual void OnCollision(CCollider* pOther);
	virtual CExitRobot* Clone();
	virtual void render();
	virtual void update();
	float accel = 0.f;
	float timer = 0.f;
	bool trriger=true;
	bool End = false;
};

