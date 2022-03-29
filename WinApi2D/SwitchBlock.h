#pragma once
#include "CGameObject.h"
class CD2DImage;

class SwitchBlock : public CGameObject
{
public:
	CD2DImage* m_pImg;

	bool m_bSW;
	float m_fAlp;
	SwitchBlock();
	~SwitchBlock();
	virtual SwitchBlock* Clone();

	virtual void update();
	virtual void render();

	void Switch();
};

//#pragma once
//#include "CGameObject.h"
//
//class CD2DImage;
//
//class CPlatform : public CGameObject
//{
//	CD2DImage* m_pImg;
//
//public:
//	CPlatform();
//	virtual ~CPlatform();
//	virtual CPlatform* Clone();
//
//	virtual void update();
//	virtual void render();
//};
//
