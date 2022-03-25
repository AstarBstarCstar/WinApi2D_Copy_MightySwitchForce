#include "framework.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CGameObject.h"
#include "CTexture.h"

CAnimation::CAnimation()
{
	m_pAnimator = nullptr;
	m_strAnimName = L"";
	m_pImg = nullptr;
	m_iCurFrm = 0;
	m_fAccTime = 0.f;
	m_bIsLoop = false;
	m_fCurAnimDuration = 0.f;
}

CAnimation::~CAnimation()
{
}

void CAnimation::SetName(const wstring& strName)
{
	m_strAnimName = strName;
}

const wstring& CAnimation::GetName()
{
	return m_strAnimName;
}

void CAnimation::SetFrame(int frmIndex)
{
	m_iCurFrm = frmIndex;
}

tAnimFrm& CAnimation::GetFrame(int frmIndex)
{
	return m_vecAnimFrm[frmIndex];
}

void CAnimation::update()
{
	// 시간 축적 > fDuration -> m_iCurFrm++
	m_fAccTime += fDT;

	if (m_fAccTime >= m_vecAnimFrm[m_iCurFrm].fDuration)
	{
		// 축적 시간 -> fDuration 만큼 다시 빼줌 -> 0으로 초기화보다는 정확
		m_fAccTime -= m_vecAnimFrm[m_iCurFrm].fDuration;

		m_iCurFrm++;

		if (m_bIsLoop)
		{
			// 애니메이션에 끝에 도달했으면 처음 프레임으로 돌아감
			m_iCurFrm %= m_vecAnimFrm.size();
		}
		else
		{
			if (m_iCurFrm == m_vecAnimFrm.size())
			{
				m_iCurFrm = (int)m_vecAnimFrm.size() - 1;

				if (m_fCurAnimDuration <= m_fAccTime)
					m_iCurFrm = 0;
			}
		}
	}
}

void CAnimation::render()
{
	CGameObject* pObj = m_pAnimator->GetObj();
	// 그릴 위치
	fPoint fptDrawPos = pObj->GetPos();
	// 현재 그려야할 프레임의 애니메이션
	tAnimFrm animFrm = m_vecAnimFrm[m_iCurFrm];

	fptDrawPos = fptDrawPos + animFrm.fptOffset;

	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(fptDrawPos);
	fPoint fptScale = pObj->GetScale();

	if (animFrm.fptTexScale.x > fptScale.x)
	{
		fptScale.x = animFrm.fptTexScale.x * 1.0f;
	}
	if (animFrm.fptTexScale.y > fptScale.y)
	{
		fptScale.y = animFrm.fptTexScale.y * 1.0f;
	}

	if (m_bReverse)
	{
		CRenderManager::GetInst()->RenderRevFrame(
			m_pImg,
			fptRenderPos.x - fptScale.x / 2.f,
			fptRenderPos.y - fptScale.y / 2.f,
			fptRenderPos.x + fptScale.x / 2.f,
			fptRenderPos.y + fptScale.y / 2.f,
			animFrm.fptLeftTop.x,
			animFrm.fptLeftTop.y,
			animFrm.fptLeftTop.x + animFrm.fptTexScale.x,
			animFrm.fptLeftTop.y + animFrm.fptTexScale.y
		);
	}
	else
	{
		CRenderManager::GetInst()->RenderFrame(
			m_pImg,
			fptRenderPos.x - fptScale.x / 2.f,
			fptRenderPos.y - fptScale.y / 2.f,
			fptRenderPos.x + fptScale.x / 2.f,
			fptRenderPos.y + fptScale.y / 2.f,
			animFrm.fptLeftTop.x,
			animFrm.fptLeftTop.y,
			animFrm.fptLeftTop.x + animFrm.fptTexScale.x,
			animFrm.fptLeftTop.y + animFrm.fptTexScale.y
		);
	}
}

