#pragma once
#include "CGameObject.h"
class CUI : public CGameObject
{
	friend class CUIManager;

private:
	vector<CUI*> m_vecChildUI;	// �ڽ� UI�� ������ ������ ����
	CUI* m_pParentUI;// �θ� UI

	fPoint m_fptFinalPos;

	bool m_bCameraAffected; //ī�޶� ������ �޴´ٸ� True
	bool m_bMouseOn;  //���� �����ӿ� ���콺 �÷��������� True
	bool m_bLbtnDown;			// UI���� ������ ���ȴ�.

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