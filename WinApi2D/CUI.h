#pragma once
#include "CGameObject.h"
class CUI : public CGameObject
{
	friend class CUIManager;

private:
	vector<CUI*> m_vecChildUI;	// 자식 UI를 계층적 구조로 구현
	CUI* m_pParentUI;// 부모 UI

	fPoint m_fptFinalPos;

	bool m_bCameraAffected; //카메라 영향을 받는다면 True
	bool m_bMouseOn;  //이전 프레임에 마우스 올려져있으면 True
	bool m_bLbtnDown;			// UI에서 이전에 눌렸다.

	CD2DImage* m_pImg;

	wstring		m_strText;
	COLORREF	m_rgbTxtColor;
	COLORREF	m_rgbTxtShadowColor;

public:
	CUI();	
	CUI(const CUI& other);
	virtual ~CUI();

	virtual CUI* Clone() = 0;

	virtual void update();
	virtual void finalupdate();
	virtual void render();

	void update_child();
	void finalupdate_child();
	void render_child();

	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	fPoint GetFinalPos();

	bool GetCameraAffected();
	void SetCameraAffected(bool isAffected);
	bool IsMouseOn();
	bool IsLbtnDown();

	CUI* GetParent();
	void AddChild(CUI* pUI);
	const vector<CUI*>& GetChildUI();

	void LoadImg(const wstring& strKey, const wstring& strRelativePath);

	void SetText(const wstring& text);
	const wstring& GetText();

	void SetTextColor(const COLORREF color);
	const COLORREF GetTextColor();

	void SetTxtShadowColor(const COLORREF color);
	const COLORREF GetTxtShadowColor();

	void SelectUI();
	void DeselectUI();



private:
	void MouseOnCheck();
};