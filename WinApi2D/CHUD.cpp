#include "framework.h"
#include "CHUD.h"
#include "CPlayer.h"
#include "CD2DImage.h"

CHUD::CHUD()
{
	/*m_pImg = nullptr;*/

	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Heart", L"texture\\HUD\\Heart\\3.png");
	m_pImg->GetHeight();
	m_fptScale = { (float)m_pImg->GetWidth(),(float)m_pImg->GetHeight()};
}

CHUD::~CHUD()
{
}

CHUD* CHUD::Clone()
{
	return new CHUD(*this);
}

void CHUD::update()
{
}

void CHUD::render()
{
	CRenderManager::GetInst()->RenderImage(m_pImg, m_fptPos.x - m_fptScale.x * 0.5, m_fptPos.y - m_fptScale.y * 0.5, m_fptPos.x + m_fptScale.x * 0.5, m_fptPos.y + m_fptScale.y * 0.5);
}
