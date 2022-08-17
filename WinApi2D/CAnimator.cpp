#include "framework.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
{
	m_pOwner = nullptr;
	m_pCurAni = nullptr;
}

CAnimator::~CAnimator()
{
	// 등록되어있던 애니메이션들 지워주기
	for (map<wstring, CAnimation*>::iterator iter = m_mapAni.begin(); iter != m_mapAni.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapAni.clear();
}

void CAnimator::update()
{
	if (nullptr != m_pCurAni)
		m_pCurAni->update();
}
bool CAnimator::PlayEnd(const wstring& strName)
{
	CAnimation* pAnim = FindAnimation(strName);
	 pAnim->m_iCurFrm;
	 pAnim->m_vecAnimFrm.size();
	 if (pAnim->m_iCurFrm == pAnim->m_vecAnimFrm.size() - 1)
	 {
		 pAnim->m_iCurFrm = 0;
		 return true;
	 }

}

void CAnimator::render()
{
	if (nullptr != m_pCurAni)
		m_pCurAni->render();
}

void CAnimator::CreateAnimation(const wstring& strName, CD2DImage* pImg, fPoint leftTop, fPoint scale,
	fPoint step,fPoint size, UINT column, float duration, UINT frmCount, bool isLoop, bool bReverse)
{
	CAnimation* pAnim = FindAnimation(strName);
	
	// 이름이 똑같은 애니메이션을 넣을 때의 반응
	assert(pAnim == nullptr);

	pAnim = new CAnimation;
	pAnim->m_Count = frmCount;
	pAnim->SetName(strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(pImg, leftTop, scale, step,size, column, duration, frmCount);
	pAnim->SetLoop(isLoop);
	pAnim->m_bReverse = bReverse;

	m_mapAni.insert(make_pair(strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAni.find(strName);

	if (iter == m_mapAni.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring& strName, bool reset)
{
	m_pCurAni = FindAnimation(strName);
	//if (reset == true)
	//{
	//	m_pCurAni->SetFrame(0);
	//}
}


CGameObject* CAnimator::GetObj()
{
	return m_pOwner;
}
