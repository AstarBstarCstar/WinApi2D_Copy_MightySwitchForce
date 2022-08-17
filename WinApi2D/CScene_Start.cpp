#include "framework.h"
#include "CScene_Start.h"
#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMap.h"
#include "CBackGround.h"
#include "SwitchBlock.h"
#include "SwitchBlock2.h"
#include "CHooligan.h"
#include "CHooligan2.h"
#include "CHooligan3.h"
#include "CHooligan4.h"
#include "CHooligan5.h"
#include "CExitRobot.h"
#include "CUI.h"
#include "CHUD.h"
#include "CHolliganHUD.h"
#include "CHolliganSave.h"
#include "CButtonUI.h"
#include "CHeartHUD.h"
#include "CSound.h"
#include "CD2DImage.h"
float CScene_Start::timer;
bool CScene_Start::isStop=true;
bool CPlayer::isDead = false;
CScene_Start::CScene_Start()
{
}
short CHolliganSave::isGet = 0;
CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	if (initTimer <= 0.1f)
	{
		initTimer += fDT;
		CPlayer::holiganSave = 0;
	}
	CScene::update();

	if(isStop)
	CScene_Start::timer += fDT;

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
		CSoundManager::GetInst()->Stop(L"Stbgm");
	}
	if (CPlayer::isDead)
	{
		changeTimer += fDT;
		
		if (changeTimer>=9.0f&&!Count)
		{
			CCameraManager::GetInst()->FadeOut(1.1f);
			Count = true;
		}
		if (changeTimer >= 10.f)
		{
			changeTimer = 0.f;
			Count = false;
			CPlayer::isDead = false;
			ChangeScn(GROUP_SCENE::TITLE);
		}

	}

	temp = CScene_Start::timer;
	min = temp /60 ;
	sec = (int)temp % 60;
	cel = (int)(temp * 100) % 100;
	Time_min = std::to_wstring(min);
	Time_sec = std::to_wstring(sec);
	Time_cel = std::to_wstring(cel);
	m_pMin->SetText(Time_min);
	m_pSec->SetText(Time_sec);
	m_pCel->SetText(Time_cel);

	if (CPlayer::isGameOver)
	{
		CPlayer::isGameOver = false;
			ChangeScn(GROUP_SCENE::TITLE);
	}

}
void CScene_Start::Enter()
{
		CScene_Start::isStop = true;
		initTimer = 0.f;
		CScene_Start::timer = 0.f;
		CCameraManager::GetInst()->FadeIn(0.7f);
		CSoundManager::GetInst()->AddSound(L"Stbgm", L"sound\\MSF_ST2.wav", true, true);
		CSoundManager::GetInst()->Play(L"Stbgm");
		CSoundManager::GetInst()->Play(L"READY");
		/*맵의 최좌측 최하단: 0,2400*/

		// 타일 로딩
		wstring path = CPathManager::GetInst()->GetContentPath();
		path += L"tile\\Level1.tile";
		LoadTile(path);

		ObjectSetter();
		UISetter();
}


void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionManager::GetInst()->Reset();
}

