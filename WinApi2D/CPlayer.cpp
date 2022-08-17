
#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTile.h"
#include "SwitchBlock.h"
#include "CPlayerSiren.h"
CPlayer* CPlayer::instance = nullptr;
bool CPlayer::isGameOver = false;
bool CPlayer::debugMode = false;
bool CPlayer::CameraLock = false;
float CPlayer::m_fCurHp;
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
	CD2DImage* m_Die = CResourceManager::GetInst()->LoadD2DImage(L"Die", L"texture\\Animation\\PatriciaWagon\\Die\\Die_200_275.png");
	CD2DImage* m_Hit = CResourceManager::GetInst()->LoadD2DImage(L"Hit", L"texture\\Animation\\PatriciaWagon\\Hit\\Hit.png");
	CD2DImage* m_Sweat = CResourceManager::GetInst()->LoadD2DImage(L"Sweat", L"texture\\Animation\\PatriciaWagon\\Sweat\\Sweat_260_236.png");
	CD2DImage* m_Smashed = CResourceManager::GetInst()->LoadD2DImage(L"Smashed", L"texture\\Animation\\PatriciaWagon\\Smashed\\Smashed_731_846.png");
	m_crik = CResourceManager::GetInst()->LoadD2DImage(L"crik", L"texture\\crik.png");
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
	GetAnimator()->CreateAnimation(L"Die", m_Die, fPoint(0.f, 0.f), fPoint(200.f, 275.f), fPoint(200.f, 0.f), fPoint(200.f, 275.f), 0, 0.035f, 72, true, false);
	GetAnimator()->CreateAnimation(L"R_Die", m_Die, fPoint(0.f, 0.f), fPoint(200.f, 275.f), fPoint(200.f, 0.f), fPoint(200.f, 275.f), 0, 0.035f, 72, false, true);
	GetAnimator()->CreateAnimation(L"Sweat", m_Sweat, fPoint(0.f, 0.f), fPoint(260.f, 236.f), fPoint(260.f, 0.f), fPoint(260.f, 236.f), 0, 0.065f, 13, true, false);
	GetAnimator()->CreateAnimation(L"R_Sweat", m_Sweat, fPoint(0.f, 0.f), fPoint(260.f, 236.f), fPoint(260.f, 0.f), fPoint(260.f, 236.f), 0, 0.065f, 13, false, true);
	GetAnimator()->CreateAnimation(L"Hit", m_Hit, fPoint(0.f, 0.f), fPoint(200.f, 275.f), fPoint(200.f, 0.f), fPoint(200.f, 275.f), 0, 0.065f, 4, true, false);
	GetAnimator()->CreateAnimation(L"R_Hit", m_Hit, fPoint(0.f, 0.f), fPoint(200.f, 275.f), fPoint(200.f, 0.f), fPoint(200.f, 275.f), 0, 0.065f, 4, true, true);
	GetAnimator()->CreateAnimation(L"Smashed", m_Smashed, fPoint(0.f, 0.f), fPoint(731.f, 846.f), fPoint(731.f, 0.f), fPoint(731.f, 846.f),0,0.07f,9, true, false);
	GetAnimator()->Play(L"Idle");

	CSoundManager::GetInst()->AddSound(L"FireSound", L"sound\\PELLET_FIRE.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Switch", L"sound\\Switch.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Camera", L"sound\\SFX_CAMERA.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"CameraRelease", L"sound\\SFX_CAMERA_RELEASE.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"GlassHit", L"sound\\SFX_GLASS_SMASH.wav" , false, false);
	CSoundManager::GetInst()->AddSound(L"Spike", L"sound\\SFX_DIE_SPIKES.wav" , false, false);
	CSoundManager::GetInst()->AddSound(L"Hit", L"sound\\OUCH_5.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Switching", L"sound\\Switch.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Jump", L"sound\\SFX_JUMP.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"HITBULLET", L"sound\\SFX_PELLET_HIT_FOE.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"BATHIT", L"sound\\SFX_BAT_HIT.wav", false, false);

	CSoundManager::GetInst()->AddSound(L"TAKEOFF", L"sound\\SFX_ROBOT_TAKEOFF.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"ROBOTCLOSE", L"sound\\SFX_ROBOT_CLOSE.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"ROBOTOPEN", L"sound\\SFX_ROBOT_OPEN.wav", false, false);
	
	

	CreateCollider();
	GetCollider()->SetScale(fPoint(60.f, 160.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 25.f));
	
	isLeft = false;
	CameraLock = false;
	m_bJustHit = false;
	m_bGrounding = true;
	Run = false;
	m_bAttacking = false;

	m_fCurHp = 3;
	m_fFullHp = 3;
	m_fCurDir = { 1.f, 1.f };
	m_fPrevDir = {};
	timer=0;
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

