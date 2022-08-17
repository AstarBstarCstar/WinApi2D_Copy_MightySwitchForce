#pragma once
#include "CScene.h"

class CD2DImage;

class CScene_Ending : public CScene
{


public:
	float m_Count;
	bool m_Trigger = false;
	CScene_Ending();
	virtual ~CScene_Ending();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};
