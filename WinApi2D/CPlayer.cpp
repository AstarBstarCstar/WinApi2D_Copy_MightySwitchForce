#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTile.h"

CPlayer* CPlayer::instance = nullptr;

CPlayer::CPlayer()
{
	SetScale(fPoint(100.f, 200.f));
	SetName(L"Player");
	CD2DImage* m_Idle = CResourceManager::GetInst()->LoadD2DImage(L"Idle", L"texture\\Animation\\PatriciaWagon\\Resting_Idle\\Resting_Idle_104_216.png");
	CD2DImage* m_Run = CResourceManager::GetInst()->LoadD2DImage(L"Run", L"texture\\Animation\\PatriciaWagon\\Run\\Run_196_204.png");
	CD2DImage* m_Fire = CResourceManager::GetInst()->LoadD2DImage(L"Fire", L"texture\\Animation\\PatriciaWagon\\Fire\\Fire_172_212.png");
	

	CreateCollider();
	GetCollider()->SetScale(fPoint(70.f, 100.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));//TODO:

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Idle", m_Idle, fPoint(0.f, 0.f), fPoint(104.f, 216.f), fPoint(104.f, 0.f), 0.1f, 7);
	GetAnimator()->Play(L"Idle");
	GetAnimator()->CreateAnimation(L"Run", m_Run, fPoint(0.f, 0.f), fPoint(196.f, 204.f), fPoint(196.f, 0.f), 0.1f, 12);
	GetAnimator()->CreateAnimation(L"R_Run", m_Run, fPoint(0.f, 0.f), fPoint(196.f, 204.f), fPoint(196.f, 0.f), 0.1f, 12, true);
	GetAnimator()->CreateAnimation(L"Fire", m_Fire, fPoint(0.f, 0.f), fPoint(172.f, 212.f), fPoint(172.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"R_Fire", m_Fire, fPoint(0.f, 0.f), fPoint(172.f, 212.f), fPoint(172.f, 0.f), 0.1f, 5,true);

	//CAnimation* pAni;
	////pAni = GetAnimator()->FindAnimation(L"LeftMove");
	//pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
	////pAni = GetAnimator()->FindAnimation(L"RightMove");
	//pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);

	CSoundManager::GetInst()->AddSound(L"FireSound", L"sound\\PELLET_FIRE.wav",false,false);
	CSoundManager::GetInst()->AddSound(L"Switch", L"sound\\Switch.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"SLAM", L"sound\\Flip.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Camera", L"sound\\SFX_CAMERA.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"CameraRelease", L"sound\\SFX_CAMERA_RELEASE.wav", false, false);
	isLeft = false;
	CameraLock = false;
	m_fVelocity = 0.f;
	m_fMaxVelocity = MAX_SPEED;
	m_gravity = GRAVITY;
	m_State = CharacterState::IDLE;
}

CPlayer::~CPlayer()
{
	instance = nullptr;
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
			fVec2 vPos = GetPos();
		CTile* pTile = (CTile*)pOtherObj;
		GROUP_TILE Type = pTile->GetGroup();

	if (pOtherObj->GetName() == L"Tile")
	{

		switch (Type)
		{
		case GROUP_TILE::GROUND:
		{
			if (abs(GetCollider()->GetFinalPos().y - pOther->GetFinalPos().y) + 2.f >= GetCollider()->GetScale().y / 2.f + pOther->GetScale().y / 2.f)
			{
				++m_Ground;
			}
			else
			{
				if (GetCollider()->GetFinalPos().x < pOther->GetFinalPos().x)
				{
					vPos.x -= 2.f;
				}
				else if (GetCollider()->GetFinalPos().x > pOther->GetFinalPos().x)
				{
					vPos.x += 2.f;
				}
				++m_Ground;
			}
			
				break;
		}
		case GROUP_TILE::PLATFORM:
		{	
			if (abs(GetCollider()->GetFinalPos().y - pOther->GetFinalPos().y) + 2.f >= GetCollider()->GetScale().y / 2.f + pOther->GetScale().y / 2.f)
			{
				++m_Plat;
			}
		}
		case GROUP_TILE::SPIKE:
		{
			break;
		}
		}
		SetPos(vPos);
	}
}

void CPlayer::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	fVec2 vPos = GetPos();
	CTile* pTile = (CTile*)pOtherObj;
	GROUP_TILE Type = pTile->GetGroup();

	if (pOtherObj->GetName() == L"Tile")
	{
		switch (Type)
		{
		case GROUP_TILE::GROUND:
		{
				if (GetCollider()->GetFinalPos().y < pOther->GetFinalPos().y)
				{
					vPos.y -= 2.f;
				}
				else if (GetCollider()->GetFinalPos().y > pOther->GetFinalPos().y)
				{
					vPos.y += 2.f;
				}

			break;
		}
		case GROUP_TILE::PLATFORM:
		{
			if (GetCollider()->GetFinalPos().y < pOther->GetFinalPos().y)
			{
				vPos.y -= 2.f;
			}
			break;
		}
		case GROUP_TILE::SPIKE:
		{
			break;
		}
		}
	}
	SetPos(vPos);

}

