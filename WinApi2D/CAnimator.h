#pragma once

class CGameObject;
class CAnimation;
class CD2DImage;

class CAnimator
{
	friend class CGameObject;

private:
	map<wstring, CAnimation*>	m_mapAni;
	CAnimation*					m_pCurAni;
	CGameObject*				m_pOwner;

public:
	CAnimator();
	~CAnimator();

	void update();
	bool PlayEnd(const wstring& strName);
	void render();

	void CreateAnimation(const wstring& strName, CD2DImage* pImg, fPoint leftTop, fPoint scale,
		fPoint step,fPoint size, UINT column, float duration, UINT frmCount, bool isLoop, bool bReverse);
	CAnimation* FindAnimation(const wstring& strName);
	void Play(const wstring& strName, bool reset = false);

	CGameObject* GetObj();
};

