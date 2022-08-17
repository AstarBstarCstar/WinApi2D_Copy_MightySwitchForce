#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CPlayer.h"
#include "CGameObject.h"
CMonster::CMonster()
{
	CD2DImage* m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"MonsterTex", L"texture\\Animation\\Monster\\Bat\\Fly\\Bat_292_220.png");
	m_pImg2 = CResourceManager::GetInst()->LoadD2DImage(L"BatCrash", L"texture\\Animation\\Monster\\Bat\\batcrash.png");

	m_pAI = nullptr;
	m_fCurDir = { 1.f, 1.f };
	SetName(L"Monster");
	SetScale(fPoint(292*0.6, 220*0.6));

	CreateCollider();
	GetCollider()->SetScale(fPoint(70.f, 70.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", m_pImg, fPoint(0, 0), fPoint(292.f, 220.f), fPoint(292.f, 0), fPoint(292.f, 220.f),0, 0.1f, 7,true, true);
	GetAnimator()->CreateAnimation(L"R_IDLE", m_pImg, fPoint(0, 0), fPoint(292.f, 220.f), fPoint(292.f, 0), fPoint(292.f, 220.f), 0, 0.1f, 7, true, false);
	GetAnimator()->CreateAnimation(L"GLASSBAT", m_pImg2, fPoint(0, 0), fPoint(712.f, 712.f), fPoint(712.f, 0), fPoint(712.f, 712.f), 0, 3.0f, 1, false, false);
	GetAnimator()->Play(L"IDLE");
}
bool CTraceState::tracing = false;

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}
void CMonster::SetAnim(bool setter)
{
	if (setter)
	{
		GetAnimator()->Play(L"R_IDLE");
	}
}

CMonster* CMonster::Clone()
{
	CMonster* newMonster = new CMonster;
	if (nullptr != m_pAI)
	{
		newMonster->m_pAI = new AI;
	}
	return new CMonster(*newMonster);
}

CMonster* CMonster::Create(MON_TYPE type, fPoint pos)
{
	CMonster* pMon = nullptr;

	switch (type)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 100.f;
		info.fRecogRange = 300.f;
		info.fHP = 1.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->SetCurState(STATE_MON::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::RANGE:
		break;
	default:
		break;
	}
	assert(pMon);
	return pMon;
}

void CMonster::render()
{
	if (CPlayer::debugMode)
	CGameObject::debug_render();

	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::GetInst()->GetRenderPos(pos);

	if (!hit&&CTraceState::tracing)
	{
		CPlayer* pPlayer = CPlayer::GetPlayer();
		if (nullptr == pPlayer)
			return;

		fPoint fptPlayerPos = pPlayer->GetPos();

		CMonster* pMonster = this;
		fPoint fptMonsterPos = pMonster->GetPos();

		fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
		int apos = fvDiff.Normalize().x * 500 * fDT;
		if (apos >= 1)
		{
			GetAnimator()->Play(L"R_IDLE");
		}
		else if (apos < -1)
		{
			GetAnimator()->Play(L"IDLE");
		}
	}
	if (hit)
	{
		GetCollider()->SetScale(fPoint(0.f, 0.f));
		deletetimer += fDT;
		GetAnimator()->Play(L"GLASSBAT");
		SetGroup((GROUP_GAMEOBJ)10);
		if (deletetimer >= 5)
		{
			DeleteObj(this);
		}
		
	}

	

	component_render();
}

void CMonster::update()
{

	if (CGameObject::Switching != true)
	{
		if (nullptr != GetAnimator())
			GetAnimator()->update();
		if (nullptr != m_pAI&&!hit)
			m_pAI->update();
	}
}


float CMonster::GetSpeed()
{
	return m_tInfo.fSpeed;
}

const tMonInfo& CMonster::GetMonInfo()
{
	return m_tInfo;
}

void CMonster::SetSpeed(float speed)
{
	m_tInfo.fSpeed = speed;
}

void CMonster::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CMonster::SetMonInfo(const tMonInfo& info)
{
	m_tInfo = info;
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_tInfo.fHP -= 1;
		if (m_tInfo.fHP <= 0)
		DeleteObj(this);
	}

}
void CMonster::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Switching"&&!hit)
	{
		hit = true;
		SetName(L"Dead");
		CSoundManager::GetInst()->Play(L"BATHIT");
		CSoundManager::GetInst()->Play(L"GlassHit");
		CCameraManager::GetInst()->ShakeM(1.0f);
	}
}