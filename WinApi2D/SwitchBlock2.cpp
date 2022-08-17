#include "framework.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "SwitchBlock2.h"
#include "CPlayer.h"

SwitchBlock2::SwitchBlock2()
{
	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"SWBlock", L"texture\\Object\\SwitchBlock\\SwitchBlock.png");
	//CSoundManager::GetInst()->AddSound(L"Switching", L"sound\\Switch.wav", false, false);
	//CSoundManager::GetInst()->AddSound(L"Flip", L"sound\\Flip.wav", false, false);
	SetScale(fPoint(192, 192));
	SetName(L"SWB");

	CreateCollider();
	GetCollider()->SetScale(fPoint(190.f, 190.f));

	m_bSW = false;
	fCurTime = 0.f;
	m_eChanger = BLOCK_CHANGE::CLOSE;
	fDuration = 0.5f;
}
SwitchBlock2::~SwitchBlock2()
{
}

SwitchBlock2* SwitchBlock2::Clone()
{
	return new SwitchBlock2(*this);
}

void SwitchBlock2::update()
{
	if (KeyDown('C'))
	{
		//CSoundManager::GetInst()->Play(L"Switching");
		//CSoundManager::GetInst()->Play(L"Flip");
		if (m_bSW==true)//활성화 된 스위치블럭 상태에서 c 누를시
		{
			m_eChanger = BLOCK_CHANGE::CLOSE;
			fDuration = 0.5;
			fCurTime = 0.f;
			m_bSW = false;
			SetName(L"SWB");
		}
		else//활성화 안 된 스위치블럭 상태에서 c 누를시
		{
			m_eChanger = BLOCK_CHANGE::OPEN;
			fDuration = 0.5;
			fCurTime = 0.f;
			m_bSW = true;
			SetName(L"Switching");
			CGameObject::Switching = true;
		}
	}
}

void SwitchBlock2::render()
{
	CGameObject::debug_render();//디버그용 정보 표시
	fCurTime += (float)fDT;

	float fRatio = fCurTime / fDuration;
	float fAlpha = 1;
	if (BLOCK_CHANGE::CLOSE == m_eChanger)
	{
		fAlpha = 1.f - fRatio;
		if (fAlpha <= 0.5f)
		{
			fAlpha = 0.5f;
		}
	}
	else if (BLOCK_CHANGE::OPEN == m_eChanger)
	{
		fAlpha = 0.5f + fRatio;
		if (fAlpha >= 1.f)
		{
			SetName(L"SwitchBlock");
			CGameObject::Switching = false;
		}
	}

	fPoint scale = GetScale();
	fPoint pos = CCameraManager::GetInst()->GetRenderPos(GetPos());
	CRenderManager::GetInst()->RenderImage(m_pImg, pos.x - scale.x * 0.5, pos.y - scale.y * 0.5, pos.x + scale.x * 0.5, pos.y + scale.y * 0.5, fAlpha);//그냥 값넣으면 원래 크기의 두배를 렌더 하지 않아?

	component_render();
}

