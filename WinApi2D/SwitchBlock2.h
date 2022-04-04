#pragma once
#include "CGameObject.h"
class CD2DImage;

class SwitchBlock2 : public CGameObject
{
public:
	CD2DImage* m_pImg;

	BLOCK_CHANGE m_eChanger;
	bool m_bSW;
	float fDuration;
	float fCurTime;

	SwitchBlock2();
	~SwitchBlock2();
	virtual SwitchBlock2* Clone();

	virtual void update();
	virtual void render();

};
