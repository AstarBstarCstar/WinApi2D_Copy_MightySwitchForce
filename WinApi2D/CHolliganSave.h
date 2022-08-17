#pragma once
#include "CUI.h"
class CD2DImage;


class CHolliganSave:public CUI
{
private:
	fPoint m_fptPos;
	const fPoint m_fptPos0 = { 600.f, 70.f };
	const fPoint m_fptPos1 = { 700.f, 70.f };
	const fPoint m_fptPos2 = { 800.f, 70.f };
	const fPoint m_fptPos3 = { 900.f, 70.f };
	const fPoint m_fptPos4 = { 1000.f, 70.f };
	
	fPoint m_fptScale;
	CD2DImage* m_pImg2;


public:
	CHolliganSave();
	virtual ~CHolliganSave();

	virtual void update();
	virtual void render();
	virtual CHolliganSave* Clone();

	void SetPos(const fPoint& fptPos) { m_fptPos = fptPos; }
	const fPoint& GetPos() { return m_fptPos; }

	void SetScale(const fPoint& fptScale) { m_fptScale = fptScale; }
	const fPoint& GetScale() { return m_fptScale; }
	void SetImage(CD2DImage* pImg) { m_pImg2 = pImg; }
	static short isGet;
};
