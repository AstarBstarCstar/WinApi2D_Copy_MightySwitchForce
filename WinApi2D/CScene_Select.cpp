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
}

CScene_Select::~CScene_Select()
{
}

void CScene_Select::update()
{
	if (KeyDown(VK_UP))
	{
		CSoundManager::GetInst()->Play(L"CursorMove");
	}
	if (KeyDown(VK_DOWN))
	{
		CSoundManager::GetInst()->Play(L"CursorMove");
	}
	if (KeyDown(VK_RETURN))
	{
		ChangeScn(GROUP_SCENE::START);
		CSoundManager::GetInst()->Stop(L"SelectBGM");
		CSoundManager::GetInst()->Play(L"LevelSelected");
	}
	if (KeyDown('B'))
	{
		ChangeScn(GROUP_SCENE::TITLE);
		CSoundManager::GetInst()->Play(L"BackButton");
		CSoundManager::GetInst()->Stop(L"SelectBGM");
	}
	CScene::update();
}
void ClickINC(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::START);
	CSoundManager::GetInst()->Stop(L"SelectBGM");
	CSoundManager::GetInst()->Play(L"LevelSelected");
}

void ClickQuit(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::TITLE);
	CSoundManager::GetInst()->Play(L"BackButton");
	CSoundManager::GetInst()->Stop(L"SelectBGM");
}

void CScene_Select::Enter()
{
	CSoundManager::GetInst()->AddSound(L"BackButton", L"sound\\BackButton.wav", false,false);
	CSoundManager::GetInst()->AddSound(L"CursorMove", L"sound\\CursorMove.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"LevelSelected", L"sound\\LevelSelected.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"SelectBGM", L"sound\\LevelSelect.wav", false, true);
	CSoundManager::GetInst()->Play(L"SelectBGM");
	CMap* Select = new CMap;
	Select->TitleLoad(L"Select", L"texture\\background\\Street.png");
	Select->SetPos(fPoint(0, 0));
	AddObject(Select, GROUP_GAMEOBJ::MAP);

	CButtonUI* m_pINCIDENT01 = new CButtonUI;
	m_pINCIDENT01->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT01->SetText(L"I N C I D E N T   . 0 1");
	m_pINCIDENT01->SetPos(fPoint(WINSIZEX / 2.f + 335.f, WINSIZEY / 2.f -210.f));
	m_pINCIDENT01->SetClickedCallBack(ClickINC, 0, 0);
	AddObject(m_pINCIDENT01, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pINCIDENT02 = new CButtonUI;
	m_pINCIDENT02->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT02->SetText(L"L O C K E D !");
	m_pINCIDENT02->SetPos(fPoint(WINSIZEX / 2.f + 335.f, WINSIZEY / 2.f + 162.f));
	AddObject(m_pINCIDENT02, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pINCIDENT03 = new CButtonUI;
	m_pINCIDENT03->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT03->SetText(L"L O C K E D !");
	m_pINCIDENT03->SetPos(fPoint(WINSIZEX / 2.f + 335.f, WINSIZEY / 2.f + 87.f));
	AddObject(m_pINCIDENT03, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pINCIDENT04 = new CButtonUI;
	m_pINCIDENT04->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT04->SetText(L"L O C K E D !");
	m_pINCIDENT04->SetPos(fPoint(WINSIZEX / 2.f +335.f, WINSIZEY / 2.f +15.f));
	AddObject(m_pINCIDENT04, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pINCIDENT05 = new CButtonUI;
	m_pINCIDENT05->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT05->SetText(L"L O C K E D !");
	m_pINCIDENT05->SetPos(fPoint(WINSIZEX / 2.f + 335.f, WINSIZEY / 2.f - 60.f));
	AddObject(m_pINCIDENT05, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pINCIDENT06 = new CButtonUI;
	m_pINCIDENT06->SetScale(fPoint(200.f, 50.f));
	m_pINCIDENT06->SetText(L"L O C K E D !");
	m_pINCIDENT06->SetPos(fPoint(WINSIZEX / 2.f +335.f, WINSIZEY / 2.f - 135.f));
	AddObject(m_pINCIDENT06, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pPAR = new CButtonUI;
	m_pPAR->SetScale(fPoint(200.f, 50.f));
	m_pPAR->SetText(L"N / A");
	m_pPAR->SetPos(fPoint(WINSIZEX / 2.f - 375.f, WINSIZEY / 2.f +145.f));
	AddObject(m_pPAR, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pBestTime = new CButtonUI;
	m_pBestTime->SetScale(fPoint(200.f, 50.f));
	m_pBestTime->SetText(L"N / A");
	m_pBestTime->SetPos(fPoint(WINSIZEX / 2.f -375.f, WINSIZEY / 2.f + 80.f));
	AddObject(m_pBestTime, GROUP_GAMEOBJ::UI);

	CButtonUI* Back = new CButtonUI;
	Back->SetScale(fPoint(100.f, 50.f));
	Back->SetText(L"B A C K");
	Back->SetPos(fPoint(WINSIZEX / 2.f - 505.f, WINSIZEY / 2.f +275.f));
	Back->SetClickedCallBack(ClickQuit, 0, 0);
	AddObject(Back, GROUP_GAMEOBJ::UI);

}

void CScene_Select::Exit()
{
	DeleteAll();

	CCollisionManager::GetInst()->Reset();
}
