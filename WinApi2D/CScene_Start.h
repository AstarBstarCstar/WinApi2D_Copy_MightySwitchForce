#pragma once
#include "CScene.h"

class CD2DImage;
class CHolliganSave;
class CButtonUI;

class CScene_Start : public CScene
{
private:
	void ObjectSetter();
	void UISetter();
public:
	CScene_Start();
	virtual ~CScene_Start();

	virtual void update();
	virtual void Enter();

	virtual void Exit();
	fPoint playerPos;

	CButtonUI* m_pMin;
	CButtonUI* m_pCel;
	CButtonUI* m_pSec;
	wstring Time_min;
	wstring Time_sec;
	wstring Time_cel;

	bool CameraLock=false;
	bool Count=false;
	static float timer;
	static bool isStop;

	float initTimer;
	float changeTimer;
	float temp = 0.f;
	int min;
	int sec;
	int cel;

};
