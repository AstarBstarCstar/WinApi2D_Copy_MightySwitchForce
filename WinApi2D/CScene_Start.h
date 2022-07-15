#pragma once
#include "CScene.h"

class CD2DImage;

class CScene_Start : public CScene
{
public:
	CScene_Start();
	virtual ~CScene_Start();

	virtual void update();
	virtual void Enter();

	virtual void Exit();
	fPoint playerPos;

	bool CameraLock=false;
	bool Count=false;
};
