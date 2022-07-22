#include "framework.h"
#include "CHolliganHUD.h"
#include "CPlayer.h"
#include "CD2DImage.h"

CHolliganHUD::CHolliganHUD()
{
	/*m_pImg = nullptr;*/

	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"HolliganHUD", L"texture\\HUD\\Sis\\1.png");
	m_pImg->GetHeight();

	m_fptScale = { (float)m_pImg->GetWidth()*0.8f ,(float)m_pImg->GetHeight()*0.8f};
}

CHolliganHUD::~CHolliganHUD()
{
}

CHolliganHUD* CHolliganHUD::Clone()
{
	return new CHolliganHUD(*this);
}

void CHolliganHUD::update()
{
}

void CHolliganHUD::render()
{
	CRenderManager::GetInst()->RenderImage(m_pImg, m_fptPos.x - m_fptScale.x * 0.5, m_fptPos.y - m_fptScale.y * 0.5, m_fptPos.x + m_fptScale.x * 0.5, m_fptPos.y + m_fptScale.y * 0.5);
}
