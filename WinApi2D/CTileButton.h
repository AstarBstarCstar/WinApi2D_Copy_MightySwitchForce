#pragma once
#include "CButtonUI.h"
#include "CGameObject.h"
class CTileButton : public CButtonUI
{
private:
	CD2DImage* m_pImg;
	int m_iIdx;

public:
	CTileButton();
	virtual ~CTileButton();

	virtual void render();

	int GetIdx();
	void SetIdx(int idx);
	void SetImage(CD2DImage* img);
};