#pragma once
#include "CScene.h"

class CD2DImage;

class CScene_Tool : public CScene
{
private:
	CD2DImage* m_pMap;

	HWND m_hWnd;
	UINT m_iIdx;
	GROUP_TILE m_gTile;
	float m_velocity;

	UINT m_iTileX;
	UINT m_iTileY;

public:
	CScene_Tool();
	~CScene_Tool();

	virtual void update();
	virtual void render();
	virtual void Enter();
	virtual void Exit();

	void LoadTile(const wstring& strPath);
	void CreateTile(UINT xSize, UINT ySize);
	void SetIdx(UINT idx);
	void SetTileIdx();		// ���콺�� ��ȣ�ۿ��ؼ� Ÿ���� �ٲ�.
	void SetGroup(GROUP_TILE group);
	void SetTileGroup();

	void SaveTile(const wstring& strPath);
	void SaveTileData();
	void LoadTileData();
private:
	void PrintTileLine();
	void PrintTileGroup();
};

