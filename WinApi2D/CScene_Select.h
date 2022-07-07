#pragma once
#include "CScene.h"

class CScene_Select : public CScene
{
public:
	CScene_Select();
	virtual ~CScene_Select();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
	bool m_isChanged;
	float timer = 0.f;
};

