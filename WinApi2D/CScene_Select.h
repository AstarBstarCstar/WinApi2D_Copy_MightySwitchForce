#pragma once
#include "CScene.h"

class CButtonUI;

class CScene_Select : public CScene
{
public:
	CScene_Select();
	virtual ~CScene_Select();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
	void TimerSetter();
	bool m_isChanged;
	float timer = 0.f;
	bool is_checked = false;

	static float temptimer;
	CButtonUI* m_pMin;
	CButtonUI* m_pCel;
	CButtonUI* m_pSec;
	wstring Time_min;
	wstring Time_sec;
	wstring Time_cel;


};

