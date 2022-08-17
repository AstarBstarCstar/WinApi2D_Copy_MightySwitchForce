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
//#include "CD2DImage.h"
//#include "CAnimator.h"
//
//CHooligan::CHooligan()
//{
//	srand(time(NULL));
//	CD2DImage* m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Hooligan", L"texture\\Animation\\Hooligan\\Host1\\Idle\\Host1_144_240.png");
//	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\JUSTICESERVED1.wav", false, false);
//	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\JUSTICESERVED2.wav", false, false);
//	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\GOTCHA.wav", false, false);
//	CSoundManager::GetInst()->AddSound(L"Collect", L"Sound\\COLLECTHOOLIGAN.wav", false, false);
//	SetName(L"Hooligan");
//	SetScale(fPoint(144 * 0.7, 240 * 0.7));
//
//	CreateCollider();
//	GetCollider()->SetScale(fPoint(40.f, 120.f));
//
//	CreateAnimator();
//	GetAnimator()->CreateAnimation(L"IdleHool", m_pImg, fPoint(0, 0), fPoint(144.f, 240.f), fPoint(144.f, 0), fPoint(144.f, 240.f), 0, 0.1f, 20, true, false);
//	/*애니메이션이름,다렉이름,왼쪽위,*/
//}
//
//CHooligan::~CHooligan()
//{
//}
//
//CHooligan* CHooligan::Clone()
//{
//	return new CHooligan(*this);
//}
//
//void CHooligan::render()
//{
//	fPoint pos = GetPos();
//	fPoint scale = GetScale();
//	pos = CCameraManager::GetInst()->GetRenderPos(pos);
//
//	component_render();
//}
//
//void CHooligan::update()
//{
//	GetAnimator()->update();
//	GetAnimator()->Play(L"IdleHool");
//}
