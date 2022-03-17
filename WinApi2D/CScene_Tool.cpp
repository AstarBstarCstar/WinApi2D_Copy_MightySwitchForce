#include "framework.h"
#include "CScene_Tool.h"
#include "CTile.h"
#include "resource.h"
#include "CScene.h"
#include "CD2DImage.h"
#include "commdlg.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CButtonUI.h"

INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CScene_Tool::CScene_Tool()
{
	m_pMap = nullptr;

	m_hWnd = 0;
	m_iIdx = 0;
	m_gTile = GROUP_TILE::GROUND;
	m_velocity = 200;
	m_iTileX = 0;
	m_iTileY = 0;
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::START);
	}

	if (Key('A'))
	{
		CCameraManager::getInst()->Scroll(fVec2(-1, 0),  m_velocity);
	}
	if (Key('D'))
	{
		CCameraManager::getInst()->Scroll(fVec2(1, 0), m_velocity);
	}
	if (Key('W'))
	{
		CCameraManager::getInst()->Scroll(fVec2(0, -1), m_velocity);
	}
	if (Key('S'))
	{
		CCameraManager::getInst()->Scroll(fVec2(0, 1), m_velocity);
	}

	SetTileIdx();
	SetTileGroup();
}

void CScene_Tool::render()
{
	CScene::render();

	PrintTileLine();
	PrintTileGroup();
}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::START);
}

void ButtonClicked(DWORD_PTR, DWORD_PTR)
{
	int a = 0;
}

void CScene_Tool::Enter()
{
	CreateTile(5, 5);

	m_hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILEBOX), hWnd, TileWinProc);
	ShowWindow(m_hWnd, SW_SHOW);

	//// UI ����
	//CPanelUI* pPanelUI = new CPanelUI();
	//pPanelUI->SetScale(fPoint(200.f, 80.f));
	//pPanelUI->SetPos(fPoint(WINSIZEX - pPanelUI->GetScale().x, 0.f));		// UI�� ī�޶��� ��ġ�� ������� ���� ��ǥ�� ���� ����
	//AddObject(pPanelUI, GROUP_GAMEOBJ::UI);

	//CButtonUI* pButtonUI = new CButtonUI();
	//pButtonUI->SetScale(fPoint(100.f, 40.f));
	//pButtonUI->SetClickedCallBack(ButtonClicked, 0, 0);	// �߰� ������ �ʿ�� ���� �ʴ� ����
	//pButtonUI->SetPos(fPoint(10.f, 10.f));
	//pPanelUI->AddChild(pButtonUI);

	//// UI ����
	//CPanelUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + fPoint(-500.f, 0.f));
	//AddObject(pClonePanel, GROUP_GAMEOBJ::UI);

	//CButtonUI* pBtnUI = new CButtonUI();
	//pBtnUI->SetScale(fPoint(100.f, 100.f));
	//pBtnUI->SetPos(fPoint(100.f, 100.f));
	//pBtnUI->SetClickedCallBack(ChangeScene, 0, 0);
	//AddObject(pBtnUI, GROUP_GAMEOBJ::UI);

	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}

void CScene_Tool::Exit()
{
	EndDialog(m_hWnd, IDOK);
	DeleteAll();
}

void CScene_Tool::SetIdx(UINT idx)
{
	m_iIdx = idx;
}

void CScene_Tool::SetTileIdx()
{
	if (Key(VK_LBUTTON) || Key(VK_RBUTTON))
	{
		fPoint fptMousePos = MousePos();
		fptMousePos = CCameraManager::getInst()->GetRealPos(fptMousePos);

		int iTileX = m_iTileX;
		int iTileY = m_iTileY;

		int iCol = (int)fptMousePos.x / CTile::SIZE_TILE;
		int iRow = (int)fptMousePos.y / CTile::SIZE_TILE;

		if (fptMousePos.x < 0.f || iTileX <= iCol ||
			fptMousePos.y < 0.f || iTileY <= iRow)
		{
			return;		// Ÿ���� ���� ��ġ ����
		}

		UINT iIdx = iRow * iTileX + iCol;
		const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
		if (Key(VK_LBUTTON))
			((CTile*)vecTile[iIdx])->SetImgIdx(m_iIdx);
		else if (Key(VK_RBUTTON))
			((CTile*)vecTile[iIdx])->SetImgIdx(0);
	}
}

void CScene_Tool::SetGroup(GROUP_TILE group)
{
	m_gTile = group;
}

void CScene_Tool::SetTileGroup()
{
	if (Key(VK_LBUTTON) || Key(VK_RBUTTON))
	{
		fPoint fptMousePos = MousePos();
		fptMousePos = CCameraManager::getInst()->GetRealPos(fptMousePos);

		int iTileX = m_iTileX;
		int iTileY = m_iTileY;

		int iCol = (int)fptMousePos.x / CTile::SIZE_TILE;
		int iRow = (int)fptMousePos.y / CTile::SIZE_TILE;

		if (fptMousePos.x < 0.f || iTileX <= iCol ||
			fptMousePos.y < 0.f || iTileY <= iRow)
		{
			return;		// Ÿ���� ���� ��ġ ����
		}

		UINT iIdx = iRow * iTileX + iCol;
		const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
		((CTile*)vecTile[iIdx])->SetImgIdx(m_iIdx);
		if (Key(VK_LBUTTON))
			((CTile*)vecTile[iIdx])->SetGroup(m_gTile);
		else if (Key(VK_RBUTTON))
			((CTile*)vecTile[iIdx])->SetGroup(GROUP_TILE::NONE);
	}
}