void CScene_Start::ObjectSetter()
{
	// Monster 추가

	CMonster* pMon = CMonster::Create(MON_TYPE::NORMAL, fPoint(1100.f, 2000.f));
	AddObject(pMon, GROUP_GAMEOBJ::MONSTER);
	CMonster* pMon1 = CMonster::Create(MON_TYPE::NORMAL, fPoint(2078.f, 1500.f));
	AddObject(pMon1, GROUP_GAMEOBJ::MONSTER);
	CMonster* pMon2 = CMonster::Create(MON_TYPE::NORMAL, fPoint(2070.f, 1300.f));
	AddObject(pMon2, GROUP_GAMEOBJ::MONSTER);
	CMonster* pMon3 = CMonster::Create(MON_TYPE::NORMAL, fPoint(3230.f, 2250.f));
	AddObject(pMon3, GROUP_GAMEOBJ::MONSTER);
	pMon3->SetAnim(true);
	CMonster* pMon4 = CMonster::Create(MON_TYPE::NORMAL, fPoint(5237.f, 2280.f));
	AddObject(pMon4, GROUP_GAMEOBJ::MONSTER);
	CMonster* pMon5 = CMonster::Create(MON_TYPE::NORMAL, fPoint(5830.f, 2270.f));
	AddObject(pMon5, GROUP_GAMEOBJ::MONSTER);
	CMonster* pMon6 = CMonster::Create(MON_TYPE::NORMAL, fPoint(5670.f, 2033.f));
	AddObject(pMon6, GROUP_GAMEOBJ::MONSTER);
	CMonster* pMon7 = CMonster::Create(MON_TYPE::NORMAL, fPoint(5670.f, 1776.f));
	AddObject(pMon7, GROUP_GAMEOBJ::MONSTER);
	CMonster* pMon8 = CMonster::Create(MON_TYPE::NORMAL, fPoint(745.f, 1711.f));
	AddObject(pMon8, GROUP_GAMEOBJ::MONSTER);


	CMonster* pMon9 = CMonster::Create(MON_TYPE::NORMAL, fPoint(4595.f, 500.f));
	AddObject(pMon9, GROUP_GAMEOBJ::MONSTER);
	pMon9->SetAnim(true);
	CMonster* pMon10 = CMonster::Create(MON_TYPE::NORMAL, fPoint(3786.f, 600.f));
	AddObject(pMon10, GROUP_GAMEOBJ::MONSTER);
	pMon10->SetAnim(true);
	CMonster* pMon11 = CMonster::Create(MON_TYPE::NORMAL, fPoint(2658.f, 550.f));
	AddObject(pMon11, GROUP_GAMEOBJ::MONSTER);
	pMon11->SetAnim(true);
	CMonster* pMon12 = CMonster::Create(MON_TYPE::NORMAL, fPoint(1672.f, 738.f));
	AddObject(pMon12, GROUP_GAMEOBJ::MONSTER);
	pMon12->SetAnim(true);
	CMonster* pMon13 = CMonster::Create(MON_TYPE::NORMAL, fPoint(1304.f, 738.f));
	AddObject(pMon13, GROUP_GAMEOBJ::MONSTER);
	pMon13->SetAnim(true);

	SwitchBlock* pSwitch = new SwitchBlock;
	SwitchBlock* pSwitchC3 = pSwitch->Clone();
	SwitchBlock* pSwitchC5 = pSwitch->Clone();
	SwitchBlock* pSwitchC6 = pSwitch->Clone();
	SwitchBlock* pSwitchC7 = pSwitch->Clone();
	SwitchBlock* pSwitchC8 = pSwitch->Clone();
	SwitchBlock* pSwitchC9 = pSwitch->Clone();
	SwitchBlock* pSwitchC10 = pSwitch->Clone();
	SwitchBlock* pSwitchC11 = pSwitch->Clone();
	SwitchBlock* pSwitchC12 = pSwitch->Clone();
	SwitchBlock* pSwitchC13 = pSwitch->Clone();
	SwitchBlock* pSwitchC14 = pSwitch->Clone();
	SwitchBlock* pSwitchC15 = pSwitch->Clone();
	SwitchBlock* pSwitchC16 = pSwitch->Clone();
	SwitchBlock* pSwitchC17 = pSwitch->Clone();
	SwitchBlock* pSwitchC18 = pSwitch->Clone();
	SwitchBlock* pSwitchC19 = pSwitch->Clone();
	SwitchBlock* pSwitchC20 = pSwitch->Clone();
	SwitchBlock* pSwitchC21 = pSwitch->Clone();
	SwitchBlock* pSwitchC22 = pSwitch->Clone();
	SwitchBlock* pSwitchC23 = pSwitch->Clone();
	SwitchBlock* pSwitchC24 = pSwitch->Clone();
	SwitchBlock* pSwitchC25 = pSwitch->Clone();
	SwitchBlock* pSwitchC26 = pSwitch->Clone();
	SwitchBlock* pSwitchC27 = pSwitch->Clone();
	SwitchBlock* pSwitchC28 = pSwitch->Clone();
	SwitchBlock* pSwitchC29 = pSwitch->Clone();
	SwitchBlock* pSwitchC30 = pSwitch->Clone();
	SwitchBlock* pSwitchC31 = pSwitch->Clone();
	SwitchBlock* pSwitchC32 = pSwitch->Clone();
	SwitchBlock* pSwitchC33 = pSwitch->Clone();
	SwitchBlock* pSwitchC34 = pSwitch->Clone();
	SwitchBlock* pSwitchC35 = pSwitch->Clone();
	SwitchBlock* pSwitchC36 = pSwitch->Clone();
	SwitchBlock* pSwitchC37 = pSwitch->Clone();
	SwitchBlock* pSwitchC38 = pSwitch->Clone();
	SwitchBlock* pSwitchC39 = pSwitch->Clone();


	SwitchBlock2* pSwitch2 = new SwitchBlock2;
	SwitchBlock2* pSwitch2C2 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C3 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C6 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C7 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C8 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C9 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C10 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C11 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C12 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C13 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C14 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C15 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C16 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C17 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C18 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C19 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C21 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C22 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C23 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C24 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C26 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C27 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C28 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C29 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C30 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C31 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C32 = pSwitch2->Clone();
	SwitchBlock2* pSwitch2C33 = pSwitch2->Clone();


	pSwitch->SetPos(fPoint(352, 2270));
	pSwitchC3->SetPos(fPoint(352, 1886));
	pSwitchC5->SetPos(fPoint(736, 1886));
	pSwitchC6->SetPos(fPoint(3042, 2082));
	pSwitchC7->SetPos(fPoint(2850, 2082));
	pSwitchC8->SetPos(fPoint(2659, 2082));
	pSwitchC9->SetPos(fPoint(2465, 2082));
	pSwitchC10->SetPos(fPoint(3615, 2273));
	pSwitchC11->SetPos(fPoint(3808, 2273));
	pSwitchC12->SetPos(fPoint(1312, 2270));
	pSwitchC13->SetPos(fPoint(1504, 2270));
	pSwitchC14->SetPos(fPoint(1696, 2270));
	pSwitchC15->SetPos(fPoint(1888, 2270));
	pSwitchC16->SetPos(fPoint(2080, 2270));
	pSwitchC17->SetPos(fPoint(2272, 2270));
	pSwitchC18->SetPos(fPoint(6692, 2280));
	pSwitchC19->SetPos(fPoint(6308, 1896));
	pSwitchC20->SetPos(fPoint(6500, 1512));
	pSwitchC21->SetPos(fPoint(6500, 1128));
	pSwitchC22->SetPos(fPoint(6500, 743));
	pSwitchC23->SetPos(fPoint(4386, 930));
	pSwitchC24->SetPos(fPoint(4194, 930));
	pSwitchC25->SetPos(fPoint(3042, 930));
	pSwitchC26->SetPos(fPoint(2274, 930));
	pSwitchC27->SetPos(fPoint(1484, 930));
	pSwitchC28->SetPos(fPoint(1484, 738));
	pSwitchC29->SetPos(fPoint(600, 116));
	pSwitchC30->SetPos(fPoint(600, 308));
	pSwitchC31->SetPos(fPoint(600, 500));
	pSwitchC32->SetPos(fPoint(792, 4500));
	pSwitchC33->SetPos(fPoint(792, 500));
	pSwitchC34->SetPos(fPoint(352, 1502));
	pSwitchC35->SetPos(fPoint(544, 1502));
	pSwitchC36->SetPos(fPoint(736, 1502));
	pSwitchC37->SetPos(fPoint(352, 734));
	pSwitchC38->SetPos(fPoint(544, 734));
	pSwitchC39->SetPos(fPoint(736, 734));


	pSwitch2->SetPos(fPoint(352, 2078));
	pSwitch2C2->SetPos(fPoint(736, 2078));
	pSwitch2C3->SetPos(fPoint(352, 1694));
	pSwitch2C6->SetPos(fPoint(4578, 2082));
	pSwitch2C7->SetPos(fPoint(4386, 2082));
	pSwitch2C8->SetPos(fPoint(4192, 2082));
	pSwitch2C9->SetPos(fPoint(4000, 2082));
	pSwitch2C10->SetPos(fPoint(3232, 2273));
	pSwitch2C11->SetPos(fPoint(3424, 2273));
	pSwitch2C12->SetPos(fPoint(544, 2270));
	pSwitch2C13->SetPos(fPoint(736, 2270));
	pSwitch2C14->SetPos(fPoint(928, 2270));
	pSwitch2C15->SetPos(fPoint(1120, 2270));
	pSwitch2C16->SetPos(fPoint(6500, 2088));
	pSwitch2C17->SetPos(fPoint(6308, 1704));
	pSwitch2C18->SetPos(fPoint(6692, 1320));
	pSwitch2C19->SetPos(fPoint(6500, 936));
	pSwitch2C21->SetPos(fPoint(4578, 930));
	pSwitch2C22->SetPos(fPoint(4002, 930));
	pSwitch2C23->SetPos(fPoint(3810, 930));
	pSwitch2C24->SetPos(fPoint(2658, 930));
	pSwitch2C26->SetPos(fPoint(1100, 930));
	pSwitch2C27->SetPos(fPoint(1100, 738));
	pSwitch2C28->SetPos(fPoint(1868, 930));
	pSwitch2C29->SetPos(fPoint(1868, 738));
	pSwitch2C30->SetPos(fPoint(4770, 930));
	pSwitch2C31->SetPos(fPoint(352, 1118));
	pSwitch2C32->SetPos(fPoint(544, 1118));
	pSwitch2C33->SetPos(fPoint(736, 1118));

	AddObject(pSwitch, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C2, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC3, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC5, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C3, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC6, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC7, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC8, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC9, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC10, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC11, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC12, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC13, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC14, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC15, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC16, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC17, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC18, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC19, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC20, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC21, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC22, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC23, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC24, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC25, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC26, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC27, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC28, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC29, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC30, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC31, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC32, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC33, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC34, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC35, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC36, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC37, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC38, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitchC39, GROUP_GAMEOBJ::SWITCHBLOCK);

	AddObject(pSwitch2C6, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C7, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C8, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C9, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C10, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C11, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C12, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C13, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C14, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C15, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C16, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C17, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C18, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C19, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C21, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C22, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C23, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C24, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C26, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C27, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C28, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C29, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C30, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C31, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C32, GROUP_GAMEOBJ::SWITCHBLOCK);
	AddObject(pSwitch2C33, GROUP_GAMEOBJ::SWITCHBLOCK);

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

	// Player 추가
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(3520, 2000));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	pPlayer->RegisterPlayer();

	// Camera Look 지정
	CCameraManager::GetInst()->InitCameraPos(pPlayer->GetPos());
	CCameraManager::GetInst()->SetBoundary(fPoint(0.f, 0.f), fPoint(map->GetPos().x + map->GetScale().x, map->GetPos().y + map->GetScale().y));

	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::HOOLIGAN);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::SWITCHBLOCK);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::SWITCHBLOCK);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::MONSTER, GROUP_GAMEOBJ::SWITCHBLOCK);
}

