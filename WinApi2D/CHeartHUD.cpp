#include "framework.h"
#include "CHeartHUD.h"
#include "CD2DImage.h"
#include "CPlayer.h"

CHeartHUD::CHeartHUD()
{

	m_pImg2 = CResourceManager::GetInst()->LoadD2DImage(L"FillHeart", L"texture\\HUD\\Heart\\4.png");
	m_pImg2->GetHeight();
	m_fptScale = { (float)m_pImg2->GetWidth() * 0.8f ,(float)m_pImg2->GetHeight() * 0.8f };
}

CHeartHUD::~CHeartHUD()
{
}

CHeartHUD* CHeartHUD::Clone()
{
	return new CHeartHUD(*this);
}

void CHeartHUD::update()
{
}

void CHeartHUD::render()
{
	if (CPlayer::m_fCurHp>=1)
		CRenderManager::GetInst()->RenderImage(m_pImg2, m_fptPos0.x - m_fptScale.x * 0.5, m_fptPos0.y - m_fptScale.y * 0.5, m_fptPos0.x + m_fptScale.x * 0.5, m_fptPos0.y + m_fptScale.y * 0.5);
	if (CPlayer::m_fCurHp >= 2)
		CRenderManager::GetInst()->RenderImage(m_pImg2, m_fptPos1.x - m_fptScale.x * 0.5, m_fptPos1.y - m_fptScale.y * 0.5, m_fptPos1.x + m_fptScale.x * 0.5, m_fptPos1.y + m_fptScale.y * 0.5);
	if (CPlayer::m_fCurHp >= 3)
		CRenderManager::GetInst()->RenderImage(m_pImg2, m_fptPos2.x - m_fptScale.x * 0.5, m_fptPos2.y - m_fptScale.y * 0.5, m_fptPos2.x + m_fptScale.x * 0.5, m_fptPos2.y + m_fptScale.y * 0.5);
}
