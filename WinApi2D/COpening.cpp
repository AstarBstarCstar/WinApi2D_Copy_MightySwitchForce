#include "framework.h"
#include "COpening.h"
#include <Vfw.h>
#pragma comment(lib, "Vfw32.lib")

COpening::COpening()
{
	videoTrigger = false;
}

COpening::~COpening()
{
}



void COpening::update()
{
	CScene::update();
	if (KeyDown('Z') || KeyDown('X') || MCIWndGetLength(m_Opening) <= MCIWndGetPosition(m_Opening))
	{
		ChangeScn(GROUP_SCENE::START);
	}
}

void COpening::Enter()
{
	
	Initialize();
	CCore::GetInst()->SetRender(false);
}

void COpening::Exit()
{
	MCIWndClose(m_Opening);
	DeleteAll();
	CCore::GetInst()->SetRender(true);
}


void COpening::Initialize()
{
	m_Opening = MCIWndCreate(hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, L"contents\\Opening.wmv");//TODO: 화질개선
	MoveWindow(m_Opening, 0, 0, 1600, 900, true);
	MCIWndPlay(m_Opening);
}