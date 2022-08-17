#include "framework.h"
#include "CScene_Ending.h"
#include "CGameObject.h"
#include "Map_Start.h"
#include "CMap.h"
#include "CBackGround.h"
#include "CSound.h"
#include "CD2DImage.h"
#include "CButtonUI.h"
#include "CScene_Start.h"

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
	CSoundManager::GetInst()->AddSound(L"End", L"sound\\End.wav", false, true);
	CSoundManager::GetInst()->Play(L"End");
	int R = rand() % 4;


	switch (R)
	{
	case 0:
	{
		CMap* End1 = new CMap;
		End1->Load(L"End1", L"texture\\background\\1.png");
		End1->SetPos(fPoint(0, 0));
		AddObject(End1, GROUP_GAMEOBJ::MAP);
	}
	case 1:
	{
		CMap* End2 = new CMap;
		End2->Load(L"End1", L"texture\\background\\2.png");
		End2->SetPos(fPoint(0, 0));
		AddObject(End2, GROUP_GAMEOBJ::MAP);
	}
	case 2:
	{
		CMap* End3 = new CMap;
		End3->Load(L"End1", L"texture\\background\\3.png");
		End3->SetPos(fPoint(0, 0));
		AddObject(End3, GROUP_GAMEOBJ::MAP);
	}
	default:
	{
		CMap* End4 = new CMap;
		End4->Load(L"End1", L"texture\\background\\4.png");
		End4->SetPos(fPoint(0, 0));
		AddObject(End4, GROUP_GAMEOBJ::MAP);
	}
	CButtonUI* m_pPar = new CButtonUI;
	m_pPar->SetScale(fPoint(100.f, -920.f));
	m_pPar->SetTextColor(RGB(255, 255, 0));
	m_pPar->SetFontSize(75);
	m_pPar->SetText(L"1:50.00");
	m_pPar->SetPos(fPoint(WINSIZEX / 2.f - 405.f, WINSIZEY / 2.f + 100.f));
	AddObject(m_pPar, GROUP_GAMEOBJ::UI);


	float temp = 0.f;
	int min;
	int sec;
	int cel;
	temp = CScene_Start::timer;
	min = temp / 60;
	sec = ceil((short)temp % 60);
	cel = ceil((int)(temp * 100) % 100);
	wstring Time_min;
	wstring Time_sec;
	wstring Time_cel;
	Time_min = std::to_wstring(min);
	Time_sec = std::to_wstring(sec);
	Time_cel = std::to_wstring(cel);

	CButtonUI* m_pMin = new CButtonUI;
	m_pMin->SetScale(fPoint(100.f, -735.f));
	m_pMin->SetTextColor(RGB(255, 255, 0));
	m_pMin->SetFontSize(75);
	m_pMin->SetText(Time_min);
	m_pMin->SetPos(fPoint(WINSIZEX / 2.f - 525.f, WINSIZEY / 2.f + 100.f));
	AddObject(m_pMin, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pcol = new CButtonUI;
	m_pcol->SetScale(fPoint(100.f, -735.f));
	m_pcol->SetTextColor(RGB(255, 255, 0));
	m_pcol->SetFontSize(75);
	m_pcol->SetText(L":");
	m_pcol->SetPos(fPoint(WINSIZEX / 2.f - 490.f, WINSIZEY / 2.f + 100.f));
	AddObject(m_pcol, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pSec = new CButtonUI;
	m_pSec->SetScale(fPoint(100.f, -735.f));
	m_pSec->SetTextColor(RGB(255, 255, 0));
	m_pSec->SetFontSize(75);
	m_pSec->SetText(Time_sec);
	m_pSec->SetPos(fPoint(WINSIZEX / 2.f - 428.f, WINSIZEY / 2.f + 100.f));
	AddObject(m_pSec, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pcom = new CButtonUI;
	m_pcom->SetScale(fPoint(100.f, -732.f));
	m_pcom->SetTextColor(RGB(255, 255, 0));
	m_pcom->SetFontSize(75);
	m_pcom->SetText(L".");
	m_pcom->SetPos(fPoint(WINSIZEX / 2.f - 368.f, WINSIZEY / 2.f + 100.f));
	AddObject(m_pcom, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pCel = new CButtonUI;
	m_pCel->SetScale(fPoint(100.f, -735.f));
	m_pCel->SetTextColor(RGB(255, 255, 0));
	m_pCel->SetFontSize(75);
	m_pCel->SetText(Time_cel);
	m_pCel->SetPos(fPoint(WINSIZEX / 2.f - 305.f, WINSIZEY / 2.f + 100.f));
	AddObject(m_pCel, GROUP_GAMEOBJ::UI);
}
	CCameraManager::GetInst()->FadeIn(1.5f);
	CCameraManager::GetInst()->SetLookAt(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	CCameraManager::GetInst()->InitCameraPos(fPoint(WINSIZEX / 2, WINSIZEY / 2));

}

void CScene_Ending::Exit()
{
	CSoundManager::GetInst()->Stop(L"End");
	DeleteAll();
	CCollisionManager::GetInst()->Reset();
}
