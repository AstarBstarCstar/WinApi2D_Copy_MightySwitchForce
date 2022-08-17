#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;

class CMonster : public CGameObject
{
private:
	tMonInfo m_tInfo;
	fPoint m_fCurDir;
	AI* m_pAI;
	CD2DImage* m_pImg2;

public:

	CMonster();
	virtual ~CMonster();
	void SetAnim(bool setter);
	virtual CMonster* Clone();

	static CMonster* Create(MON_TYPE type, fPoint pos);

	virtual void render();
	virtual void update();

	float GetSpeed();
	const tMonInfo& GetMonInfo();

	void SetSpeed(float speed);
	void SetAI(AI* ai);
	void SetMonInfo(const tMonInfo& info);

	void OnCollisionEnter(CCollider* pOther);
	void OnCollision(CCollider* pOther);
	bool hit;
	float deletetimer;
};













//#pragma once
//#include "CGameObject.h"
//
//class CD2DImage;
//class AI;
//
//class CMonster : public CGameObject
//{
//private:
//	CD2DImage* m_MImg;
//	AI* m_pAI;
//	fPoint m_fptCenterPos;
//	float m_fVelocity;
//	float m_fDistance;
//	bool m_bIsUPDir;
//
//public:
//	CMonster();
//	virtual ~CMonster();
//	virtual CMonster* Clone();
//
//	virtual void update();
//	virtual void render();
//
//	void SetAI(AI* ai);
//	void SetCenterPos(fPoint point);
//
//	void OnCollisionEnter(CCollider* pOther);
//};

