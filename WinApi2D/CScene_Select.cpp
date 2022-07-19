#include "framework.h"
#include "CScene_Select.h"
#include "CGameObject.h"
#include "Map_Start.h"
#include "CMap.h"
#include "CBackGround.h"
#include "CSound.h"
#include "CD2DImage.h"
#include "CButtonUI.h"

CScene_Select::CScene_Select()
{
	m_isChanged = false;
}

CScene_Select::~CScene_Select()
{
}

void CScene_Select::update()
{
	timer += fDT;
	if (KeyDown(VK_UP))
	{
		CSoundManager::GetInst()->Play(L"CursorMove");
	}
	if (KeyDown(VK_DOWN))
	{
		CSoundManager::GetInst()->Play(L"CursorMove");
	}
	if (KeyDown('A'))
	{
		m_isChanged = true;
		timer = 0.f;
		CCameraManager::GetInst()->FadeOut(0.63f);
		CSoundManager::GetInst()->Play(L"LevelSelected");
	}
	if (KeyDown('B'))
	{
		ChangeScn(GROUP_SCENE::TITLE);
		CSoundManager::GetInst()->Play(L"BackButton");
		CSoundManager::GetInst()->Stop(L"SelectBGM");
	}
	if (m_isChanged)
	{
		if (timer >= 0.62f)
		{
			timer = 0;
			ChangeScn(GROUP_SCENE::OPENING);
			CSoundManager::GetInst()->Stop(L"SelectBGM");
			m_isChanged = false;
		}
	}
	CScene::update();
}
void ClickINC(DWORD_PTR, DWORD_PTR)
{
	CCameraManager::GetInst()->FadeOut(0.7f);
	CSoundManager::GetInst()->Stop(L"SelectBGM");
	CSoundManager::GetInst()->Play(L"LevelSelected");

	ChangeScn(GROUP_SCENE::OPENING);
}

void ClickQuit(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::TITLE);
	CSoundManager::GetInst()->Play(L"BackButton");
	CSoundManager::GetInst()->Stop(L"SelectBGM");
}

void CScene_Select::Enter()
{
	CCameraManager::GetInst()->FadeIn(0.7f);
	CSoundManager::GetInst()->AddSound(L"BackButton", L"sound\\BackButton.wav", false,false);
	CSoundManager::GetInst()->AddSound(L"CursorMove", L"sound\\CursorMove.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"LevelSelected", L"sound\\LevelSelected.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"SelectBGM", L"sound\\LevelSelect.wav", false, true);
	CSoundManager::GetInst()->Play(L"SelectBGM");
	CMap* Select = new CMap;
	Select->Load(L"Select", L"texture\\background\\Street.png");
	Select->SetPos(fPoint(0, 0));
	AddObject(Select, GROUP_GAMEOBJ::MAP);

	CButtonUI* m_pINCIDENT01 = new CButtonUI;
	m_pINCIDENT01->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT01->SetText(L"INCIDENT .01");
	m_pINCIDENT01->SetFontSize(25);
	m_pINCIDENT01->SetPos(fPoint(WINSIZEX / 2.f + 445.f, WINSIZEY / 2.f -255.f));
	m_pINCIDENT01->SetClickedCallBack(ClickINC, 0, 0);
	AddObject(m_pINCIDENT01, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pINCIDENT02 = new CButtonUI;
	m_pINCIDENT02->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT02->SetText(L"LOCKED!");
	m_pINCIDENT02->SetFontSize(25);
	m_pINCIDENT02->SetPos(fPoint(WINSIZEX / 2.f + 445.f, WINSIZEY / 2.f - 165.f));
	AddObject(m_pINCIDENT02, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pINCIDENT03 = new CButtonUI;
	m_pINCIDENT03->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT03->SetText(L"LOCKED!");
	m_pINCIDENT03->SetFontSize(25);
	m_pINCIDENT03->SetPos(fPoint(WINSIZEX / 2.f + 445.f, WINSIZEY / 2.f - 75.f));
	AddObject(m_pINCIDENT03, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pINCIDENT04 = new CButtonUI;
	m_pINCIDENT04->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT04->SetText(L"LOCKED!");
	m_pINCIDENT04->SetFontSize(25);
	m_pINCIDENT04->SetPos(fPoint(WINSIZEX / 2.f +445.f, WINSIZEY / 2.f +17.f));
	AddObject(m_pINCIDENT04, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pINCIDENT05 = new CButtonUI;
	m_pINCIDENT05->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT05->SetText(L"LOCKED!");
	m_pINCIDENT05->SetFontSize(25);
	m_pINCIDENT05->SetPos(fPoint(WINSIZEX / 2.f + 445.f, WINSIZEY / 2.f +109.f));
	AddObject(m_pINCIDENT05, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pINCIDENT06 = new CButtonUI;
	m_pINCIDENT06->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT06->SetText(L"LOCKED!");
	m_pINCIDENT06->SetFontSize(25);
	m_pINCIDENT06->SetPos(fPoint(WINSIZEX / 2.f +445.f, WINSIZEY / 2.f +200.f));
	AddObject(m_pINCIDENT06, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pPAR = new CButtonUI;
	m_pPAR->SetScale(fPoint(200.f, 50.f));
	m_pPAR->SetTextColor(RGB(255, 255, 0));
	m_pPAR->SetFontSize(75);
	m_pPAR->SetText(L"01:50.00");
	m_pPAR->SetPos(fPoint(WINSIZEX / 2.f - 405.f, WINSIZEY / 2.f +185.f));
	AddObject(m_pPAR, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pBestTime = new CButtonUI;
	m_pBestTime->SetScale(fPoint(200.f, 50.f));
	m_pBestTime->SetTextColor(RGB(255, 255, 0));
	m_pBestTime->SetFontSize(75);
	m_pBestTime->SetText(L"--:--.--");
	m_pBestTime->SetPos(fPoint(WINSIZEX / 2.f -405.f, WINSIZEY / 2.f + 100.f));
	AddObject(m_pBestTime, GROUP_GAMEOBJ::UI);

	CButtonUI* Back = new CButtonUI;
	Back->SetScale(fPoint(100.f, 50.f));
	Back->SetText(L"BACK");
	Back->SetPos(fPoint(WINSIZEX / 2.f - 655.f, WINSIZEY / 2.f +345.f));
	Back->SetClickedCallBack(ClickQuit, 0, 0);
	AddObject(Back, GROUP_GAMEOBJ::UI);

	CButtonUI* SelectButton = new CButtonUI;
	SelectButton->SetScale(fPoint(100.f, 50.f));
	SelectButton->SetText(L"SELECT");
	SelectButton->SetPos(fPoint(WINSIZEX / 2.f +530.f, WINSIZEY / 2.f + 345.f));
	SelectButton->SetClickedCallBack(ClickINC, 0, 0);
	AddObject(SelectButton, GROUP_GAMEOBJ::UI);

}

void CScene_Select::Exit()
{
	DeleteAll();

	CCollisionManager::GetInst()->Reset();
}
