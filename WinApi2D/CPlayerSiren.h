#pragma once
#include "CGameObject.h"
class CD2DImage;
class CAnimation;

class CPlayerSiren : public CGameObject
{
public:
	CD2DImage* m_pImg;
	CAnimation* pAni;
	fVec2 m_fvDir;
	bool isChecked;
	CPlayerSiren();
	~CPlayerSiren();
	void SetDir(fVec2 vec);
	void SetDir(float theta);
	virtual CPlayerSiren* Clone();
	virtual void update();
	virtual void render();
};

