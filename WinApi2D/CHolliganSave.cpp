#include "framework.h"
#include "CHolliganSave.h"
#include "CD2DImage.h"
#include "CPlayer.h"

CHolliganSave::CHolliganSave()
{

	m_pImg2 = CResourceManager::GetInst()->LoadD2DImage(L"HolliganOn", L"texture\\HUD\\Sis\\2.png");
	m_pImg2->GetHeight();
	m_fptScale = { (float)m_pImg2->GetWidth() * 0.8f ,(float)m_pImg2->GetHeight() * 0.8f };
	isGet = 0;
}

CHolliganSave::~CHolliganSave()
{
}

CHolliganSave* CHolliganSave::Clone()
{
	return new CHolliganSave(*this);
}

void CHolliganSave::update()
{
}

void CHolliganSave::render()
{
	if(CPlayer::holiganSave >= 1)
	CRenderManager::GetInst()->RenderImage(m_pImg2, m_fptPos0.x - m_fptScale.x * 0.5, m_fptPos0.y - m_fptScale.y * 0.5, m_fptPos0.x + m_fptScale.x * 0.5, m_fptPos0.y + m_fptScale.y * 0.5);
	if (CPlayer::holiganSave >= 2)
	CRenderManager::GetInst()->RenderImage(m_pImg2, m_fptPos1.x - m_fptScale.x * 0.5, m_fptPos1.y - m_fptScale.y * 0.5, m_fptPos1.x + m_fptScale.x * 0.5, m_fptPos1.y + m_fptScale.y * 0.5);
	if (CPlayer::holiganSave >= 3)
	CRenderManager::GetInst()->RenderImage(m_pImg2, m_fptPos2.x - m_fptScale.x * 0.5, m_fptPos2.y - m_fptScale.y * 0.5, m_fptPos2.x + m_fptScale.x * 0.5, m_fptPos2.y + m_fptScale.y * 0.5);
	if (CPlayer::holiganSave >= 4)
	CRenderManager::GetInst()->RenderImage(m_pImg2, m_fptPos3.x - m_fptScale.x * 0.5, m_fptPos3.y - m_fptScale.y * 0.5, m_fptPos3.x + m_fptScale.x * 0.5, m_fptPos3.y + m_fptScale.y * 0.5);
	if (CPlayer::holiganSave >= 5)
	CRenderManager::GetInst()->RenderImage(m_pImg2, m_fptPos4.x - m_fptScale.x * 0.5, m_fptPos4.y - m_fptScale.y * 0.5, m_fptPos4.x + m_fptScale.x * 0.5, m_fptPos4.y + m_fptScale.y * 0.5);

}