void CPlayer::OnCollisionExit(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	fVec2 vPos = GetPos();
	CTile* pTile = (CTile*)pOtherObj;
	GROUP_TILE Type = pTile->GetGroup();
	if (pOtherObj->GetName() == L"Tile")
	{

		switch (Type)
		{
		case GROUP_TILE::GROUND:
		{
			--m_Ground;
			break;
		}
		case GROUP_TILE::PLATFORM:
		{
			--m_Plat;
			break;
		}
		case GROUP_TILE::SPIKE:
		{
			break;
		}
		}
	}
}

/*
TODO:
����->   Z
����->   X
����ġ->C
ī�޶�->Space
UP DOWN Ű ����*/
void CPlayer::update()
{
	fPoint pos = GetPos();
	if (m_Ground > 0)
	{
		m_gravity = 0.f;
		m_Upper = 0.f;
	}
	else
	{
		m_gravity = GRAVITY;
		pos.y += GRAVITY * fDT;
	}

	if (m_State == CharacterState::JUMP)
	{
		m_Upper -= (700 * fDT);
		pos.y -= m_Upper * fDT;
	}

	if (Key(VK_LEFT))
	{
		pos.x -= m_fSpeed * fDT;
		isLeft = true;
		GetAnimator()->Play(L"R_Run");
	}
	if (Key(VK_RIGHT))
	{
		pos.x += m_fSpeed * fDT;
		isLeft = false;
		GetAnimator()->Play(L"Run");
	}
	if (Key(VK_UP))
	{
		pos.y -= m_fSpeed * fDT;
	}
	if (Key(VK_DOWN))
	{
		pos.y += m_fSpeed * fDT;
	}
	if (Key('X'))
	{
		m_Upper = UPPER;
		pos.y -= 20.f;
	}
	if (KeyDown('Z'))
	{
		CreateMissile();
		CSoundManager::GetInst()->Play(L"FireSound");
		if (isLeft == 1)
		{
			GetAnimator()->Play(L"R_Fire");
			if(KeyUp('Z'))
				GetAnimator()->Play(L"Idle");
		}
		else if (isLeft == 0)
		{
			GetAnimator()->Play(L"Fire");
			if (KeyUp('Z'))
				GetAnimator()->Play(L"Idle");
			
		}
	}
	if (KeyDown('C'))
	{
		CSoundManager::GetInst()->Play(L"Switch");
		CSoundManager::GetInst()->Play(L"Flip");
	}
	if (Key(VK_SPACE))
	{
		//CameraRelease();
	}
	SetPos(pos);
	GetAnimator()->update();
}
void CPlayer::render()
{
	component_render();
}

CharacterState CPlayer::GetState()
{
	return CharacterState();
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
	if (isLeft == true)
	{
		pMissile->SetDir(fVec2(-1, 0));
		pMissile->SetName(L"Missile_Player");
		CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
	}
	else
	{
		pMissile->SetDir(fVec2(1, 0));
		pMissile->SetName(L"Missile_Player");
		CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
	}
}

void CPlayer::Jump()
{

}

