
#include "framework.h"
#include "CScene_Start.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTurtle.h"
#include "CMap.h"
#include "CBackGround.h"
#include "CHooligan.h"
#include "CHooligan2.h"
#include "CHooligan3.h"
#include "CHooligan4.h"
#include "CHooligan5.h"

#include "CSound.h"
#include "CD2DImage.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
		CSoundManager::GetInst()->Stop(L"Stbgm");
	}

}


void CScene_Start::Enter()
{
	{
		CSoundManager::GetInst()->AddSound(L"Stbgm", L"sound\\MSF_ST2.wav", false, true);
		CSoundManager::GetInst()->Play(L"Stbgm");

		/*맵의 최좌측 최하단: 0,2400*/

		// 타일 로딩
		wstring path = CPathManager::GetInst()->GetContentPath();
		path += L"tile\\Level1.tile";
		LoadTile(path);

		// Player 추가
		CPlayer* pPlayer = new CPlayer;
		pPlayer->SetPos(fPoint(700, 1300));
		AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
		pPlayer->RegisterPlayer();

		// Monster 추가
		CMonster* pMonster = new CMonster;
		CMonster* pMon = CMonster::Create(MON_TYPE::NORMAL, fPoint(1100.f, 1000.f));
		CMonster* pCloneMonster = pMonster->Clone();
		pCloneMonster->SetPos(fPoint(500, 1350));
		AddObject(pCloneMonster, GROUP_GAMEOBJ::MONSTER);
		AddObject(pMon, GROUP_GAMEOBJ::MONSTER);

		//CTurtle* pTurtle = new CTurtle;
		//CTurtle* pTur = CTurtle::Create(MON_TYPE::NORMAL, fPoint(1100.f, 1000.f));
		//CTurtle* pCloneTurtle = pTurtle->Clone();
		//pCloneTurtle->SetPos(fPoint(500, 1350));
		//AddObject(pCloneTurtle, GROUP_GAMEOBJ::MONSTER);
		//AddObject(pTur, GROUP_GAMEOBJ::MONSTER);

		CHooligan* pHooligan = new CHooligan;
		pHooligan->SetPos(fPoint(950, 1000));
		AddObject(pHooligan, GROUP_GAMEOBJ::HOOLIGAN);
		CHooligan2* pHooligan2 = new CHooligan2;
		pHooligan2->SetPos(fPoint(1050, 1000));
		AddObject(pHooligan2, GROUP_GAMEOBJ::HOOLIGAN);
		CHooligan3* pHooligan3 = new CHooligan3;
		pHooligan3->SetPos(fPoint(1150, 1000));
		AddObject(pHooligan3, GROUP_GAMEOBJ::HOOLIGAN);
		CHooligan4* pHooligan4 = new CHooligan4;
		pHooligan4->SetPos(fPoint(1250, 1000));
		AddObject(pHooligan4, GROUP_GAMEOBJ::HOOLIGAN);
		CHooligan5* pHooligan5 = new CHooligan5;
		pHooligan5->SetPos(fPoint(1350, 1000));
		AddObject(pHooligan5, GROUP_GAMEOBJ::HOOLIGAN);



		CMap* map = new CMap;
		map->Load(L"Map_Start", L"texture\\map\\IncLevel1.png");
		AddObject(map, GROUP_GAMEOBJ::MAP);

		CBackGround* backGround = new CBackGround;
		backGround->Load(L"BackGround_Start", L"texture\\background\\Level01.png");
		backGround->SetPos(fPoint(-100.f, -500.f));
		AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

		CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
		CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);
		CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
		CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::HOOLIGAN);

		// Camera Look 지정
		CCameraManager::GetInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
		CCameraManager::GetInst()->SetTargetObj(pPlayer);
		//CCameraManager::GetInst()->FadeOut(1.f);
		//CCameraManager::GetInst()->FadeIn(1.f);

		// 몬스터 배치
	}
}


void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionManager::GetInst()->Reset();
}











//#include "framework.h"
//#include "CScene_Start.h"
//
//#include "CGameObject.h"
//#include "CPlayer.h"
//#include "CMonster.h"
//#include "CMap.h"
//#include "CBackGround.h"
//
//#include "CSound.h"
//#include "CD2DImage.h"
//
//CScene_Start::CScene_Start()
//{
//}
//
//CScene_Start::~CScene_Start()
//{
//}
//
//void CScene_Start::update()
//{
//	CScene::update();
//
//	if (KeyDown(VK_TAB))
//	{
//		ChangeScn(GROUP_SCENE::TOOL);
//	}
//
//	if (KeyDown('Z'))
//	{
//
//	}
//
//	if (KeyDown('X'))
//	{
//		CSoundManager::GetInst()->Stop(L"MSF_ST2");
//	}
//}
//
//void CScene_Start::Enter()
//{
//	CSoundManager::GetInst()->AddSound(L"MSF_ST2", L"sound\\MSF_ST2.wav", false, true);
//	CSoundManager::GetInst()->Play(L"MSF_ST2");
//	// Å¸ÀÏ ·Îµù
//	wstring path = CPathManager::GetInst()->GetContentPath();
//	path += L"tile\\Start.tile";
//	LoadTile(path);
//
//	// Player Ãß°¡
//	CGameObject* pPlayer = new CPlayer;
//	pPlayer->SetPos(fPoint(200, 200));
//	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
//
//	// Monster Ãß°¡
//	CMonster* pMonster = new CMonster;
//	pMonster->SetPos(fPoint(1100, 350));
//	AddObject(pMonster, GROUP_GAMEOBJ::PLAYER);
//
//	CMonster* pCloneMonster = pMonster->Clone();
//	pCloneMonster->SetPos(fPoint(500, 350));
//	AddObject(pCloneMonster, GROUP_GAMEOBJ::MONSTER);
//
//	CMap* map = new CMap;
//	map->Load(L"Map_Start", L"texture\\map\\Yoshis Island 2.png");
//	AddObject(map, GROUP_GAMEOBJ::MAP);
//
//	CBackGround* backGround = new CBackGround;
//	backGround->Load(L"BackGround_Start", L"texture\\background\\background_start.png");
//	backGround->SetPos(fPoint(-100.f, -500.f));
//	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);
//
//	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
//	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);
//	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
//
//	// Camera Look ÁöÁ¤
//	CCameraManager::GetInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
//	CCameraManager::GetInst()->SetTargetObj(pPlayer);
//	CCameraManager::GetInst()->FadeOut(1.f);
//	CCameraManager::GetInst()->FadeIn(1.f);
//}
//
//void CScene_Start::Exit()
//{
//	DeleteAll();
//
//	CCollisionManager::GetInst()->Reset();
//}