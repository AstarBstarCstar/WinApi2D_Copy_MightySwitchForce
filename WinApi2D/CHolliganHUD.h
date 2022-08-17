#pragma once
#include "CUI.h"
class CD2DImage;


class CHolliganHUD :public CUI
{
private:
	fPoint m_fptPos;
	fPoint m_fptScale;
	CD2DImage* m_pImg;
	

public:
	CHolliganHUD();
	virtual ~CHolliganHUD();

	virtual void update();
	virtual void render();
	virtual CHolliganHUD* Clone();

	void SetPos(const fPoint& fptPos) { m_fptPos = fptPos; }
	const fPoint& GetPos() { return m_fptPos; }

	void SetScale(const fPoint& fptScale) { m_fptScale = fptScale; }
	const fPoint& GetScale() { return m_fptScale; }
	void SetImage(CD2DImage* pImg) { m_pImg = pImg; }
};
