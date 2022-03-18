
#pragma once

#include "CGameObject.h"

class CD2DImage;

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;
	float m_fSpeed = 300;

	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();

	void RegisterPlayer();
	static CPlayer* GetPlayer();	// ���� ���� �ϳ��� �ִ� �÷��̾� ��ü Ȯ��(���Ƿ� �̱��� ����)
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
