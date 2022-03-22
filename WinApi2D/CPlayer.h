
#pragma once

#include "CGameObject.h"

class CD2DImage;

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;
	float m_fSpeed = 300;

	void CreateMissile();
	void Jump();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();

	void RegisterPlayer();
	void CameraRelease();
	static CPlayer* GetPlayer();	// ���� ���� �ϳ��� �ִ� �÷��̾� ��ü Ȯ��(���Ƿ� �̱��� ����)

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
