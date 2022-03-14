#pragma once
#include "CGameObject.h"

class CD2DImage;

class CMonster : public CGameObject
{
private:
	CD2DImage* m_MImg;
	fPoint m_fptCenterPos;
	float m_fVelocity;
	float m_fDistance;
	bool m_bIsUPDir;

public:
	CMonster();
	~CMonster();
	virtual CMonster* Clone();

	virtual void update();
	virtual void render();

	void SetCenterPos(fPoint point);

	void OnCollisionEnter(CCollider* pOther);
};