void CAnimation::Create(CD2DImage* pImg,	// 애니메이션의 이미지
	fPoint leftTop,		// 애니메이션 시작 프레임 좌상단 좌표
	fPoint scale,		// 애니메이션 프레임의 크기
	fPoint step,		// 애니메이션 프레임 반복 위치
	fPoint size,      // 애니메이션 사이즈
	UINT column,		// 행당 열 갯수
	float duration,		// 애니메이션 프레임 지속 시간
	UINT frmCount)		// 애니메이션 프레임 개수
{
	m_pImg = pImg;

	tAnimFrm frm = {};
	for (UINT i = 0; i < frmCount; ++i)
	{
		frm.fDuration = duration;	// 지속 시간
		frm.fptTexScale = size;	// 텍스쳐의 크기

		UINT count = i;
		if (count != 0 && column != 0 && count % column == 0)
		{
			count = 0;

			leftTop = fPoint(0.f, leftTop.y + scale.y);
		}
		else if (count != 0 && column != 0)
		{
			count %= column;
		}

		// leftTop + 다음 프레임 이미지까지의 거리 * 현재 프레임 카운트
		frm.fptLeftTop = leftTop + step * count;

		m_vecAnimFrm.push_back(frm);
	}

	m_fCurAnimDuration += duration * frmCount;
}

void CAnimation::SetLoop(bool isLoop)
{
	m_bIsLoop = isLoop;
}

bool CAnimation::GetReverse()
{
	return m_bReverse;
}

float CAnimation::GetAnimDuration()
{
	return m_fCurAnimDuration;
}


