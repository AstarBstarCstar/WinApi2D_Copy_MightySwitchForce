#pragma once
#include "CGameObject.h"
class CD2DImage;



class SwitchBlock : public CGameObject
{
public:
	CD2DImage* m_pImg;
	BLOCK_CHANGE m_eChanger;
	bool m_bSW;
	float fDuration;
	float fCurTime;
	SwitchBlock();
	~SwitchBlock();

	virtual SwitchBlock* Clone();

	virtual void update();
	virtual void render();
	//bool GetSwitching();
	//void SetSwitching(bool SW);

};
