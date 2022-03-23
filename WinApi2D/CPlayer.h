
#pragma once

#include "CGameObject.h"

class CD2DImage;

enum class CharacterState
{
	IDLE,
	HIT,
	DEAD,

	LANDMOVE,
	ATTACK,
	JUMP,
	FALL,

	SIZE
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;
	float m_fSpeed = 300;
	float m_gravity;
	float m_Upper;
	UINT m_Ground;
	UINT m_Plat;
	UINT m_Spike;
	
	fPoint m_fvCurDir;
	fPoint m_fvPrevDir;

	CharacterState m_State;

	float m_fAccelGravity;
	float m_fVelocity;
	float m_fMaxVelocity;
	bool  m_bIsGrounded;
	

	void CreateMissile();
	void Jump();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();

	CharacterState GetState();
	void RegisterPlayer();
	void CameraRelease();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);

	static CPlayer* GetPlayer();	// 게임 내에 하나만 있는 플레이어 객체 확인(임의로 싱글톤 선언)

	bool isLeft;
	bool Run;
	bool CameraLock;
	bool Count = 1;
};











//#pragma once
//
//#include "CGameObject.h"
//
//class CD2DImage;
//
//class CPlayer : public CGameObject
//{
//private:
//	CD2DImage* m_pImg;
//	float m_fVelocity = 300;
//
//	void CreateMissile();
//
//public:
//	CPlayer();
//	~CPlayer();
//	virtual CPlayer* Clone();
//
//	virtual void update();
//	virtual void render();
//
//	
//};
//
