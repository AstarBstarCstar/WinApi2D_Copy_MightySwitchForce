#pragma once
#include "CScene.h"

class CD2DImage;

class CScene_Title : public CScene
{
	
	
public:
	float m_Count;
	bool m_Trigger = false;
	CScene_Title();
	virtual ~CScene_Title();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

