#include "framework.h"
#include "CExitRobot.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CAnimation.h"

CExitRobot::CExitRobot()
{	
	SetName(L"EndRobot");
	CreateCollider();
	GetCollider()->SetScale(fPoint(50.f, 50.f));

	CD2DImage* m_OpenIdle = CResourceManager::GetInst()->LoadD2DImage(L"OpenIdle", L"texture\\Animation\\EndRobot\\OpenIdleClose\\Open.png"); 
	CD2DImage* m_RobotIdle = CResourceManager::GetInst()->LoadD2DImage(L"RobotIdle", L"texture\\Animation\\EndRobot\\Idle\\Idle.png");
	CD2DImage* m_TakeOff = CResourceManager::GetInst()->LoadD2DImage(L"TakeOff", L"texture\\Animation\\EndRobot\\Take_Off\\takeoff.png");
	CD2DImage* m_EnterZero = CResourceManager::GetInst()->LoadD2DImage(L"EnterZero", L"texture\\Animation\\EndRobot\\Enter_Zero_or_Base\\Enter.png");
	CD2DImage* m_Fly = CResourceManager::GetInst()->LoadD2DImage(L"Fly", L"texture\\Animation\\EndRobot\\Fly_Away\\1.png");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"TakeOff", m_TakeOff, fPoint(0, 0), fPoint(524.f, 444.f), fPoint(524.f, 0), fPoint(524.f, 444.f), 0, 0.1f, 11, false, false);
	GetAnimator()->CreateAnimation(L"OpenIdle", m_OpenIdle, fPoint(0, 0), fPoint(456.f, 372.f), fPoint(456.f, 0), fPoint(456.f, 372.f), 0, 0.1f, 18, true, false);
	GetAnimator()->CreateAnimation(L"RobotIdle", m_RobotIdle, fPoint(0, 0), fPoint(420.f, 360.f), fPoint(420.f, 0), fPoint(420.f, 360.f), 0, 0.1f, 18, true, false);
	GetAnimator()->CreateAnimation(L"EnterZero", m_EnterZero, fPoint(0, 0), fPoint(464.f, 364.f), fPoint(464.f, 0), fPoint(464.f, 364.f), 0, 0.1f, 12, false, false);
	GetAnimator()->CreateAnimation(L"Fly", m_Fly, fPoint(0, 0), fPoint(336.f, 476.f), fPoint(336.f, 0), fPoint(336.f, 476.f), 0, 1.f, 1, true, false);
	GetAnimator()->Play(L"RobotIdle");
}

CExitRobot::~CExitRobot()
{
}

void CExitRobot::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		if (CGameObject::holiganSave == 6)
		{
			trriger = false;
			///*GetAnimator()->Play("");*/
			DeleteObj(pOtherObj);
			GetAnimator()->Play(L"EnterZero");
		}
	}
}

CExitRobot* CExitRobot::Clone()
{
	return new CExitRobot(*this);
}

void CExitRobot::render()
{
	if (CGameObject::holiganSave==6)
	{
		fPoint pos = GetPos();
		fPoint scale = GetScale();
		pos = CCameraManager::GetInst()->GetRenderPos(pos);

		component_render();
	}
}

void CExitRobot::update()
{
	if (trriger)
	{
		if (GetAnimator()->PlayEnd(L"RobotIdle") == true)
		{
			GetAnimator()->Play(L"OpenIdle");
		}

		else if (GetAnimator()->PlayEnd(L"OpenIdle") == true)
		{
			GetAnimator()->Play(L"RobotIdle");
		}
	}
	if (GetAnimator()->PlayEnd(L"EnterZero")==true)
	{
		GetAnimator()->Play(L"TakeOff");
	}
	if (GetAnimator()->PlayEnd(L"TakeOff") == true)
	{
		CCameraManager::GetInst()->FadeOut(4.f);
		GetAnimator()->Play(L"Fly");
		End = true;
		
		
	}
	if (End)
	{
		timer += fDT;
		fPoint x = this->GetPos();
		accel += fDT*1.5;
		x.y -=accel;
		SetPos(fPoint(x));//피벗 위치 오른쪽으로 
		
	}
	if (timer >= 3.9f)
	{
		timer = 0.f;
		ChangeScn(GROUP_SCENE::END);
	}

	GetAnimator()->update();

}
