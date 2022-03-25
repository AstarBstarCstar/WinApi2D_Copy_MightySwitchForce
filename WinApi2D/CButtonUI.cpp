#include "framework.h"
#include "CButtonUI.h"

CButtonUI::CButtonUI()
{
	m_pFunc = nullptr;
	m_pParam1 = {};
	m_pParam2 = {};
	m_FontSize = 36;
}

CButtonUI::~CButtonUI()
{
}

CButtonUI* CButtonUI::Clone()
{
	return new CButtonUI(*this);
}

void CButtonUI::render()
{
	if (GetText() != L"")
	{
		CRenderManager::GetInst()->RenderText(GetText(),
			GetPos().x - GetScale().x,
			GetPos().y - GetScale().y + 2.f,
			GetPos().x + GetScale().x * 2.f,
			(GetPos().y + GetScale().y * 2.f) + 2.f,
			m_FontSize, GetTxtShadowColor());

		CRenderManager::GetInst()->RenderText(GetText(),
			GetPos().x - GetScale().x,
			GetPos().y - GetScale().y,
			GetPos().x + GetScale().x * 2.f,
			GetPos().y + GetScale().y * 2.f,
			m_FontSize, GetTextColor());
		CUI::render();
	}
	else
	{
		CUI::render();
	}
}
void CButtonUI::SetFontSize(int size)
{
	m_FontSize = size;
}
void CButtonUI::MouseOn()
{

}

void CButtonUI::MouseLbtnDown()
{
}

void CButtonUI::MouseLbtnUp()
{

}

void CButtonUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_pParam1, m_pParam2);
	}
}

//


void CButtonUI::SetClickedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
}
         