
#pragma once

#include "CGameObject.h"

class CD2DImage;

enum class PLAYER_STATE
{
	IDLE,
	HIT,
	DIE,
	MOVE,
	ATTACK,
	JUMPRISE,
	JUMPFALL,
	JUMPEND,
	FIRE,
	MOVEFIRE,
	JUMPFIRE,
	SMASHED,

	SIZE
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;
	
	float m_fFullHp;

	fVec2 m_fCurDir;
	fVec2 m_fPrevDir;
	float m_fSpeed;
	float m_fAccelGravity;
	float m_Upper;

	bool m_bActing;
	bool m_bAttacking;
	bool m_bGrounding;

	bool alpTrriger=true;
	bool crashTrriger = true;
	bool m_bJustHit;
	float m_HitTimer;
	bool isLeft;
	bool Run;
	bool CameraLock;
	bool Count = 1 ;
	
	float m_gravity;
	float timer = 0;
	UINT m_Wall;
	UINT m_Plat;
	UINT m_Spike;
	
	fPoint m_fvCurDir;
	fPoint m_fvPrevDir;

	PLAYER_STATE m_State;
	PLAYER_STATE m_PrevState;

	

	void CreateMissile();
	void Jump();

public:
	CPlayer();
	~CPlayer();
	void SetPlayerPos();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();
	void CreateSiren();
	PLAYER_STATE GetState();
	void RegisterPlayer();
	void CameraRelease();

	void update_State();
	void update_Move();
	void update_Animation();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);
	static float m_fCurHp;
	static bool isGameOver;
	static bool debugMode;
	static CPlayer* GetPlayer();	// 게임 내에 하나만 있는 플레이어 객체 확인(임의로 싱글톤 선언)
};