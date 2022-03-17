#include "framework.h"
#include "CScene_Title.h"
#include "CGameObject.h"
#include "Map_Start.h"
#include "CMap.h"
#include "CBackGround.h"
#include "CSound.h"
#include "CD2DImage.h"

CScene_Title::CScene_Title()
{
}

CScene_Title::~CScene_Title()
{
}

void CScene_Title::update()
{
	if (KeyDown('A'))
	{
		CCameraManager::getInst()->FadeOut(0.5f);
		CSoundManager::getInst()->Play(L"Click");
		CSoundManager::getInst()->Play(L"EnterVoice");
		CSoundManager::getInst()->Stop(L"TitleBGM");
		ChangeScn(GROUP_SCENE::SELECT);
	}
	CScene::update();
}

void CScene_Title::Enter()
{
	CSoundManager::getInst()->AddSound(L"StartVoice", L"sound\\MSFC.wav", false);
	CSoundManager::getInst()->AddSound(L"EnterVoice", L"sound\\IntroStart.wav", false);
	CSoundManager::getInst()->AddSound(L"Click", L"sound\\MAKE_CHOICE.wav", false);
	CSoundManager::getInst()->AddSound(L"TitleBGM", L"sound\\Title.wav", false,true);
	CSoundManager::getInst()->Play(L"TitleBGM");

	CMap* Title = new CMap;
	Title->TitleLoad(L"Map_Title", L"texture\\background\\en_Title_BG.png");
	Title->SetPos(fPoint(0, 0));
	AddObject(Title, GROUP_GAMEOBJ::MAP);
	CCameraManager::getInst()->FadeIn(2.0f);
	Sleep(500);
	CSoundManager::getInst()->Play(L"StartVoice");
}

void CScene_Title::Exit()
{
	DeleteAll();
	CCollisionManager::getInst()->Reset();
}
