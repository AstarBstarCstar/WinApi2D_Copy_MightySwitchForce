#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer* CPlayer::instance = nullptr;

CPlayer::CPlayer()
{
	CD2DImage* m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"PlayerImg", L"texture\\Animation_Player.bmp");
	SetName(L"Player");
	SetScale(fPoint(70.f, 70.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 40.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"LeftNone", m_pImg, fPoint(0.f, 0.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"RightNone", m_pImg, fPoint(0.f, 70.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"LeftMove", m_pImg, fPoint(0.f, 140.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"RightMove", m_pImg, fPoint(0.f, 210.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"LeftHit", m_pImg, fPoint(140.f, 0.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"RightHit", m_pImg, fPoint(140.f, 70.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
	GetAnimator()->Play(L"LeftNone");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"LeftMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
	pAni = GetAnimator()->FindAnimation(L"RightMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);

	CSoundManager::GetInst()->AddSound(L"FireSound", L"Sound\\PELLET_FIRE.wav",false,false);
}

CPlayer::~CPlayer()
{
	instance = nullptr;
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	fPoint pos = GetPos();

	if (Key(VK_LEFT))
	{
		pos.x -= m_fSpeed * fDT;
		GetAnimator()->Play(L"LeftMove");
	}
	if (Key(VK_RIGHT))
	{
		pos.x += m_fSpeed * fDT;
		GetAnimator()->Play(L"RightMove");
	}
	if (Key(VK_UP))
	{
		pos.y -= m_fSpeed * fDT;
	}
	if (Key(VK_DOWN))
	{
		pos.y += m_fSpeed * fDT;
	}

	SetPos(pos);

	if (KeyDown(VK_SPACE))
	{
		CreateMissile();
		CSoundManager::GetInst()->Play(L"FireSound");
		GetAnimator()->Play(L"LeftHit");
	}

	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::RegisterPlayer()
{
	instance = this;
}

CPlayer* CPlayer::GetPlayer()
{
	return instance;
}

void CPlayer::CreateMissile()
{
	fPoint fpMissilePos = GetPos();
	fpMissilePos.x += GetScale().x / 2.f;

	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fpMissilePos);
	pMissile->SetDir(fVec2(1, 0));
	pMissile->SetName(L"Missile_Player");

	CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
}














//#include "framework.h"
//#include "CPlayer.h"
//#include "CMissile.h"
//#include "CScene.h"
//#include "CTexture.h"
//#include "CCollider.h"
//#include "CAnimator.h"
//#include "CAnimation.h"
//
//CPlayer::CPlayer()
//{
//	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"PlayerImg", L"texture\\Animation\\Test.PNG");
//	SetName(L"PlayerImg");
//	SetScale(fPoint(70.f, 70.f));
//
//	CreateCollider();
//	GetCollider()->SetScale(fPoint(40.f, 40.f));
//	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));
//
//	CreateAnimator();
//	GetAnimator()->CreateAnimation(L"RightNone",		m_pImg, fPoint(0.f, 0.f),	fPoint(160.f, 286.f), fPoint(160.f, 0.f), 0.1f, 7);
//	//GetAnimator()->CreateAnimation(L"RightNone",	m_pImg, fPoint(0.f, 70.f),	fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.5f, 2);
//	//GetAnimator()->CreateAnimation(L"LeftMove",		m_pImg, fPoint(0.f, 140.f),	fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
//	//GetAnimator()->CreateAnimation(L"RightMove",	m_pImg, fPoint(0.f, 210.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
//	//GetAnimator()->CreateAnimation(L"LeftHit",		m_pImg, fPoint(140.f, 0.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
//	//GetAnimator()->CreateAnimation(L"RightHit",		m_pImg, fPoint(140.f, 70.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
//	GetAnimator()->Play(L"RightNone");
//
//	//CAnimation* pAni;
//	//pAni = GetAnimator()->FindAnimation(L"LeftMove");
//	//pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
//	//pAni = GetAnimator()->FindAnimation(L"RightMove");
//	//pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
//	CSoundManager::GetInst()->AddSound(L"fire", L"sound\\PELLET_FIRE.wav", false);
//	
//}
//
//CPlayer::~CPlayer()
//{
//
//}
//
//CPlayer* CPlayer::Clone()
//{
//	return new CPlayer(*this);
//}
//
//void CPlayer::update()
//{
//	fPoint pos = GetPos();
//
//	if (Key(VK_LEFT))
//	{
//		pos.x -= m_fVelocity * fDT;
//	}
//	if (Key(VK_RIGHT))
//	{
//		pos.x += m_fVelocity * fDT;
//	}				   
//	if (Key(VK_UP))	   
//	{				   
//		pos.y -= m_fVelocity * fDT;
//	}				   
//	if (Key(VK_DOWN))  
//	{				   
//		pos.y += m_fVelocity * fDT;
//	}
//
//	SetPos(pos);
//
//	if (KeyDown(VK_SPACE))
//	{
//		CreateMissile();
//		/*GetAnimator()->Play(L"LeftHit");*/
//		CSoundManager::GetInst()->Play(L"fire");
//	}
//
//	GetAnimator()->update();
//}
//
//void CPlayer::render()
//{
//	component_render();
//}
//
//void CPlayer::CreateMissile()
//{
// 	fPoint fpMissilePos = GetPos();
//	fpMissilePos.x += GetScale().x / 2.f;
//
//	// Misiile Object
//	CMissile* pMissile = new CMissile;
//	pMissile->SetPos(fpMissilePos);
//	pMissile->SetDir(fVec2(100, 0));
//
//
//
//
//	CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
//}