void CPlayer::update()
{
	CGameObject::Switching;
	if (CGameObject::Switching != true || m_State==PLAYER_STATE::SMASHED)
	{
		update_Animation();
		GetAnimator()->update();
		if (CameraLock != true)
		{
		update_State();
		if (m_State != PLAYER_STATE::DIE)
		{
			update_Move();
		}
		}
	}

	else if (CGameObject::Switching == true || m_State == PLAYER_STATE::SMASHED)
	{
		update_State();
	}
	CCameraManager::GetInst()->SetLookAt(GetPos());
	m_PrevState = m_State;
	m_fPrevDir = m_fCurDir;

	if (KeyDown(VK_HOME))
	{
		if (CPlayer::debugMode == false)
			CPlayer::debugMode = true;

		else if (CPlayer::debugMode == true)
			CPlayer::debugMode = false;
	}
	if (KeyDown(VK_SPACE))
	{
		CSoundManager::GetInst()->Play(L"Camera");
		CameraLock = true;
		CCameraManager::GetInst()->FollowTargetObj(nullptr, 0, 0);
	}
	if (KeyUp(VK_SPACE))
	{
		CSoundManager::GetInst()->Play(L"CameraRelease");
		CameraLock = false;
	}
	if (CameraLock == true)
	{
		
		/*CCameraManager::GetInst()->FollowTargetObj(nullptr, 0, 0);*/
		CameraRelease();
	}
	if (m_State == PLAYER_STATE::SMASHED)
	{
		GetCollider()->SetScale(fPoint(0.f,0.f));
	}
}

void CPlayer::render()
{
	component_render();

	if(CPlayer::debugMode)
	CGameObject::debug_render();//디버그용 정보 표시

	if(CameraLock)
	CRenderManager::GetInst()->RenderImage(m_crik, 800 - 1590 * 0.5, 450 - 890 * 0.5, 800 + 1590 * 0.5, 450 + 890 * 0.5);
}

