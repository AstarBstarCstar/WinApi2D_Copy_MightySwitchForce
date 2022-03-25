#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
//신경치료 아프다 아프기보다 기분이 뒤지게 나쁘다
CMonster::CMonster()
{
	CD2DImage* m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"MonsterTex", L"texture\\Animation\\Monster\\Bat\\Fly\\Bat_292_220.png");

	m_pAI = nullptr;

	SetName(L"Monster");
	SetScale(fPoint(292*0.7, 220*0.7));

	CreateCollider();
	GetCollider()->SetScale(fPoint(50.f, 50.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PlayerStand", m_pImg, fPoint(0, 0), fPoint(292.f, 220.f), fPoint(292.f, 0), 0.1f, 7, true);
	GetAnimator()->Play(L"PlayerStand");
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
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
		info.fAttRange = 50.f;
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
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::GetInst()->GetRenderPos(pos);

	component_render();
}

void CMonster::update()
{
	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pAI)
		m_pAI->update();

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













//#include "framework.h"
//#include "CMonster.h"
//#include "CCollider.h"
//#include "CAnimator.h"
//#include "CAnimation.h"
//#include "CTexture.h"
//#include "CScene.h"
//#include "AI.h"
//
//CMonster* CMonster::Clone()
//{
//	return new CMonster(*this);
//}
//
//CMonster::CMonster()
//{
//	m_fptCenterPos = fPoint(0, 0);
//	m_fVelocity = 0;
//	m_fDistance = 300;
//	m_bIsUPDir = true;
//
//	m_MImg = CResourceManager::GetInst()->LoadD2DImage(L"MonsterImg", L"texture\\Animation\\MonTest.PNG");
//	SetName(L"MonsterImg");
//	SetScale(fPoint(100, 100));
//
//	//SetName(L"Monster");
//	//SetScale(fPoint(100.f, 100.f));
//
//	CreateCollider();
//	GetCollider()->SetScale(fPoint(90.f, 90.f));
//
//
//
//	CreateCollider();
//	GetCollider()->SetScale(fPoint(40.f, 40.f));
//	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));
//
//	CreateAnimator();
//	GetAnimator()->CreateAnimation(L"RightNone", m_MImg, fPoint(0.f, 0.f), fPoint(89.1f, 157.f), fPoint(89.1f, 0.f), 0.1f, 9,true);
//	//GetAnimator()->CreateAnimation(L"RightNone",	m_pImg, fPoint(0.f, 70.f),	fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.5f, 2);
//	//GetAnimator()->CreateAnimation(L"LeftMove",		m_pImg, fPoint(0.f, 140.f),	fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
//	//GetAnimator()->CreateAnimation(L"RightMove",	m_pImg, fPoint(0.f, 210.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
//	//GetAnimator()->CreateAnimation(L"LeftHit",		m_pImg, fPoint(140.f, 0.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
//	//GetAnimator()->CreateAnimation(L"RightHit",		m_pImg, fPoint(140.f, 70.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
//	GetAnimator()->Play(L"RightNone");
//
//}
//
//CMonster::~CMonster()
//{
//	if (nullptr != m_pAI)
//	{
//		delete m_pAI;
//	}
//}
//
//void CMonster::update()
//{
//	fPoint pos = GetPos();
//
//	if (m_bIsUPDir)
//	{
//		pos.y -= fDT * m_fVelocity;
//		if (pos.y < m_fptCenterPos.y - m_fDistance)
//			m_bIsUPDir = false;
//	}
//	else
//	{
//		pos.y += fDT * m_fVelocity;
//		if (pos.y > m_fptCenterPos.y + m_fDistance)
//			m_bIsUPDir = true;
//	}
//
//	SetPos(pos);
//	if (nullptr != GetAnimator())
//		GetAnimator()->update();
//	if (nullptr != m_pAI)
//		m_pAI->update();
//}
//void CMonster::render()
//{
//	component_render();
//}
//
//void CMonster::SetAI(AI* ai)
//{
//	m_pAI = ai;
//	m_pAI->m_pOwner = this;
//}
//
//void CMonster::SetCenterPos(fPoint point)
//{
//	m_fptCenterPos = point;
//}
//
//void CMonster::OnCollisionEnter(CCollider* pOther)
//{
//
//}