// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#pragma comment(lib, "Msimg32.lib")

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

// STL
#include <vector>
#include <map>
#include <list>

using namespace std;

// Util
#include "SingleTon.h"
#include "struct.h"
#include "Logger.h"


//========================================
//## 게임 그룹						##
//========================================

enum class GROUP_GAMEOBJ//TODO: 가려져있는 반투명 오브젝트. 스위치 눌린상태로 보여지는그룹 bool time managetfDT -> 한프레임당 시간이 짧게 걸렸
{
	DEFAULT,
	BACKGROUND,
	MAP,
	TILE,
	HOOLIGAN,
	MONSTER,
	PLAYER,

	MISSILE_PLAYER,
	MISSILE_MONSTER,

	UI,		// UI는 모든 게임오브젝트 중 최상단 Layer에 위치
	SIZE,
};

enum class GROUP_TILE
{
	NONE,
	GROUND,
	WALL,
	PLATFORM,
	SPIKE,
	SLOPE,

	SIZE,
};

enum class GROUP_SCENE
{
	TOOL,
	TITLE,
	SELECT,
	START,
	STAGE_01,
	STAGE_02,

	SIZE,
};

//========================================
//## 이벤트 타입					##
//========================================

enum class TYPE_EVENT
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_SCENE,
	CHANGE_AI_STATE,

	SIZE,
};

enum class STATE_MON
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,

	SIZE,
};

enum class MON_TYPE
{
	NORMAL,
	RANGE,

	SIZE,
};

//enum class PLAYER_STATE
//{
//	IDLE,
//	WALK,
//	ATTACK,
//	JUMP,
//	DEAD,
//};

struct tMonInfo
{
	float fSpeed;
	float fHP;
	float fRecogRange;
	float fAttRange;
	float fAtt;
};

// Core & Manager
#include "CCore.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CCollisionManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"
#include "CSoundManager.h"
#include "CRenderManager.h"

//========================================
//##			디파인문				##
//========================================

#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	1600
#define	WINSIZEY	900
#define GRAVITY	600.f
#define MAX_SPEED 600
#define UPPER 800
#define WINSTYLE	WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

#define DT				CTimeManager::GetInst()->GetDT()
#define fDT				CTimeManager::GetInst()->GetfDT()

#define Key(key)		CKeyManager::GetInst()->GetButton(key)
#define KeyUp(key)		CKeyManager::GetInst()->GetButtonUP(key)
#define KeyDown(key)	CKeyManager::GetInst()->GetButtonDOWN(key)

#define MousePos()		CKeyManager::GetInst()->GetMousePos()

#define CreateObj(pObj, group)		CEventManager::GetInst()->EventCreateObject(pObj, group)
#define DeleteObj(pObj)				CEventManager::GetInst()->EventDeleteObject(pObj)
#define ChangeScn(scene)			CEventManager::GetInst()->EventChangeScene(scene)
#define ChangeAIState(ai, state)	CEventManager::GetInst()->EventChangeAIState(ai, state)



//========================================
//## 전역변수(인스턴스, 윈도우 핸들)	##
//========================================

extern HINSTANCE hInst;
extern HWND hWnd;
