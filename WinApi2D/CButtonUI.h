#pragma once
#include "CUI.h"

class CD2DImage;

// 함수포인터를 위한 타입정의
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class CButtonUI : public CUI
{
private:
	BTN_FUNC m_pFunc;
	DWORD_PTR m_pParam1;
	DWORD_PTR m_pParam2;
	int m_FontSize;

public:
	CButtonUI();
	~CButtonUI();

	virtual CButtonUI* Clone();

	virtual void render();

	void SetFontSize(int size);

	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	void SetClickedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2);
};

