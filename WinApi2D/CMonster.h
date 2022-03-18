#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;

struct tMonInfo
{
	float fSpeed;
	float fHP;
	float fRecogRange;
	float fAttRange;
	float fAtt;
};

enum class MON_TYPE
{
	NORMAL,
	RANGE,

	SIZE,
};

class CMonster : public CGameObject
{
private:
	tMonInfo m_tInfo;
	AI* m_pAI;

public:
	CMonster();
	virtual ~CMonster();
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

