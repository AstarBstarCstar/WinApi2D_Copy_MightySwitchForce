
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
	SetName(L"Player");
	CD2DImage* m_Idle = CResourceManager::GetInst()->LoadD2DImage(L"Idle", L"texture\\Animation\\PatriciaWagon\\Resting_Idle\\Resting_Idle_124_224.png");
	CD2DImage* m_Run = CResourceManager::GetInst()->LoadD2DImage(L"Run", L"texture\\Animation\\PatriciaWagon\\Run\\Run_200_220.png");
	CD2DImage* m_Fire = CResourceManager::GetInst()->LoadD2DImage(L"Fire", L"texture\\Animation\\PatriciaWagon\\Fire\\Fire_192_212.png");
	CD2DImage* m_JumpFire = CResourceManager::GetInst()->LoadD2DImage(L"FiretoIdle", L"texture\\Animation\\PatriciaWagon\\Jump_Fire\\JumpFire_192_228.png");
	CD2DImage* m_RunFire = CResourceManager::GetInst()->LoadD2DImage(L"JumpFire", L"texture\\Animation\\PatriciaWagon\\Run_Fire\\RunFire_232_224.png");
	CD2DImage* m_FiretoIdle = CResourceManager::GetInst()->LoadD2DImage(L"RunFire", L"texture\\Animation\\PatriciaWagon\\Fire_Idle_to_Rest\\Fire_Idle_to_Rest_150_220.png");
	CD2DImage* m_JumpRise = CResourceManager::GetInst()->LoadD2DImage(L"JumpRise", L"texture\\Animation\\PatriciaWagon\\Jump_Rise\\Jump_Rise_144_228.png");
	CD2DImage* m_JumpFall = CResourceManager::GetInst()->LoadD2DImage(L"JumpFall", L"texture\\Animation\\PatriciaWagon\\Jump_Fall\\Jump_Fall_152_220.png");
	CD2DImage* m_Die = CResourceManager::GetInst()->LoadD2DImage(L"Die", L"texture\\Animation\\PatriciaWagon\\Die\\Die_200_275.png");//Hit 같이
	CD2DImage* m_Sweat = CResourceManager::GetInst()->LoadD2DImage(L"Sweat", L"texture\\Animation\\PatriciaWagon\\Sweat\\Sweat_260_236.png");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Idle", m_Idle, fPoint(0.f, 0.f), fPoint(124.f, 224.f), fPoint(124.f, 0.f), fPoint(124.f, 224.f), 0, 0.065f, 7, true, false);
	GetAnimator()->CreateAnimation(L"R_Idle", m_Idle, fPoint(0.f, 0.f), fPoint(124.f, 224.f), fPoint(124.f, 0.f), fPoint(124.f, 224.f), 0, 0.065f, 7, true, true);
	GetAnimator()->CreateAnimation(L"Run", m_Run, fPoint(0.f, 0.f), fPoint(200.f, 220.f), fPoint(200.f, 0.f), fPoint(200.f, 220.f), 0, 0.065f, 12, true, false);
	GetAnimator()->CreateAnimation(L"R_Run", m_Run, fPoint(0.f, 0.f), fPoint(200.f, 220.f), fPoint(200.f, 0.f), fPoint(200.f, 220.f), 0, 0.065f, 12, true, true);
	GetAnimator()->CreateAnimation(L"Fire", m_Fire, fPoint(0.f, 0.f), fPoint(192.f, 212.f), fPoint(192.f, 0.f), fPoint(192.f, 212.f), 0, 0.065f, 5, true, false);
	GetAnimator()->CreateAnimation(L"R_Fire", m_Fire, fPoint(0.f, 0.f), fPoint(192.f, 212.f), fPoint(192.f, 0.f), fPoint(192.f, 212.f), 0, 0.065f, 5, true, true);
	GetAnimator()->CreateAnimation(L"RunFire", m_RunFire, fPoint(0.f, 0.f), fPoint(232.f, 224.f), fPoint(232.f, 0.f), fPoint(232.f, 224.f), 0, 0.065f, 12, true, false);
	GetAnimator()->CreateAnimation(L"R_RunFire", m_RunFire, fPoint(0.f, 0.f), fPoint(232.f, 224.f), fPoint(232.f, 0.f), fPoint(232.f, 224.f), 0, 0.065f, 12, true, true);
	GetAnimator()->CreateAnimation(L"JumpFire", m_JumpFire, fPoint(0.f, 0.f), fPoint(192.f, 228.f), fPoint(192.f, 0.f), fPoint(192.f, 228.f), 0, 0.065f, 8, true, false);
	GetAnimator()->CreateAnimation(L"R_JumpFire", m_JumpFire, fPoint(0.f, 0.f), fPoint(192.f, 228.f), fPoint(192.f, 0.f), fPoint(192.f, 228.f), 0, 0.065f, 8, true, true);
	GetAnimator()->CreateAnimation(L"FiretoIdle", m_FiretoIdle, fPoint(0.f, 0.f), fPoint(150.f, 220.f), fPoint(150.f, 0.f), fPoint(150.f, 220.f), 0, 0.065f, 4, true, false);
	GetAnimator()->CreateAnimation(L"R_FiretoIdle", m_FiretoIdle, fPoint(0.f, 0.f), fPoint(150.f, 220.f), fPoint(150.f, 0.f), fPoint(150.f, 220.f), 0, 0.065f, 4, false, true);
	GetAnimator()->CreateAnimation(L"JumpRise", m_JumpRise, fPoint(0.f, 0.f), fPoint(144.f, 228.f), fPoint(144.f, 0.f), fPoint(144.f, 228.f), 0, 0.110f, 4, true, false);
	GetAnimator()->CreateAnimation(L"R_JumpRise", m_JumpRise, fPoint(0.f, 0.f), fPoint(144.f, 228.f), fPoint(144.f, 0.f), fPoint(144.f, 228.f), 0, 0.110f, 4, true, true);
	GetAnimator()->CreateAnimation(L"JumpFall", m_JumpFall, fPoint(0.f, 0.f), fPoint(152.f, 220.f), fPoint(152.f, 0.f), fPoint(152.f, 220.f), 0, 0.110f, 4, true, false);
	GetAnimator()->CreateAnimation(L"R_JumpFall", m_JumpFall, fPoint(0.f, 0.f), fPoint(152.f, 216.f), fPoint(152.f, 0.f), fPoint(152.f, 220.f), 0, 0.110f, 4, false, true);
	GetAnimator()->CreateAnimation(L"Die", m_Die, fPoint(0.f, 0.f), fPoint(220.f, 275.f), fPoint(220.f, 0.f), fPoint(220.f, 275.f), 0, 0.065f, 72, true, false);
	GetAnimator()->CreateAnimation(L"R_Die", m_Die, fPoint(0.f, 0.f), fPoint(220.f, 275.f), fPoint(220.f, 0.f), fPoint(220.f, 275.f), 0, 0.065f, 72, false, true);
	GetAnimator()->CreateAnimation(L"Sweat", m_Sweat, fPoint(0.f, 0.f), fPoint(260.f, 236.f), fPoint(260.f, 0.f), fPoint(260.f, 236.f), 0, 0.065f, 13, true, false);
	GetAnimator()->CreateAnimation(L"R_Sweat", m_Sweat, fPoint(0.f, 0.f), fPoint(260.f, 236.f), fPoint(260.f, 0.f), fPoint(260.f, 236.f), 0, 0.065f, 13, false, true);
	GetAnimator()->CreateAnimation(L"Hit", m_Die, fPoint(0.f, 0.f), fPoint(220.f, 275.f), fPoint(220.f, 0.f), fPoint(220.f, 275.f), 0, 0.065f, 4, true, false);
	GetAnimator()->CreateAnimation(L"R_Hit", m_Die, fPoint(0.f, 0.f), fPoint(220.f, 275.f), fPoint(220.f, 0.f), fPoint(220.f, 275.f), 0, 0.065f, 4, true, true);
	GetAnimator()->Play(L"Idle");

	//CAnimation* pAni;
	//pAni = GetAnimator()->FindAnimation(L"JumpRise");
	//for (int i = 0; i < 6; ++i)
	//{
	//	pAni->GetFrame(i);
	//}

	CSoundManager::GetInst()->AddSound(L"FireSound", L"sound\\PELLET_FIRE.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Switch", L"sound\\Switch.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"SLAM", L"sound\\Flip.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Camera", L"sound\\SFX_CAMERA.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"CameraRelease", L"sound\\SFX_CAMERA_RELEASE.wav", false, false);

	CreateCollider();
	GetCollider()->SetScale(fPoint(55.f, 160.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 25.f));

	isLeft = false;
	CameraLock = false;
	m_bJustHit = false;
	m_bGrounding = true;
	Run = false;
	m_bAttacking = false;

	m_fCurDir = { 1.f, 1.f };
	m_fPrevDir = {};

	m_fAccelGravity = 0.f;
	m_fSpeed = MAX_SPEED;
	m_gravity = GRAVITY;
	m_Upper = UPPER;
	m_Spike = 0;
	m_Wall = 0;
	m_State = PLAYER_STATE::IDLE;
}

