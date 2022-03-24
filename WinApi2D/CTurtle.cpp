#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CTurtle.h"

CTurtle::CTurtle()
{
	CD2DImage* m_Tpatrol = CResourceManager::GetInst()->LoadD2DImage(L"MonsterTex", L"texture\\Animation\\Monster\\Turtle\Walk\\TurtleWalk_212_204.png");
	m_pAI = nullptr;

	SetName(L"Turtle");
	SetScale(fPoint(212 * 0.7, 204 * 0.7));

	CreateCollider();
	GetCollider()->SetScale(fPoint(70.f, 70.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"TurtleWalk", m_Tpatrol, fPoint(0, 0), fPoint(212.f, 204.f), fPoint(212.f, 0), 0.1f, 10);
	GetAnimator()->CreateAnimation(L"R_TurtleWalk", m_Tpatrol, fPoint(0, 0), fPoint(212.f, 204.f), fPoint(212.f, 0), 0.1f, 10, true);
	GetAnimator()->Play(L"TurtleWalk");
}

CTurtle::~CTurtle()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}


CTurtle* CTurtle::Clone()
{
	CTurtle* newTurtle = new CTurtle;
	if (nullptr != m_pAI)
	{
		newTurtle->m_pAI = new AI;
	}
	return new CTurtle(*newTurtle);
}

CTurtle* CTurtle::Create(MON_TYPE type, fPoint pos)
{
	CTurtle* pTur = nullptr;

	switch (type)
	{
	case MON_TYPE::NORMAL:
	{
		pTur = new CTurtle;
		pTur->SetPos(pos);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fHP = 9999.f;
		info.fSpeed = 200.f;

		info.fAttRange = 0.f;
		info.fRecogRange = 0.f;

		AI* p_TurAI = new AI;
		p_TurAI->AddState(new CIdleState(STATE_MON::IDLE));
		p_TurAI->SetCurState(STATE_MON::IDLE);
		pTur->SetMonInfo(info);
		pTur->SetAI(p_TurAI);
		break;
	}
	case MON_TYPE::RANGE:
		break;
	default:
		break;


	}
	assert(pTur);
	return pTur;
}

void CTurtle::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::GetInst()->GetRenderPos(pos);

	component_render();
}

void CTurtle::update()
{
	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pAI)
		m_pAI->update();
}

float CTurtle::GetSpeed()
{
	return m_tInfo.fSpeed;
}

const tMonInfo& CTurtle::GetMonInfo()
{
	return m_tInfo;
}

void CTurtle::SetSpeed(float speed)
{
	m_tInfo.fSpeed = speed;
}

void CTurtle::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwnTurtle = this;
}

void CTurtle::SetMonInfo(const tMonInfo& info)
{
	m_tInfo = info;
}

void CTurtle::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		//웅크리기 패턴 사용
	}
	else if (pOtherObj->GetName() == L"Tile")
	{
		//뒤로돌아
	}
}
