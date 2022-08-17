#include "framework.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CPlayerSiren.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "SwitchBlock.h"
CPlayerSiren::CPlayerSiren()
{
	m_fvDir = fVec2(0, -5);
	CD2DImage* m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Siren", L"texture\\Animation\\PatriciaWagon\\Siren_512_512.png");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Siren", m_pImg, fPoint(0.f, 0.f), fPoint(512.f, 512.f), fPoint(512.f, 0.f), fPoint(512.f, 512.f), 0, 0.045f, 8, false, false);
	//CPlayerSiren* pPlayerSiren = new CPlayerSiren;
	//pPlayerSiren->SetPos(fPoint(3520, 2250));
	//AddObject(pPlayerSiren, GROUP_GAMEOBJ::SWITCHBLOCK);
		//pAni = GetAnimator()->FindAnimation(L"RightMove");
		//pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
}
CPlayerSiren::~CPlayerSiren()
{
}
void CPlayerSiren::SetDir(fVec2 vec)
{
	m_fvDir = vec.Normalize();
}

void CPlayerSiren::SetDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CPlayerSiren::update()
{
	CGameObject::Switching;
	if (CGameObject::Switching != true)
	{
		GetAnimator()->update();
		pAni = GetAnimator()->FindAnimation(L"Siren");
		DeleteObj(this);
		CCameraManager::GetInst()->ShakeP(0.05f);
	}
	else if (CGameObject::Switching == true)
	{
		GetAnimator()->update();
		GetAnimator()->Play(L"Siren");
		
		pAni = GetAnimator()->FindAnimation(L"Siren");


	}
}
CPlayerSiren* CPlayerSiren::Clone()
{
	return new CPlayerSiren(*this);
}
void CPlayerSiren::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(pos);
	component_render();
}