CPlayer::~CPlayer()
{
}

/*
TODO:
공격->   Z
점프->   X
스위치->C
카메라->Space
UP DOWN 키 없음*/
void CPlayer::update()
{
	CCameraManager::GetInst()->SetLookAt(GetPos());
	update_Animation();
	update_State();
	update_Move();

	m_PrevState = m_State;
	m_fPrevDir = m_fCurDir;
	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::update_State()
{
	if (m_fSpeed <= 0 && !m_bAttacking)
	{
		if (m_State != PLAYER_STATE::JUMPRISE)
			m_State = PLAYER_STATE::IDLE;
	}

	if (PLAYER_STATE::JUMPEND == m_State)
	{
		if (Key(VK_LEFT) || Key(VK_RIGHT))
		{
			m_State = PLAYER_STATE::MOVE;
		}
	}
	if (Key(VK_LEFT) && !m_bAttacking)
	{
		if (PLAYER_STATE::JUMPRISE != m_State)
		{
			m_State = PLAYER_STATE::MOVE;
		}
	}
	if (Key(VK_RIGHT) && !m_bAttacking)
	{
		if (PLAYER_STATE::JUMPRISE != m_State)
		{
			m_State = PLAYER_STATE::MOVE;
		}
	}

	if (KeyDown('X') && m_bGrounding && !m_bAttacking)
	{
		m_State = PLAYER_STATE::JUMPRISE;
	}
	if (!m_bAttacking && m_fAccelGravity > 200)
	{
		m_State = PLAYER_STATE::JUMPFALL;
	}
	if (KeyDown('Z') && !m_bGrounding)
	{
		CreateMissile();
		m_State = PLAYER_STATE::JUMPFIRE;
		m_bAttacking = true;
	}
	if (KeyDown('Z') && m_bGrounding && m_fSpeed <= 0)
	{
		CreateMissile();
		m_State = PLAYER_STATE::ATTACK;
		m_bAttacking = true;
	}
	if (Key(VK_LEFT) && KeyDown('Z') && m_bGrounding && m_fSpeed > 500)
	{
		if (PLAYER_STATE::JUMPRISE != m_State)
		{
			CreateMissile();
			m_State = PLAYER_STATE::MOVEFIRE;
			m_bAttacking = true;
		}
	}
	if (Key(VK_RIGHT) && KeyDown('Z') && m_bGrounding && m_fSpeed >= 500)
	{
		if (PLAYER_STATE::JUMPRISE != m_State)
		{
			CreateMissile();
			m_State = PLAYER_STATE::MOVEFIRE;
			m_bAttacking = true;
		}
	}

}
void CPlayer::update_Move()
{
	if (Key(VK_LEFT))
	{
		m_fvCurDir.x = -1;
		m_fSpeed = 600.f;
	}
	if (KeyUp(VK_LEFT))
	{
		m_fSpeed = 0.f;
	}

	if (Key(VK_RIGHT))
	{
		m_fvCurDir.x = 1;
		m_fSpeed = 600.f;
	}
	if (KeyUp(VK_RIGHT))
	{
		m_fSpeed = 0.f;
	}

	if (m_State == PLAYER_STATE::JUMPRISE && m_bGrounding)
	{
		Jump();
	}

	fPoint fptPos = GetPos();
	fptPos.x += m_fvCurDir.x * m_fSpeed * fDT;
	fptPos.y += m_fAccelGravity * fDT;
	SetPos(fptPos);
	m_fAccelGravity += GRAVITY * fDT;
	if (m_fAccelGravity >= 7000.f)
		m_fAccelGravity = 7000.f;

}
void CPlayer::update_Animation()
{
	if (m_PrevState == m_State && m_fvPrevDir == m_fvCurDir)
	{
		return;
	}
	switch (m_State)
	{
	case PLAYER_STATE::IDLE:
	{
		static float fIdleTime = 0.f;
		fIdleTime += fDT;
		if (-1 == m_fvCurDir.x && fIdleTime < 3)
		{
			GetAnimator()->Play(L"R_Idle");
		}
		else if (1 == m_fvCurDir.x && fIdleTime < 3)
		{
			GetAnimator()->Play(L"Idle");
		}
		//else if (-1 == m_fvCurDir.x && fIdleTime >= 3)
		//{
		//	GetAnimator()->Play(L"R_Sweat");
		//	fIdleTime = 0.f;
		//}
		//else if (1 == m_fvCurDir.x && fIdleTime >= 3)
		//{
		//	GetAnimator()->Play(L"Sweat");
		//	fIdleTime = 0.f;
		//}
		break;
	}

	case PLAYER_STATE::MOVE:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"R_Run");
		}
		else
		{
			GetAnimator()->Play(L"Run");
		}
		break;
	}

	case PLAYER_STATE::JUMPRISE:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"R_JumpRise");
		}
		else
		{
			GetAnimator()->Play(L"JumpRise");
		}
		break;
	}
	case PLAYER_STATE::JUMPFALL:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"R_JumpFall");
		}
		else
		{
			GetAnimator()->Play(L"JumpFall");
		}
		break;
	}
	case PLAYER_STATE::JUMPEND:
	{
		m_State = PLAYER_STATE::IDLE;
		break;
	}
	case PLAYER_STATE::ATTACK:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"R_Fire", true);
		}
		else
		{
			GetAnimator()->Play(L"Fire", true);
		}
		static float fTime = 0.f;
		fTime += fDT;
		if (0.325 <= fTime)
		{
			m_bAttacking = false;
			fTime = 0.f;
		}

		break;
	}
	case PLAYER_STATE::MOVEFIRE:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"R_RunFire", true);
		}
		else
		{
			GetAnimator()->Play(L"RunFire", true);
		}
		static float fTime = 0.f;
		fTime += fDT;
		if (0.325 <= fTime)
		{
			m_bAttacking = false;
			fTime = 0.f;
		}
		break;
	}
	case PLAYER_STATE::JUMPFIRE:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"R_JumpFire", true);
		}
		else
		{
			GetAnimator()->Play(L"JumpFire", true);
		}
		static float fTime = 0.f;
		fTime += fDT;
		if (0.325 <= fTime)
		{
			m_bAttacking = false;
			fTime = 0.f;
		}
		break;
	}
	}
}

