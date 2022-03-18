#pragma once

class CMonster;
class CState;

class AI
{
	friend class CMonster;

private:
	map<STATE_MON, CState*> m_mapState;
	CMonster* m_pOwner;
	CState* m_pCurState;

public:
	void update();

	void AddState(CState* state);

	CMonster* GetOwnerAI();
	CState* GetState(STATE_MON state);
	void SetCurState(STATE_MON state);
	void ChangeState(STATE_MON nextState);

public:
	AI();
	~AI();


};
