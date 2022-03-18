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
		CCameraManager::GetInst()->FadeOut(0.5f);
		CSoundManager::GetInst()->Play(L"Click");
		CSoundManager::GetInst()->Play(L"EnterVoice");
		CSoundManager::GetInst()->Stop(L"TitleBGM");
		ChangeScn(GROUP_SCENE::SELECT);
	}
	CScene::update();
}

void CScene_Title::Enter()
{
	CSoundManager::GetInst()->AddSound(L"StartVoice", L"sound\\MSFC.wav", false);
	CSoundManager::GetInst()->AddSound(L"EnterVoice", L"sound\\IntroStart.wav", false);
	CSoundManager::GetInst()->AddSound(L"Click", L"sound\\MAKE_CHOICE.wav", false);
	CSoundManager::GetInst()->AddSound(L"TitleBGM", L"sound\\Title.wav", false,true);
	CSoundManager::GetInst()->Play(L"TitleBGM");

	CMap* Title = new CMap;
	Title->TitleLoad(L"Map_Title", L"texture\\background\\en_Title_BG.png");
	Title->SetPos(fPoint(0, 0));
	AddObject(Title, GROUP_GAMEOBJ::MAP);
	CCameraManager::GetInst()->FadeIn(2.0f);

	CSoundManager::GetInst()->Play(L"StartVoice");
}

void CScene_Title::Exit()
{
	DeleteAll();
	CCollisionManager::GetInst()->Reset();
}