void CPlayer::CreateMissile()
{
	fPoint fpMissilePos = GetPos();
	fpMissilePos.x += GetScale().x / 2.f;

	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fpMissilePos);
	if (m_fvCurDir.x == -1)
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
	m_bGrounding = false;
	m_fAccelGravity += m_Upper;
}

void CPlayer::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	CTile* pTile = (CTile*)pOtherObj;
	GROUP_TILE Type = pTile->GetGroup();
	if (pOtherObj->GetName() == L"Tile")
	{
		switch (Type)
		{
		case GROUP_TILE::GROUND:
		{
			if (GetCollider()->GetBorderPos().top < pOther->GetBorderPos().top
				&& GetCollider()->GetBorderPos().bottom >= pOther->GetBorderPos().top)
			{
				if (m_State == PLAYER_STATE::JUMPRISE)
				{
					m_State = PLAYER_STATE::JUMPEND;
				}
			}
			break;
		}
		case GROUP_TILE::PLATFORM:
		{
			if (GetCollider()->GetBorderPos().top < pOther->GetBorderPos().top
				&& GetCollider()->GetBorderPos().bottom >= pOther->GetBorderPos().top)
			{
				if (m_State == PLAYER_STATE::JUMPRISE)
				{
					//애니메이터점프 왼오른쪽구현
					m_State = PLAYER_STATE::JUMPEND;
				}
			}
			break;
		}
		}
	}
}

