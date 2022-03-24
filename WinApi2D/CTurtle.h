#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;

class CTurtle : public CGameObject
{
private:
	tMonInfo m_tInfo;
	AI* m_pAI;

public:
	CTurtle();
	virtual ~CTurtle();
	virtual CTurtle* Clone();

	static CTurtle* Create(MON_TYPE type, fPoint pos);

	virtual void render();
	virtual void update();

	float GetSpeed();
	const tMonInfo& GetMonInfo();

	void SetSpeed(float speed);
	void SetAI(AI* ai);
	void SetMonInfo(const tMonInfo& info);

	void OnCollisionEnter(CCollider* pOther);
};