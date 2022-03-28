#pragma once
#include "CGameObject.h"
class CD2DImage;

class SwitchBlock : public CGameObject
{
public:
	bool SW;
	SwitchBlock();
	~SwitchBlock();

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