void CPlayer::CameraRelease()
{
	CameraLock = true;
	bool CameraLimit = false;
	if (Count == 0)
	{
		CSoundManager::GetInst()->Play(L"Camera");
		Count += 1;
	}

	/*����Ű�� ī�޶� �̵� �����¿�*/

	if (Key(VK_UP))
	{
		CCameraManager::GetInst()->Scroll(fVec2(0, -1), 600);
	}
	if (Key(VK_DOWN))
	{
		/*TODO:ī�޶� �Ʒ��� ������������*/
		CCameraManager::GetInst()->Scroll(fVec2(0, 1), 600);
	}
	if (Key(VK_LEFT))
	{
		/*TODO:ī�޶� �������� ������������*/
		CCameraManager::GetInst()->Scroll(fVec2(-1, 0), 600);
	}
	if (Key(VK_RIGHT))
	{
		/*TODO:ī�޶� ���������� ������������*/
		CCameraManager::GetInst()->Scroll(fVec2(1, 0), 600);
	}
if (KeyUp(VK_SPACE))
{
	CSoundManager::GetInst()->Play(L"CameraRelease");
	CameraLock = false;
	Count = 0;
	return;
}
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


//void CPlayer::OnCollisionEnter(CCollider* pOther)
//{
//	CGameObject* pOtherObj = pOther->GetObj();
//	fVec2 vPos = GetPos();
//	CTile* pTile = (CTile*)pOtherObj;
//	GROUP_TILE Type = pTile->GetGroup();
//
//	if (pOtherObj->GetName() == L"Tile")
//	{
//
//		switch (Type)
//		{
//		case GROUP_TILE::GROUND:
//		{
//			if (abs(GetCollider()->GetFinalPos().y - pOther->GetFinalPos().y) + 2.f
//				>= GetCollider()->GetScale().y / 2.f + pOther->GetScale().y / 2.f)
//			{
//				++m_Ground;
//			}
//			else
//			{
//				if (GetCollider()->GetFinalPos().x < pOther->GetFinalPos().x)
//				{
//					vPos.x -= 2.f;
//				}
//				else if (GetCollider()->GetFinalPos().x > pOther->GetFinalPos().x)
//				{
//					vPos.x += 2.f;
//				}
//				++m_Ground;
//			}
//
//			break;
//		}
//		case GROUP_TILE::PLATFORM:
//		{
//			++m_Ground;
//			break;
//		}
//		case GROUP_TILE::SPIKE:
//		{break; }
//		}
//		SetPos(vPos);
//	}
//}
//
//void CPlayer::OnCollision(CCollider* pOther)
//{
//	CGameObject* pOtherObj = pOther->GetObj();
//	fVec2 vPos = GetPos();
//	CTile* pTile = (CTile*)pOtherObj;
//	GROUP_TILE Type = pTile->GetGroup();
//
//	if (pOtherObj->GetName() == L"Tile")
//	{
//		switch (Type)
//		{
//		case GROUP_TILE::GROUND:
//		{
//			int yCol1 = abs((int)(GetCollider()->GetFinalPos().y - pOther->GetFinalPos().y));
//			int yCol2 = (int)(GetCollider()->GetScale().y / 2.f + pOther->GetScale().y / 2.f);
//			int ysum = abs(yCol1 - yCol2);
//			if (1 < ysum)
//				vPos.y -= 1;
//			break;
//		}
//		case GROUP_TILE::PLATFORM:
//		{
//			break;
//		}
//		case GROUP_TILE::SPIKE:
//		{
//			break;
//		}
//		}
//	}
//	SetPos(vPos);
//}
//
//void CPlayer::OnCollisionExit(CCollider* pOther)
//{
//	CGameObject* pOtherObj = pOther->GetObj();
//	fVec2 vPos = GetPos();
//	CTile* pTile = (CTile*)pOtherObj;
//	GROUP_TILE Type = pTile->GetGroup();
//	if (pOtherObj->GetName() == L"Tile")
//	{
//
//		switch (Type)
//		{
//		case GROUP_TILE::GROUND:
//		{
//			--m_Ground;
//			break;
//		}
//		case GROUP_TILE::PLATFORM:
//		{
//			--m_Ground;
//			break;
//		}
//		case GROUP_TILE::SPIKE:
//		{
//			break;
//		}
//		}
//	}
//}