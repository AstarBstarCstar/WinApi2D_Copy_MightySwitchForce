#include "framework.h"
#include "CHolliganHUD.h"
#include "CPlayer.h"
#include "CD2DImage.h"

CHolliganHUD::CHolliganHUD()
{

	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"HolliganHUD", L"texture\\HUD\\Sis\\1.png");
	m_pImg2 = CResourceManager::GetInst()->LoadD2DImage(L"EXIT", L"texture\\HUD\\EXIT.png");
	m_pImg->GetHeight();

	m_fptScale = { (float)m_pImg->GetWidth()*0.8f ,(float)m_pImg->GetHeight()*0.8f};
	on = true;
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
	if (CGameObject::holiganSave >= 5)
	{
		timer += fDT;
		if (on)
		{
			alpha = 1.f;
			if (timer >= 0.5f)
			{
				on = false;
				off = true;
				timer = 0.f;
			}
		}
		if (off)
		{
			alpha = 0.f;
			if (timer >= 0.5f)
			{
				on = true;
				off = false;
				timer = 0.f;
			}
		}
	}
}

void CHolliganHUD::render()
{
	CRenderManager::GetInst()->RenderImage(m_pImg2, m_fptPos.x - m_fptScale.x * 0.6, m_fptPos.y+50.f - m_fptScale.y * 0.6, m_fptPos.x + m_fptScale.x * 0.6, m_fptPos.y+50.f + m_fptScale.y * 0.6, alpha);
	CRenderManager::GetInst()->RenderImage(m_pImg, m_fptPos.x - m_fptScale.x * 0.5, m_fptPos.y - m_fptScale.y * 0.5, m_fptPos.x + m_fptScale.x * 0.5, m_fptPos.y + m_fptScale.y * 0.5);
}