void CPlayer::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	CTile* pTile = (CTile*)pOtherObj;
	GROUP_TILE Type = pTile->GetGroup();
	if (pOtherObj->GetName() == L"Tile")
	{
		switch (Type)
		{
		case GROUP_TILE::GROUND:
		{
			LONG yDiff = 0;
			LONG xDiff = 0;
			if (pOther->GetBorderPos().left > GetCollider()->GetBorderPos().left)
			{
				xDiff = (GetCollider()->GetBorderPos().right - pOther->GetBorderPos().left);
			}
			else if (pOther->GetBorderPos().right < GetCollider()->GetBorderPos().right)
			{
				xDiff = (pOther->GetBorderPos().right - GetCollider()->GetBorderPos().left);
			}
			else
				xDiff = (GetCollider()->GetBorderPos().right - GetCollider()->GetBorderPos().left);


			if (m_fvCurDir.x < 0.f)
			{
				if (pOther->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
					&& pOther->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
				{
					yDiff = (GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);

					if (yDiff > xDiff && GetCollider()->GetBorderPos().right > pOther->GetBorderPos().right)
					{
						fPoint fptPos = GetPos();
						fptPos.x += (float)(pOther->GetBorderPos().right - GetCollider()->GetBorderPos().left);
						SetPos(fptPos);
					}
				}
			}
			if (m_fvCurDir.x > 0.f)
			{
				if (pOther->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
					&& pOther->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
				{
					yDiff = (GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);

					if (yDiff > xDiff && GetCollider()->GetBorderPos().left < pOther->GetBorderPos().left
						&& GetCollider()->GetBorderPos().right > pOther->GetBorderPos().left)
					{
						fPoint fptPos = GetPos();
						fptPos.x -= (float)(GetCollider()->GetBorderPos().right - pOther->GetBorderPos().left);
						SetPos(fptPos);
					}
				}
			}


			if (GetCollider()->GetBorderPos().bottom > pOther->GetBorderPos().bottom &&
				GetCollider()->GetBorderPos().top <= pOther->GetBorderPos().bottom)
			{
				yDiff = (pOther->GetBorderPos().bottom - GetCollider()->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					fPoint fptPos = GetPos();
					fptPos.y += (float)(pOther->GetBorderPos().bottom - GetCollider()->GetBorderPos().top);
					SetPos(fptPos);
				}

			}
			if (GetCollider()->GetBorderPos().top < pOther->GetBorderPos().top
				&& GetCollider()->GetBorderPos().bottom >= pOther->GetBorderPos().top)
			{
				yDiff = (GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					fPoint fptPos = GetPos();
					fptPos.y -= (float)(GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);
					SetPos(fptPos);

					m_bGrounding = true;
					m_fAccelGravity = 0.f;
				}
			}
			break;

		}
		case GROUP_TILE::WALL:
		{
		}
		case GROUP_TILE::PLATFORM:
		{
			LONG yDiff = 0;
			LONG xDiff = 0;

			if (pOther->GetBorderPos().left > GetCollider()->GetBorderPos().left)
			{
				xDiff = (GetCollider()->GetBorderPos().right - pOther->GetBorderPos().left);
			}
			else if (pOther->GetBorderPos().right < GetCollider()->GetBorderPos().right)
			{
				xDiff = (pOther->GetBorderPos().right - GetCollider()->GetBorderPos().left);
			}
			else
				xDiff = (GetCollider()->GetBorderPos().right - GetCollider()->GetBorderPos().left);

			if (m_fAccelGravity > 0.f || m_Upper > 0.f)
			{
				if (GetCollider()->GetBorderPos().top < pOther->GetBorderPos().top
					&& GetCollider()->GetBorderPos().bottom >= pOther->GetBorderPos().top)
				{
					yDiff = (GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);

					if (yDiff < xDiff)
					{
						fPoint fptPos = GetPos();
						fptPos.y -= (float)(GetCollider()->GetBorderPos().bottom - pOther->GetBorderPos().top);
						SetPos(fptPos);

						m_bGrounding = true;
						m_fAccelGravity = 0.f;
					}
				}
			}
			break;
		}
		case GROUP_TILE::SPIKE:
		{
			break;
		}
		}

	}
}

void CPlayer::OnCollisionExit(CCollider* pOther)
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

	/*방향키로 카메라 이동 상하좌우*/

	if (Key(VK_UP))
	{
		CCameraManager::GetInst()->Scroll(fVec2(0, -1), 600);
	}
	if (Key(VK_DOWN))
	{
		/*TODO:카메라 아래로 일정범위까지*/
		CCameraManager::GetInst()->Scroll(fVec2(0, 1), 600);
	}
	if (Key(VK_LEFT))
	{
		/*TODO:카메라 왼쪽으로 일정범위까지*/
		CCameraManager::GetInst()->Scroll(fVec2(-1, 0), 600);
	}
	if (Key(VK_RIGHT))
	{
		/*TODO:카메라 오른쪽으로 일정범위까지*/
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

PLAYER_STATE CPlayer::GetState()
{
	return PLAYER_STATE();
}

void CPlayer::RegisterPlayer()
{
	instance = this;
}

CPlayer* CPlayer::GetPlayer()
{
	return instance;
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
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


	//fPoint pos = GetPos();

	//if (Key(VK_LEFT))
	//{
	//	pos.x -= m_fSpeed * fDT;
	//	isLeft = true;
	//	GetAnimator()->Play(L"R_Run");
	//}
	//if (Key(VK_RIGHT))
	//{
	//	pos.x += m_fSpeed * fDT;
	//	isLeft = false;
	//	GetAnimator()->Play(L"Run");
	//}
	//if (Key(VK_UP))
	//{
	//	pos.y -= m_fSpeed * fDT;
	//}
	//if (Key(VK_DOWN))
	//{
	//	pos.y += m_fSpeed * fDT;
	//}
	//if (Key('X'))
	//{
	//	m_Upper = UPPER;
	//	pos.y -= 5.f;
	//}
	//if (KeyDown('Z'))
	//{
	//	CreateMissile();
	//	CSoundManager::GetInst()->Play(L"FireSound");
	//	if (isLeft == 1)
	//	{
	//		GetAnimator()->Play(L"R_Fire");
	//		if(KeyUp('Z'))
	//			GetAnimator()->Play(L"Idle");
	//	}
	//	else if (isLeft == 0)
	//	{
	//		GetAnimator()->Play(L"Fire");
	//		if (KeyUp('Z'))
	//			GetAnimator()->Play(L"Idle");
	//		
	//	}
	//}
	//if (KeyDown('C'))
	//{
	//	
	//	CSoundManager::GetInst()->Play(L"Switch");
	//	CSoundManager::GetInst()->Play(L"Flip");
	//}
	//if (Key(VK_SPACE))
	//{
	//	//CameraRelease();
	//}
	//SetPos(pos);
	//GetAnimator()->update();
	//CCameraManager::GetInst()->SetLookAt(GetPos());


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
//			if (abs(GetCollider()->GetFinalPos().y - pOther->GetFinalPos().y) + 2.f >= GetCollider()->GetScale().y / 2.f + pOther->GetScale().y / 2.f)
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
//		case GROUP_TILE::WALL:
//		{
//			if (abs(GetCollider()->GetFinalPos().y - pOther->GetFinalPos().y) + 2.f >= GetCollider()->GetScale().y / 2.f + pOther->GetScale().y / 2.f)
//			{
//				++m_Wall;
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
//				++m_Wall;
//			}
//			break;
//		}
//		case GROUP_TILE::PLATFORM:
//		{
//			if (abs(GetCollider()->GetFinalPos().y - pOther->GetFinalPos().y) + 2.f >= GetCollider()->GetScale().y / 2.f + pOther->GetScale().y / 2.f)
//			{
//				++m_Plat;
//			}
//		}
//		case GROUP_TILE::SPIKE:
//		{
//			break;
//		}
//	}
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
//			if (GetCollider()->GetFinalPos().y < pOther->GetFinalPos().y)
//			{
//				vPos.y -= 2.f;
//			}
//			else if (GetCollider()->GetFinalPos().y > pOther->GetFinalPos().y)
//			{
//				vPos.y += 2.f;
//			}
//
//			break;
//		}
//		case GROUP_TILE::WALL:
//		{		
//			if (GetCollider()->GetFinalPos().y < pOther->GetFinalPos().y)
//		{
//			vPos.y -= 2.f;
//		}
//		else if (GetCollider()->GetFinalPos().y > pOther->GetFinalPos().y)
//		{
//			vPos.y += 2.f;
//		}
//
//		break;
//
//		}
//		case GROUP_TILE::PLATFORM:
//		{
//			if (GetCollider()->GetFinalPos().y < pOther->GetFinalPos().y)
//			{
//				vPos.y -= 2.f;
//			}
//			break;
//		}
//		case GROUP_TILE::SPIKE:
//		{
//			break;
//		}
//		}
//	}
//	SetPos(vPos);
//
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
//		case GROUP_TILE::WALL:
//		{
//			--m_Wall;
//			break;
//		}
//		case GROUP_TILE::PLATFORM:
//		{
//			--m_Plat;
//			break;
//		}
//		case GROUP_TILE::SPIKE:
//		{
//			break;
//		}
//		}
//	}
//}