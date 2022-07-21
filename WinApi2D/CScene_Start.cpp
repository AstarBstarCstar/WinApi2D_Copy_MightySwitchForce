#include "framework.h"
#include "CScene_Start.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTurtle.h"
#include "CMap.h"
#include "CBackGround.h"
#include "SwitchBlock.h"
#include "SwitchBlock2.h"
#include "CHooligan.h"
#include "CHooligan2.h"
#include "CHooligan3.h"
#include "CHooligan4.h"
#include "CHooligan5.h"
#include "CPlayerSiren.h"
#include "CExitRobot.h"
#include "CUI.h"
#include "CHUD.h"
#include "CButtonUI.h"

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
	CScene_Start::timer += fDT;
	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
		CSoundManager::GetInst()->Stop(L"Stbgm");
	}
	if (CPlayer::isGameOver)
	{
		CPlayer::isGameOver = false;
		CSoundManager::GetInst()->Stop(L"Stbgm");
		ChangeScn(GROUP_SCENE::TITLE);
	}

}
	float CScene_Start::timer;
void CScene_Start::Enter()
{
	{
		CScene_Start::timer = 0.f;
		CCameraManager::GetInst()->FadeIn(0.7f);
		CSoundManager::GetInst()->AddSound(L"Stbgm", L"sound\\MSF_ST2.wav", true, true);
		CSoundManager::GetInst()->Play(L"Stbgm");

		/*맵의 최좌측 최하단: 0,2400*/

		// 타일 로딩
		wstring path = CPathManager::GetInst()->GetContentPath();
		path += L"tile\\Level1.tile";
		LoadTile(path);



		// Monster 추가

		CMonster* pMonster = new CMonster;
		CMonster* pMon = CMonster::Create(MON_TYPE::NORMAL, fPoint(1100.f, 2000.f));
		CMonster* pCloneMonster = pMonster->Clone();
		pCloneMonster->SetPos(fPoint(500, 10350));
		AddObject(pCloneMonster, GROUP_GAMEOBJ::MONSTER);
		AddObject(pMon, GROUP_GAMEOBJ::MONSTER);

		SwitchBlock* pSwitch = new SwitchBlock;
		SwitchBlock* pSwitchC3 = pSwitch->Clone();
		SwitchBlock* pSwitchC5 = pSwitch->Clone();

		SwitchBlock2* pSwitch2 = new SwitchBlock2;
		SwitchBlock2* pSwitch2C2 = pSwitch2->Clone();
		SwitchBlock2* pSwitch2C3 = pSwitch2->Clone();

		

		pSwitch->SetPos(fPoint(352, 2270));

		pSwitchC3->SetPos(fPoint(352, 1886));
		pSwitchC5->SetPos(fPoint(736, 1886));

		pSwitch2->SetPos(fPoint(352, 2078));
		pSwitch2C2->SetPos(fPoint(736,2078));
		pSwitch2C3->SetPos(fPoint(352, 1694));
		
		AddObject(pSwitch, GROUP_GAMEOBJ::SWITCHBLOCK);
		AddObject(pSwitch2, GROUP_GAMEOBJ::SWITCHBLOCK);
		AddObject(pSwitch2C2, GROUP_GAMEOBJ::SWITCHBLOCK);
		AddObject(pSwitchC3, GROUP_GAMEOBJ::SWITCHBLOCK);
		AddObject(pSwitchC5, GROUP_GAMEOBJ::SWITCHBLOCK);
		AddObject(pSwitch2C3, GROUP_GAMEOBJ::SWITCHBLOCK);

		//CTurtle* pTurtle = new CTurtle;
		//CTurtle* pTur = CTurtle::Create(MON_TYPE::NORMAL, fPoint(1100.f, 1000.f));
		//CTurtle* pCloneTurtle = pTurtle->Clone();
		//pCloneTurtle->SetPos(fPoint(500, 1350));
		//AddObject(pCloneTurtle, GROUP_GAMEOBJ::MONSTER);
		//AddObject(pTur, GROUP_GAMEOBJ::MONSTER);

		CHooligan* pHooligan = new CHooligan;
		pHooligan->SetPos(fPoint(350, 330));
		AddObject(pHooligan, GROUP_GAMEOBJ::HOOLIGAN);
		CHooligan2* pHooligan2 = new CHooligan2;
		pHooligan2->SetPos(fPoint(1200, 1470));
		AddObject(pHooligan2, GROUP_GAMEOBJ::HOOLIGAN);
		CHooligan3* pHooligan3 = new CHooligan3;
		pHooligan3->SetPos(fPoint(3520, 720));
		AddObject(pHooligan3, GROUP_GAMEOBJ::HOOLIGAN);
		CHooligan4* pHooligan4 = new CHooligan4;
		pHooligan4->SetPos(fPoint(5900, 1510));
		AddObject(pHooligan4, GROUP_GAMEOBJ::HOOLIGAN);
		CHooligan5* pHooligan5 = new CHooligan5;
		pHooligan5->SetPos(fPoint(6687, 330));
		AddObject(pHooligan5, GROUP_GAMEOBJ::HOOLIGAN);
		CExitRobot* pExitRobot = new CExitRobot;
		pExitRobot->SetPos(fPoint(3520, 1930));
		AddObject(pExitRobot, GROUP_GAMEOBJ::HOOLIGAN);

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
		CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::TILE);
		CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::HOOLIGAN);
		CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::SWITCHBLOCK);
		CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::SWITCHBLOCK);

		// Player 추가
		CPlayer* pPlayer = new CPlayer;
		pPlayer->SetPos(fPoint(3520, 2200));
		AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
		pPlayer->RegisterPlayer();

		CHUD* m_pMin = new CHUD;
		AddObject(m_pMin, GROUP_GAMEOBJ::UI);
		m_pMin->SetPos(fPoint(WINSIZEX / 2.f, 50.f));

		CHUD* m_pMin2 = new CHUD;
		AddObject(m_pMin2, GROUP_GAMEOBJ::UI);
		m_pMin2->SetPos(fPoint(900, 60.f));

		CHUD* m_pMin3 = new CHUD;
		AddObject(m_pMin3, GROUP_GAMEOBJ::UI);
		m_pMin3->SetPos(fPoint((WINSIZEX / 2.f), 70.f));

		// Camera Look 지정
		CCameraManager::GetInst()->InitCameraPos(pPlayer->GetPos());
		CCameraManager::GetInst()->SetBoundary(fPoint(0.f, 0.f), fPoint(map->GetPos().x + map->GetScale().x, map->GetPos().y + map->GetScale().y));

		/*CCameraManager::GetInst()->SetLookAt(fPoint(WINSIZEX , WINSIZEY ));*/
		//CCameraManager::GetInst()->SetTargetObj(pPlayer);


	}
}


void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionManager::GetInst()->Reset();
}