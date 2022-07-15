#include "framework.h"
#include "COpening.h"
#include <Vfw.h>
#pragma comment(lib, "Vfw32.lib")

COpening::COpening()
{
	isVideoFinished = false;
}

COpening::~COpening()
{
}



void COpening::update()
{
	CScene::update();
	if (KeyDown('Z') || KeyDown('X') || MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo))
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
	CCore::GetInst()->SetRender(true);
	MCIWndClose(m_hVideo);
	DeleteAll();
}


void COpening::Initialize()
{
	// 비디오 윈도우 핸들에 세팅 및 재생
	m_hVideo = MCIWndCreate(hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD
		, L"contents\\Opening.wmv");
	MoveWindow(m_hVideo, 0, 0, WINSIZEX, WINSIZEY, false);

	MCIWndPlay(m_hVideo);
}