#pragma once
#include "CScene.h"
class COpening :
	public CScene
{
private:
	HWND m_Opening;
	bool videoTrigger;
public:
	void Initialize();
public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
public:
	COpening();
	~COpening();
};