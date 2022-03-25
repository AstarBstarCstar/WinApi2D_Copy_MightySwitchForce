#include "framework.h"
#include "CUI.h"

CUI::CUI()
{
	m_pParentUI = nullptr;
	m_bCameraAffected = false;
	m_bMouseOn = false;
	m_bLbtnDown = false;

	m_pImg = nullptr;
	m_strText = L"";
	m_rgbTxtColor = RGB(255, 255, 255);
	m_rgbTxtShadowColor = RGB(0, 0, 0);
}

CUI::CUI(const CUI& other)
	: CGameObject(other)		// 부모의 복사생성자를 지정해주어야 함
{
	m_pParentUI = nullptr;
	m_bCameraAffected = other.m_bCameraAffected;
	m_bMouseOn = false;
	m_bLbtnDown = false;
	m_pImg = nullptr;
	m_strText = L"";
	m_rgbTxtColor = RGB(255, 255, 255);
	m_rgbTxtShadowColor = RGB(0, 0, 0);
	for (UINT i = 0; i < other.m_vecChildUI.size(); i++)
	{
		AddChild(other.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	for (int i = 0; i < m_vecChildUI.size(); i++)
	{
		if (nullptr != m_vecChildUI[i])
			delete m_vecChildUI[i];
	}
}

void CUI::update()
{
	update_child();
}

void CUI::finalupdate()
{
	CGameObject::finalupdate();

	m_fptFinalPos = GetPos();
	if (GetParent())
	{
		fPoint fptParentPos = GetParent()->GetFinalPos();
		m_fptFinalPos += fptParentPos;
	}

	MouseOnCheck();

	finalupdate_child();
}

void CUI::render()
{
	fPoint fptPos = GetPos();
	fPoint fptFPos = GetFinalPos();
	fPoint fptScale = GetScale();

	if (m_bCameraAffected)	// 카메라 영향 받으면 랜더링 좌표로
	{
		fptFPos = CCameraManager::GetInst()->GetRenderPos(fptFPos);
	}

	render_child();
}

void CUI::update_child()
{
	for (UINT i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate_child()
{
	for (UINT i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::render_child()
{
	for (UINT i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->render();
	}
}

void CUI::MouseOn()
{
	int a = 0;
}

void CUI::MouseLbtnDown()
{
	int a = 0;
}

void CUI::MouseLbtnUp()
{
	int a = 0;
}

void CUI::MouseLbtnClicked()
{
	int a = 0;
}

fPoint CUI::GetFinalPos()
{
	return m_fptFinalPos;
}

bool CUI::GetCameraAffected()
{
	return m_bCameraAffected;
}

void CUI::SetCameraAffected(bool isAffected)
{
	m_bCameraAffected = isAffected;
}

bool CUI::IsMouseOn()
{
	return m_bMouseOn;
}

bool CUI::IsLbtnDown()
{
	return m_bLbtnDown;
}

CUI* CUI::GetParent()
{
	return m_pParentUI;
}

void CUI::AddChild(CUI* pUI)
{
	m_vecChildUI.push_back(pUI);
	pUI->m_pParentUI = this;
	pUI->SetCameraAffected(this->m_bCameraAffected);
}

const vector<CUI*>& CUI::GetChildUI()
{
	return m_vecChildUI;
}

void CUI::LoadImg(const wstring& strKey, const wstring& strRelativePath)
{
	m_pImg = CResourceManager::GetInst()->LoadD2DImage(strKey, strRelativePath);
}

void CUI::SetText(const wstring& text)
{
	m_strText = text;
}

const wstring& CUI::GetText()
{
	return m_strText;
}

void CUI::SetTextColor(const COLORREF color)
{
	m_rgbTxtColor = color;
}

const COLORREF CUI::GetTextColor()
{
	return m_rgbTxtColor;
}

void CUI::SetTxtShadowColor(const COLORREF color)
{
	m_rgbTxtShadowColor = color;
}

const COLORREF CUI::GetTxtShadowColor()
{
	return m_rgbTxtShadowColor;
}

void CUI::SelectUI()
{
	m_bMouseOn = true;
	CUIManager::GetInst()->SetFocusedUI(this);
}

void CUI::DeselectUI()
{
	m_bMouseOn = false;
}

void CUI::MouseOnCheck()
{
	fPoint fptMousePos = MousePos();
	fPoint fptScale = GetScale();

	if (m_bCameraAffected)
	{
		fptMousePos = CCameraManager::GetInst()->GetRenderPos(fptMousePos);
	}

	if (m_fptFinalPos.x <= fptMousePos.x && fptMousePos.x <= m_fptFinalPos.x + fptScale.x
		&& m_fptFinalPos.y <= fptMousePos.y && fptMousePos.y <= m_fptFinalPos.y + fptScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}