//#include "framework.h"
//#include "CAnimation.h"
//#include "CAnimator.h"
//#include "CGameObject.h"
//#include "CTexture.h"
//
//CAnimation::CAnimation()
//{
//	m_pAnimator = nullptr;
//	m_strAnimName = L"";
//	m_pImg = nullptr;
//	m_iCurFrm = 0;
//	m_fAccTime = 0.f;
//	m_bIsLoop = false;
//	m_fCurAnimDuration = 0.f;
//}
//
//CAnimation::~CAnimation()
//{
//}
//
//void CAnimation::SetName(const wstring& strName)
//{
//	m_strAnimName = strName;
//}
//
//const wstring& CAnimation::GetName()
//{
//	return m_strAnimName;
//}
//
//void CAnimation::SetFrame(int frmIndex)
//{
//	m_iCurFrm = frmIndex;
//}
//
//tAnimFrm& CAnimation::GetFrame(int frmIndex)
//{
//	return m_vecAnimFrm[frmIndex];
//}
//
//void CAnimation::update()
//{
//	// 시간 축적 > fDuration -> m_iCurFrm++
//	m_fAccTime += fDT;
//
//	if (m_fAccTime >= m_vecAnimFrm[m_iCurFrm].fDuration)
//	{
//		// 축적 시간 -> fDuration 만큼 다시 빼줌 -> 0으로 초기화보다는 정확
//		m_fAccTime -= m_vecAnimFrm[m_iCurFrm].fDuration;
//
//		m_iCurFrm++;
//
//		if (m_bIsLoop)
//		{
//			// 애니메이션에 끝에 도달했으면 처음 프레임으로 돌아감
//			m_iCurFrm %= m_vecAnimFrm.size();
//		}
//		else
//		{
//			if (m_iCurFrm == m_vecAnimFrm.size())
//			{
//				m_iCurFrm = (int)m_vecAnimFrm.size() - 1;
//
//				if (m_fCurAnimDuration <= m_fAccTime)
//					m_iCurFrm = 0;
//			}
//		}
//	}
//}
//
//void CAnimation::render()
//{
//	CGameObject* pObj = m_pAnimator->GetObj();
//	// 그릴 위치
//	fPoint fptDrawPos = pObj->GetPos();
//	// 현재 그려야할 프레임의 애니메이션
//	tAnimFrm animFrm = m_vecAnimFrm[m_iCurFrm];
//
//	fptDrawPos = fptDrawPos + animFrm.fptOffset;
//
//	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(fptDrawPos);
//	fPoint fptScale = pObj->GetScale();
//
//	if (animFrm.fptTexScale.x > fptScale.x)
//	{
//		fptScale.x = animFrm.fptTexScale.x * 2.f;
//	}
//	if (animFrm.fptTexScale.y > fptScale.y)
//	{
//		fptScale.y = animFrm.fptTexScale.y * 2.f;
//	}
//
//	if (m_bReverse)
//	{
//		CRenderManager::GetInst()->RenderRevFrame(
//			m_pImg,
//			fptRenderPos.x - fptScale.x / 2.f,
//			fptRenderPos.y - fptScale.y / 2.f,
//			fptRenderPos.x + fptScale.x / 2.f,
//			fptRenderPos.y + fptScale.y / 2.f,
//			animFrm.fptLeftTop.x,
//			animFrm.fptLeftTop.y,
//			animFrm.fptLeftTop.x + animFrm.fptTexScale.x,
//			animFrm.fptLeftTop.y + animFrm.fptTexScale.y
//		);
//	}
//	else
//	{
//		CRenderManager::GetInst()->RenderFrame(
//			m_pImg,
//			fptRenderPos.x - fptScale.x / 2.f,
//			fptRenderPos.y - fptScale.y / 2.f,
//			fptRenderPos.x + fptScale.x / 2.f,
//			fptRenderPos.y + fptScale.y / 2.f,
//			animFrm.fptLeftTop.x,
//			animFrm.fptLeftTop.y,
//			animFrm.fptLeftTop.x + animFrm.fptTexScale.x,
//			animFrm.fptLeftTop.y + animFrm.fptTexScale.y
//		);
//	}
//}
//
//void CAnimation::Create(CD2DImage* pImg,	// 애니메이션의 이미지
//	fPoint leftTop,		// 애니메이션 시작 프레임 좌상단 좌표
//	fPoint scale,		// 애니메이션 프레임의 크기
//	fPoint step,		// 애니메이션 프레임 반복 위치
//	UINT column,		// 행당 열 갯수
//	float duration,		// 애니메이션 프레임 지속 시간
//	UINT frmCount)		// 애니메이션 프레임 개수
//{
//	m_pImg = pImg;
//
//	tAnimFrm frm = {};
//	for (UINT i = 0; i < frmCount; ++i)
//	{
//		frm.fDuration = duration;	// 지속 시간
//		frm.fptTexScale = scale;	// 텍스쳐의 크기
//
//		UINT count = i;
//		if (count != 0 && column != 0 && count % column == 0)
//		{
//			count = 0;
//
//			leftTop = fPoint(0.f, leftTop.y + scale.y);
//		}
//		else if (count != 0 && column != 0)
//		{
//			count %= column;
//		}
//
//		// leftTop + 다음 프레임 이미지까지의 거리 * 현재 프레임 카운트
//		frm.fptLeftTop = leftTop + step * count;
//
//		m_vecAnimFrm.push_back(frm);
//	}
//
//	m_fCurAnimDuration += duration * frmCount;
//}
//
//void CAnimation::SetLoop(bool isLoop)
//{
//	m_bIsLoop = isLoop;
//}
//
//bool CAnimation::GetReverse()
//{
//	return m_bReverse;
//}
//
//float CAnimation::GetAnimDuration()
//{
//	return m_fCurAnimDuration;
//}
//
//
//
////#include "framework.h"
////#include "CAnimation.h"
////#include "CAnimator.h"
////#include "CGameObject.h"
////#include "CTexture.h"
////
////CAnimation::CAnimation()
////{
////    m_strName = L"";
////    m_pAnimator = nullptr;
////    m_pImg = nullptr;
////    m_iCurFrm = 0;
////    m_fAccTime = 0;
////}
////
////CAnimation::CAnimation(const CAnimation& pOther)
////{
////    m_strName = pOther.m_strName;
////    for (int i = 0; i < pOther.m_vecFrm.size(); i++)
////    {
////        m_vecFrm.push_back(pOther.m_vecFrm[i]);
////    }
////    m_iCurFrm = pOther.m_iCurFrm;
////    m_fAccTime = pOther.m_fAccTime;
////    m_bReverse = pOther.m_bReverse;
////
////    m_pAnimator = nullptr;
////    m_pImg = pOther.m_pImg;
////}
////
////CAnimation::~CAnimation()
////{
////}
////
////void CAnimation::SetName(const wstring& strName)
////{
////    m_strName = strName;
////}
////
////const wstring& CAnimation::GetName()
////{
////    return m_strName;
////}
////
////void CAnimation::SetFrame(int frmIndex)
////{
////    m_iCurFrm = frmIndex;
////}
////
////tAniFrm& CAnimation::GetFrame(int frmIndex)
////{
////    return m_vecFrm[frmIndex];
////}
////
////void CAnimation::update()
////{
////    m_fAccTime += fDT;
////
////    if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
////    {
////        m_iCurFrm++;
////        m_iCurFrm %= m_vecFrm.size();
////        m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;
////    }
////}
////
////void CAnimation::render()
////{
////    CGameObject* pObj = m_pAnimator->GetObj();
////    fPoint fptPos = pObj->GetPos();
////    fPoint fptScale = pObj->GetScale();
////    tAniFrm frm = m_vecFrm[m_iCurFrm];
////
////    fptPos = fptPos + frm.fptOffset;
////    fptPos = CCameraManager::GetInst()->GetRenderPos(fptPos);
////
////
////    if (m_bReverse)
////    {
////        CRenderManager::GetInst()->RenderRevFrame(
////            m_pImg,
////            fptPos.x - fptScale.x / 2.f,
////            fptPos.y - fptScale.y / 2.f,
////            fptPos.x + fptScale.x / 2.f,
////            fptPos.y + fptScale.y / 2.f,
////            frm.fptLT.x,
////            frm.fptLT.y,
////            frm.fptLT.x + frm.fptSlice.x,
////            frm.fptLT.y + frm.fptSlice.y
////        );
////    }
////    else
////    {
////        CRenderManager::GetInst()->RenderFrame(
////            m_pImg,
////            fptPos.x - fptScale.x / 2.f,
////            fptPos.y - fptScale.y / 2.f,
////            fptPos.x + fptScale.x / 2.f,
////            fptPos.y + fptScale.y / 2.f,
////            frm.fptLT.x,
////            frm.fptLT.y,
////            frm.fptLT.x + frm.fptSlice.x,
////            frm.fptLT.y + frm.fptSlice.y
////        );
////    }
////
////}
//
////void CAnimation::Create(CD2DImage* img,     // 애니메이션의 이미지
////                        fPoint lt,          // 애니메이션 시작 프레임의 좌상단 좌표
////                        fPoint slice,       // 애니메이션 프레임의 크기
////                        fPoint step,        // 애니메이션 프레임의 반복 위치
////                        float duration,     // 애니메이션 프레임 지속시간
////                        UINT frmCount)      // 애니메이션 프레임 갯수
////{
////    m_pImg = img;
////
////    tAniFrm frm = {};
////    for (UINT i = 0; i < frmCount; i++)
////    {
////        frm.fDuration = duration;
////        frm.fptSlice = slice;
////        frm.fptLT = lt + step * i;
////
////        m_vecFrm.push_back(frm);
////    }
////}
//void CAnimation::Create(CD2DImage* pImg,	// 애니메이션의 이미지
//    fPoint leftTop,		// 애니메이션 시작 프레임 좌상단 좌표
//    fPoint scale,		// 애니메이션 프레임의 크기
//    fPoint step,		// 애니메이션 프레임 반복 위치
//    UINT column,		// 행당 열 갯수
//    float duration,		// 애니메이션 프레임 지속 시간
//    UINT frmCount)		// 애니메이션 프레임 개수
//{
//    m_pImg = pImg;
//
//    tAnimFrm frm = {};
//    for (UINT i = 0; i < frmCount; ++i)
//    {
//        frm.fDuration = duration;	// 지속 시간
//        frm.fptTexScale = scale;	// 텍스쳐의 크기
//
//        UINT count = i;
//        if (count != 0 && column != 0 && count % column == 0)
//        {
//            count = 0;
//
//            leftTop = fPoint(0.f, leftTop.y + scale.y);
//        }
//        else if (count != 0 && column != 0)
//        {
//            count %= column;
//        }
//
//        // leftTop + 다음 프레임 이미지까지의 거리 * 현재 프레임 카운트
//        frm.fptLeftTop = leftTop + step * count;
//
//        m_vecAnimFrm.push_back(frm);
//    }
//
//    m_fCurAnimDuration += duration * frmCount;
//}
//
//void CAnimation::SetLoop(bool isLoop)
//{
//    m_bIsLoop = isLoop;
//}
//
//bool CAnimation::GetReverse()
//{
//    return m_bReverse;
//}
//
//float CAnimation::GetAnimDuration()
//{
//    return m_fCurAnimDuration;
//}