void CPlayer::update_State()
{
	if (m_fCurHp <= 0)
	{
		m_State = PLAYER_STATE::DIE;
	}
	if (m_State != PLAYER_STATE::SMASHED && m_State != PLAYER_STATE::HIT&&m_State !=PLAYER_STATE::DIE)
	{
		if (m_State != PLAYER_STATE::SMASHED)
		{
			if (m_fSpeed <= 0 && !m_bAttacking)
			{
				if (m_State != PLAYER_STATE::JUMPRISE && m_State != PLAYER_STATE::SMASHED && m_State != PLAYER_STATE::HIT)
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
				CSoundManager::GetInst()->Play(L"Jump");
				GetAnimator()->FindAnimation(L"R_JumpRise")->SetFrame(0);
				GetAnimator()->FindAnimation(L"JumpRise")->SetFrame(0);
				m_State = PLAYER_STATE::JUMPRISE;
			}
			if (!m_bAttacking && m_fAccelGravity > 200)
			{
				GetAnimator()->FindAnimation(L"R_JumpFall")->SetFrame(0);
				GetAnimator()->FindAnimation(L"JumpFall")->SetFrame(0);
				m_State = PLAYER_STATE::JUMPFALL;
			}
			else
			{
				m_fSpeed = 0.f;
			}
			if (KeyDown('Z') && !m_bGrounding)
			{
				CreateMissile();
				GetAnimator()->FindAnimation(L"R_JumpFire")->SetFrame(0);
				GetAnimator()->FindAnimation(L"JumpFire")->SetFrame(0);
				m_State = PLAYER_STATE::JUMPFIRE;
				m_bAttacking = true;
			}
			if (KeyDown('Z') && m_bGrounding && m_fSpeed <= 0)
			{
				CreateMissile();
				GetAnimator()->FindAnimation(L"R_Fire")->SetFrame(0);
				GetAnimator()->FindAnimation(L"Fire")->SetFrame(0);
				m_State = PLAYER_STATE::ATTACK;
				m_bAttacking = true;
			}
			if (KeyDown('C'))
			{
				CreateSiren();
				CSoundManager::GetInst()->Play(L"Switching");
			}
			if (Key(VK_LEFT) && KeyDown('Z') && m_bGrounding)
			{
				if (PLAYER_STATE::JUMPRISE != m_State)
				{
					CreateMissile();
					GetAnimator()->FindAnimation(L"R_RunFire")->SetFrame(2);
					GetAnimator()->FindAnimation(L"RunFire")->SetFrame(2);
					m_State = PLAYER_STATE::MOVEFIRE;
					m_bAttacking = true;
				}
			}
			if (Key(VK_RIGHT) && KeyDown('Z') && m_bGrounding)
			{
				if (PLAYER_STATE::JUMPRISE != m_State)
				{
					CreateMissile();
					GetAnimator()->FindAnimation(L"R_RunFire")->SetFrame(1);
					GetAnimator()->FindAnimation(L"RunFire")->SetFrame(1);
					m_State = PLAYER_STATE::MOVEFIRE;
					m_bAttacking = true;
				}
			}
		}
	}
	if (m_bJustHit == true)
	{
		float fAlpha = 0.5f;

		m_HitTimer += fDT;
		if (m_HitTimer >= 3)
		{
			m_HitTimer = 0;
			m_bJustHit = false;
		}

	}
}
void CPlayer::update_Move()
{
	if (m_State != PLAYER_STATE::SMASHED&&m_State != PLAYER_STATE::HIT)
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
		//CGameObject::Gravity_Apply(); //플레이어는 상태패턴과 다른 처리를 위해서 컴포넌트를 받지 않고 직접 할당

		fPoint fptPos = GetPos();
		fptPos.y += m_fAccelGravity * fDT;
		fptPos.x += m_fvCurDir.x * m_fSpeed * fDT;
		m_fAccelGravity += GRAVITY * fDT;
		if (m_fAccelGravity >= 6000.f)
			m_fAccelGravity = 6000.f;
		SetPos(fptPos);
		

	}

}
void CPlayer::update_Animation()
{
	if (m_PrevState == m_State && m_fvPrevDir == m_fvCurDir)//이전 상태와 현재상태가 같거나, 이전 방향과 현재 방향이 같다면 애니메이션 갱신 하지 않음
	{
		return;
	}
	switch (m_State)
	{
	case PLAYER_STATE::IDLE:
	{
		static float fIdleTime = 0.f;
		fIdleTime += fDT;
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"R_Idle");
		}
		else if (1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"Idle");
		}
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
	case PLAYER_STATE::HIT:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"R_Hit");
		}
		else
		{
			GetAnimator()->Play(L"Hit");
		}
		if (m_HitTimer>=0.5)
		{
			m_State = PLAYER_STATE::IDLE;
		}
		break;

	}
	case PLAYER_STATE::DIE:
	{
		isDead = true;
		if (-1 == m_fvCurDir.x)
		{
			CSoundManager::GetInst()->Stop(L"Stbgm");
			GetAnimator()->Play(L"R_Die");
		}
		else
		{
			
			CSoundManager::GetInst()->Stop(L"Stbgm");
			GetAnimator()->Play(L"Die");
		}
		if (GetAnimator()->PlayEnd(L"R_Die")==true|| GetAnimator()->PlayEnd(L"Die") == true)
		{
			DeleteObj(this);
		}
		break;

	}
	case PLAYER_STATE::SMASHED:
	{
		GetAnimator()->Play(L"Smashed");
		if (crashTrriger)
		{
			CCameraManager::GetInst()->ShakeM(1.0f);
			CSoundManager::GetInst()->Play(L"Hit");
			CSoundManager::GetInst()->Play(L"GlassHit");
			CSoundManager::GetInst()->Stop(L"Stbgm");
			crashTrriger = false;
		}

		timer += fDT;
		if (timer >= 1.5f)
		{
			if (alpTrriger)
			{
				CCameraManager::GetInst()->FadeOut(3.f);
				alpTrriger = false;
			}
			if (timer >= 4.5f)
			{
				timer = 0.f;
				isGameOver = true;
				alpTrriger = true;
				crashTrriger = true;
			}
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
		if (GetAnimator()->PlayEnd(L"Fire")==true|| GetAnimator()->PlayEnd(L"R_Fire") == true)
		{
			m_bAttacking = false;
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
		if (GetAnimator()->PlayEnd(L"RunFire")==true|| GetAnimator()->PlayEnd(L"R_RunFire") == true)
		{
			m_bAttacking = false;
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

void CPlayer::CreateSiren()
{
	fPoint fSirenPos = GetPos();
	fSirenPos.y -= 100.f;

	CPlayerSiren* pSiren = new CPlayerSiren;
	pSiren->SetPos(fSirenPos);
	pSiren->SetScale(fPoint(512.f,512.f));
		pSiren->SetName(L"PlayerSiren");
		CreateObj(pSiren, GROUP_GAMEOBJ::UI);
}

void CPlayer::CreateMissile()
{
	fPoint fpMissilePos = GetPos();
	fpMissilePos.x += GetScale().x / 2.f;

	/*발사체 오브젝트 생성*/
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
	CSoundManager::GetInst()->Play(L"FireSound");
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
	if (pOtherObj->GetName() == L"Switching")												
	{																																																
		m_State = PLAYER_STATE::SMASHED;
	}
	if (pOtherObj->GetName() == L"Monster")
	{
		if (m_bJustHit == false&&m_State!=PLAYER_STATE::SMASHED)
		{
			CSoundManager::GetInst()->Play(L"Hit");
			CSoundManager::GetInst()->Play(L"Spike");
			GetAnimator()->FindAnimation(L"Hit")->SetFrame(0);
			GetAnimator()->FindAnimation(L"R_Hit")->SetFrame(0);
			m_fCurHp--;
			m_bJustHit = true;
			m_State = PLAYER_STATE::HIT;
		}
	}
	if (pOtherObj->GetName() == L"SwitchBlock")
	{
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
		}
	}
	if (pOtherObj->GetName() == L"Tile")
	{
		switch (Type)
		{
		case GROUP_TILE::GROUND:
		case GROUP_TILE::WALL:
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
		default:
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

	/*방향키로 카메라 이동 상하좌우*/
	if (Key(VK_UP))
	{
		CCameraManager::GetInst()->Scroll(fVec2(0, -1), 600);
	}
	if (Key(VK_DOWN))
	{
		CCameraManager::GetInst()->Scroll(fVec2(0, 1), 600);
	}
	if (Key(VK_LEFT))
	{
		CCameraManager::GetInst()->Scroll(fVec2(-1, 0), 600);
	}
	if (Key(VK_RIGHT))
	{
		CCameraManager::GetInst()->Scroll(fVec2(1, 0), 600);
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