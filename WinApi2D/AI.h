#pragma once

class CMonster;
class CState;
class CTurtle;

class AI
{
	friend class CMonster;
	friend class CTurtle;

private:
	map<STATE_MON, CState*> m_mapState;
	CMonster* m_pOwner;
	CTurtle* m_pOwnTurtle;
	CState* m_pCurState;

public:
	void update();

	void AddState(CState* state);

	CMonster* GetOwnerAI();
	CTurtle* GetOwnerTurtleAI();
	CState* GetState(STATE_MON state);
	void SetCurState(STATE_MON state);
	void ChangeState(STATE_MON nextState);

public:
	AI();
	~AI();


};
