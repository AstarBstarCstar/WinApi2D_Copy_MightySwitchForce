#include "framework.h"
#include "CSceneManager.h"
#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CScene_Title.h"
#include "CScene_Select.h"
#include "COpening.h"
#include "CScene_Ending.h"

CSceneManager::CSceneManager()
{
	// ?? ???? ?ʱ?ȭ
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		m_arrScene[i] = nullptr;
	}
	m_pCurScene = nullptr;
}

CSceneManager::~CSceneManager()
{
	// ?? ???? ????
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneManager::ChangeScene(GROUP_SCENE scene)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)scene];
	m_pCurScene->Enter();
}

void CSceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSceneManager::render()
{
	m_pCurScene->render();
}

void CSceneManager::init()
{
	m_arrScene[(size_t)GROUP_SCENE::START] = new CScene_Start;
	m_arrScene[(size_t)GROUP_SCENE::START]->SetName(L"Start_Scene");

	m_arrScene[(size_t)GROUP_SCENE::OPENING] = new COpening;
	m_arrScene[(size_t)GROUP_SCENE::OPENING]->SetName(L"Opening_Scene");

	m_arrScene[(size_t)GROUP_SCENE::TITLE] = new CScene_Title;
	m_arrScene[(size_t)GROUP_SCENE::TITLE]->SetName(L"Title_Scene");

	m_arrScene[(size_t)GROUP_SCENE::SELECT] = new CScene_Select;
	m_arrScene[(size_t)GROUP_SCENE::SELECT]->SetName(L"Select_Scene");

	m_arrScene[(size_t)GROUP_SCENE::TOOL] = new CScene_Tool;
	m_arrScene[(size_t)GROUP_SCENE::TOOL]->SetName(L"Tool_Scene");

	m_arrScene[(size_t)GROUP_SCENE::END] = new CScene_Ending;
	m_arrScene[(size_t)GROUP_SCENE::END]->SetName(L"End_Scene");

	m_pCurScene = m_arrScene[(size_t)GROUP_SCENE::TITLE];
	m_pCurScene->Enter();
}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
