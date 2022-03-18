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
	}
	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
	}
	if (KeyDown('B'))
	{
		ChangeScn(GROUP_SCENE::TITLE);
		CSoundManager::GetInst()->Play(L"BackButton");
		CSoundManager::GetInst()->Stop(L"SelectBGM");
	}
	CScene::update();
}

void CScene_Select::Enter()
{
	CSoundManager::GetInst()->AddSound(L"BackButton", L"sound\\BackButton.wav", false,false);
	CSoundManager::GetInst()->AddSound(L"CursorMove", L"sound\\CursorMove.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"SelectBGM", L"sound\\LevelSelect.wav", false, true);
	CSoundManager::GetInst()->Play(L"SelectBGM");
	CMap* Select = new CMap;
	Select->TitleLoad(L"Select", L"texture\\background\\Street.png");
	Select->SetPos(fPoint(0, 0));
	AddObject(Select, GROUP_GAMEOBJ::MAP);
}

void CScene_Select::Exit()
{
	DeleteAll();

	CCollisionManager::GetInst()->Reset();
}
