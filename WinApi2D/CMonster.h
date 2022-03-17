#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;

class CMonster : public CGameObject
{
private:
	CD2DImage* m_MImg;
	AI* m_pAI;
	fPoint m_fptCenterPos;
	float m_fVelocity;
	float m_fDistance;
	bool m_bIsUPDir;

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* Clone();

	virtual void update();
	virtual void render();

	void SetAI(AI* ai);
	void SetCenterPos(fPoint point);

	void OnCollisionEnter(CCollider* pOther);
};

