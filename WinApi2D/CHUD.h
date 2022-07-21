#pragma once
#include "CUI.h"
class CD2DImage;


class CHUD :public CUI
{
private:
	fPoint m_fptPos;
	fPoint m_fptScale;
	CD2DImage* m_pImg;		

public:
	CHUD();
	virtual ~CHUD();

	virtual void update();
	virtual void render();
	virtual CHUD* Clone();


	void SetPos(const fPoint& fptPos) { m_fptPos = fptPos; }
	const fPoint& GetPos() { return m_fptPos; }

	void SetScale(const fPoint& fptScale) { m_fptScale = fptScale; }
	const fPoint& GetScale() { return m_fptScale; }
	void SetImage(CD2DImage* pImg) { m_pImg = pImg; }
};

