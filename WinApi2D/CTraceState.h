#pragma once
#include "CState.h"
class CTraceState : public CState
{
public:
	CTraceState(STATE_MON state);
	static bool tracing;
	virtual ~CTraceState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};