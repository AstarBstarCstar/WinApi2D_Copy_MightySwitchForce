#include "framework.h"
#include "CScene_Ending.h"
#include "CGameObject.h"
#include "Map_Start.h"
#include "CMap.h"
#include "CBackGround.h"
#include "CSound.h"
#include "CD2DImage.h"
#include "CButtonUI.h"

CScene_Ending::CScene_Ending()
{
	srand(time(NULL));
}

CScene_Ending::~CScene_Ending()
{
}

void CScene_Ending::update()
{
	m_Count += fDT;
	if (m_Trigger)
	{
		if (m_Count >= 0.6f)
		{
			ChangeScn(GROUP_SCENE::SELECT);
			m_Trigger = false;
		}

	}
	if (KeyDown('A') && m_Count >= 1.5f)
	{
		m_Count = 0.f;
		m_Trigger = true;
		CCameraManager::GetInst()->FadeOut(0.7f);
	}
	CScene::update();
}
void CScene_Ending::Enter()
{
	int R = rand() % 5;


	switch (R)
	{
	case 0:
	{
		CMap* End1 = new CMap;
		End1->Load(L"End1", L"texture\\background\\1.png");
		End1->SetPos(fPoint(0, 0));
		AddObject(End1, GROUP_GAMEOBJ::MAP);
		End1->SetScale(fPoint(1600,900));
	}
	case 1:
	{
		CMap* End2 = new CMap;
		End2->Load(L"End1", L"texture\\background\\2.png");
		End2->SetPos(fPoint(0, 0));
		AddObject(End2, GROUP_GAMEOBJ::MAP);
		End2->SetScale(fPoint(1600, 900));
	}
	case 2:
	{
		CMap* End3 = new CMap;
		End3->Load(L"End1", L"texture\\background\\3.png");
		End3->SetPos(fPoint(0, 0));
		AddObject(End3, GROUP_GAMEOBJ::MAP);
		End3->SetScale(fPoint(1600, 900));
	}
	case 3:
	{
		CMap* End4 = new CMap;
		End4->Load(L"End1", L"texture\\background\\4.png");
		End4->SetPos(fPoint(0, 0));
		AddObject(End4, GROUP_GAMEOBJ::MAP);
		End4->SetScale(fPoint(1600, 900));
	}
	case 4:
	{
		CMap* End5 = new CMap;
		End5->Load(L"End1", L"texture\\background\\5.png");
		End5->SetPos(fPoint(0, 0));
		AddObject(End5, GROUP_GAMEOBJ::MAP);
		End5->SetScale(fPoint(1600, 900));
	}


}
	CCameraManager::GetInst()->FadeIn(1.5f);
	CCameraManager::GetInst()->SetLookAt(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	CCameraManager::GetInst()->InitCameraPos(fPoint(WINSIZEX / 2, WINSIZEY / 2));

}

void CScene_Ending::Exit()
{
	DeleteAll();
	CCollisionManager::GetInst()->Reset();
}
