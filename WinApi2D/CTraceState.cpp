#include "framework.h"
#include "CTraceState.h"
#include "CPlayer.h"
#include "CMonster.h"

CTraceState::CTraceState(STATE_MON state): CState(state)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	CPlayer* pPlayer = CPlayer::GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();
	if (fLen >= pMonster->GetMonInfo().fRecogRange)
	{
		ChangeAIState(GetOwnerAI(), STATE_MON::IDLE);
		tracing = false;
	}
	fPoint pos = pMonster->GetPos();
	pos += fvDiff.Normalize() * 500 * fDT;
	tracing = true;
	pMonster->SetPos(pos);
}

void CTraceState::Enter()
{
}


void CTraceState::Exit()
{
}