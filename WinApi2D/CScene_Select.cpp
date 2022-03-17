#include "framework.h"
#include "CScene_Select.h"
#include "CGameObject.h"
#include "Map_Start.h"
#include "CMap.h"
#include "CBackGround.h"
#include "CSound.h"
#include "CD2DImage.h"

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
		CSoundManager::getInst()->Play(L"CursorMove");
	}
	if (KeyDown(VK_DOWN))
	{
		CSoundManager::getInst()->Play(L"CursorMove");
	}
	if (KeyDown(VK_RETURN))
	{
		ChangeScn(GROUP_SCENE::START);
		CSoundManager::getInst()->Stop(L"SelectBGM");
	}
	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
	}
	if (KeyDown('B'))
	{
		ChangeScn(GROUP_SCENE::TITLE);
		CSoundManager::getInst()->Play(L"BackButton");
		CSoundManager::getInst()->Stop(L"SelectBGM");
	}
	CScene::update();
}

void CScene_Select::Enter()
{
	CSoundManager::getInst()->AddSound(L"BackButton", L"sound\\BackButton.wav", false,false);
	CSoundManager::getInst()->AddSound(L"CursorMove", L"sound\\CursorMove.wav", false, false);
	CSoundManager::getInst()->AddSound(L"SelectBGM", L"sound\\LevelSelect.wav", false, true);
	CSoundManager::getInst()->Play(L"SelectBGM");
	CMap* Select = new CMap;
	Select->TitleLoad(L"Select", L"texture\\background\\Street.png");
	Select->SetPos(fPoint(0, 0));
	AddObject(Select, GROUP_GAMEOBJ::MAP);
}

void CScene_Select::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