void CScene_Tool::CreateTile(UINT xSize, UINT ySize)
{
	DeleteGroup(GROUP_GAMEOBJ::TILE);

	m_iTileX = xSize;
	m_iTileY = ySize;

	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");

	for (UINT y = 0; y < ySize; y++)
	{
		for (UINT x = 0; x < xSize; x++)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(fPoint((float)(x * CTile::SIZE_TILE), (float)(y * CTile::SIZE_TILE)));
			pTile->SetX(x);
			pTile->SetY(y);
			pTile->SetD2DImage(pImg);
			AddObject(pTile, GROUP_GAMEOBJ::TILE);
		}
	}
}

void CScene_Tool::SaveTile(const wstring& strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"wb");		// w : write, b : binary
	assert(pFile);

	UINT xCount = m_iTileX;
	UINT yCount = m_iTileY;
	UINT tileCount = 0;

	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		CTile* pTile = (CTile*)vecTile[i];
		if (0 != pTile->GetIdx() || GROUP_TILE::NONE != pTile->GetGroup())
			tileCount++;
	}

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	fwrite(&tileCount, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		CTile* pTile = (CTile*)vecTile[i];
		if (0 != pTile->GetIdx())
			((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CScene_Tool::LoadTile(const wstring& strPath)
{
	DeleteGroup(GROUP_GAMEOBJ::TILE);

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;
	UINT tileCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	fread(&tileCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");
	CTile* pTile = new CTile;

	for (UINT i = 0; i < tileCount; i++)
	{
		pTile->Load(pFile);
		UINT iIdx = pTile->GetY() * xCount + pTile->GetX();
		((CTile*)vecTile[iIdx])->SetX(pTile->GetX());
		((CTile*)vecTile[iIdx])->SetY(pTile->GetY());
		((CTile*)vecTile[iIdx])->SetImgIdx(pTile->GetIdx());
		((CTile*)vecTile[iIdx])->SetGroup(pTile->GetGroup());
	}

	fclose(pFile);
}

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ����ü ������.
	ofn.hwndOwner = hWnd;					// �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName); // lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // ���� ����
	ofn.nFilterIndex = 0; // �⺻ ���� ����. 0�� all�� �ʱ� ���õ�. ó����.
	ofn.lpstrFileTitle = nullptr; // Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0; // Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = CPathManager::getInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // �ʱ���. �츮�� Ÿ�� �����Ұű� ������, content->tile ��η� �ص���.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ��Ÿ��

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // ����ü ������.
	ofn.hwndOwner = hWnd; // �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName); // lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // ���� ����
	ofn.nFilterIndex = 0; // �⺻ ���� ����. 0�� all�� �ʱ� ���õ�. ó����.
	ofn.lpstrFileTitle = nullptr; // Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0; // Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = CPathManager::getInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // �ʱ���. �츮�� Ÿ�� �����Ұű� ������, content->tile ��η� �ص���.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ��Ÿ��

	if (GetOpenFileName(&ofn))
	{
		LoadTile(szName);
	}
}

void CScene_Tool::PrintTileLine()
{
	fPoint pos = CCameraManager::getInst()->GetLookAt();
	pos = pos - fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);

	// ������ ���
	for (UINT y = 0; y <= m_iTileX; y++)
	{
		CRenderManager::getInst()->RenderLine(
			fPoint(0 - pos.x, y * CTile::SIZE_TILE - pos.y),
			fPoint(CTile::SIZE_TILE * m_iTileX - pos.x, y * CTile::SIZE_TILE - pos.y)
		);
	}

	// ������ ���
	for (UINT x = 0; x <= m_iTileY; x++)
	{
		CRenderManager::getInst()->RenderLine(
			fPoint(x * CTile::SIZE_TILE - pos.x, 0 - pos.y),
			fPoint(x * CTile::SIZE_TILE - pos.x, CTile::SIZE_TILE * m_iTileY - pos.y)
		);
	}
}

void CScene_Tool::PrintTileGroup()
{
	const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
	CTile* pTile;

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		pTile = (CTile*)vecTile[i];
		if (GROUP_TILE::GROUND == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(255, 0, 0)
			);
		}
		else if (GROUP_TILE::WALL == pTile->GetGroup())
		{
			CRenderManager::getInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(0, 255, 0)
			);
		}
	}
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->SaveTileData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadTileData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON_SIZE)
		{
			int x = GetDlgItemInt(hDlg, IDC_EDIT_SIZEX, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDIT_SIZEY, nullptr, false);

			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_GAMEOBJ::TILE);
			pToolScene->CreateTile(x, y);
		}
		else if (LOWORD(wParam) == IDC_BUTTON_TILE)
		{
			int m_iIdx = GetDlgItemInt(hDlg, IDC_EDIT_TILE, nullptr, false);

			CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->SetIdx(m_iIdx);
		}
		break;
	}
	return (INT_PTR)FALSE;
}