void CScene_Start::UISetter()
{
	// UI , HUD 
	CHUD* m_pHeart = new CHUD;
	AddObject(m_pHeart, GROUP_GAMEOBJ::UI);
	m_pHeart->SetPos(fPoint(1250.f, 70.f));
	CHUD* m_pMin2 = m_pHeart->Clone();
	AddObject(m_pMin2, GROUP_GAMEOBJ::UI);
	m_pMin2->SetPos(fPoint(1370.f, 70.f));
	CHUD* m_pMin3 = m_pHeart->Clone();
	AddObject(m_pMin3, GROUP_GAMEOBJ::UI);
	m_pMin3->SetPos(fPoint(1490.f, 70.f));
	CHeartHUD* m_pfillHeart = new CHeartHUD;
	AddObject(m_pfillHeart, GROUP_GAMEOBJ::UI);


	CHolliganHUD* m_pHo = new CHolliganHUD;
	AddObject(m_pHo, GROUP_GAMEOBJ::UI);
	m_pHo->SetPos(fPoint(600.f, 70.f));
	CHolliganHUD* m_pHo1 = new CHolliganHUD;
	AddObject(m_pHo1, GROUP_GAMEOBJ::UI);
	m_pHo1->SetPos(fPoint(700.f, 70.f));
	CHolliganHUD* m_pHo2 = new CHolliganHUD;
	AddObject(m_pHo2, GROUP_GAMEOBJ::UI);
	m_pHo2->SetPos(fPoint(800.f, 70.f));
	CHolliganHUD* m_pHo3 = new CHolliganHUD;
	AddObject(m_pHo3, GROUP_GAMEOBJ::UI);
	m_pHo3->SetPos(fPoint(900.f, 70.f));
	CHolliganHUD* m_pHo4 = new CHolliganHUD;
	AddObject(m_pHo4, GROUP_GAMEOBJ::UI);
	m_pHo4->SetPos(fPoint(1000.f, 70.f));
	CHolliganSave* m_pHoli = new CHolliganSave;
	AddObject(m_pHoli, GROUP_GAMEOBJ::UI);



	m_pMin = new CButtonUI;
	m_pMin->SetScale(fPoint(100.f, -735.f));
	m_pMin->SetTextColor(RGB(0, 255, 255));
	m_pMin->SetFontSize(75);
	m_pMin->SetPos(fPoint(WINSIZEX / 2.f - 775.f, WINSIZEY / 2.f - 20.f));
	AddObject(m_pMin, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pcol = new CButtonUI;
	m_pcol->SetScale(fPoint(100.f, -735.f));
	m_pcol->SetTextColor(RGB(0, 255, 255));
	m_pcol->SetFontSize(75);
	m_pcol->SetText(L":");
	m_pcol->SetPos(fPoint(WINSIZEX / 2.f - 740.f, WINSIZEY / 2.f - 20.f));
	AddObject(m_pcol, GROUP_GAMEOBJ::UI);

	m_pSec = new CButtonUI;
	m_pSec->SetScale(fPoint(100.f, -735.f));
	m_pSec->SetTextColor(RGB(0, 255, 255));
	m_pSec->SetFontSize(75);
	m_pSec->SetPos(fPoint(WINSIZEX / 2.f - 678.f, WINSIZEY / 2.f - 20.f));
	AddObject(m_pSec, GROUP_GAMEOBJ::UI);

	CButtonUI* m_pcom = new CButtonUI;
	m_pcom->SetScale(fPoint(100.f, -732.f));
	m_pcom->SetTextColor(RGB(0, 255, 255));
	m_pcom->SetFontSize(75);
	m_pcom->SetText(L".");
	m_pcom->SetPos(fPoint(WINSIZEX / 2.f - 618.f, WINSIZEY / 2.f - 20.f));
	AddObject(m_pcom, GROUP_GAMEOBJ::UI);

	m_pCel = new CButtonUI;
	m_pCel->SetScale(fPoint(100.f, -735.f));
	m_pCel->SetTextColor(RGB(0, 255, 255));
	m_pCel->SetFontSize(75);
	m_pCel->SetPos(fPoint(WINSIZEX / 2.f - 555.f, WINSIZEY / 2.f - 20.f));
	AddObject(m_pCel, GROUP_GAMEOBJ::UI);
}