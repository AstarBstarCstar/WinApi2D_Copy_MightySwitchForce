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
	// �ð� ���� > fDuration -> m_iCurFrm++
	m_fAccTime += fDT;

	if (m_fAccTime >= m_vecAnimFrm[m_iCurFrm].fDuration)
	{
		// ���� �ð� -> fDuration ��ŭ �ٽ� ���� -> 0���� �ʱ�ȭ���ٴ� ��Ȯ
		m_fAccTime -= m_vecAnimFrm[m_iCurFrm].fDuration;

		m_iCurFrm++;

		if (m_bIsLoop)
		{
			// �ִϸ��̼ǿ� ���� ���������� ó�� ���������� ���ư�
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
	// �׸� ��ġ
	fPoint fptDrawPos = pObj->GetPos();
	// ���� �׷����� �������� �ִϸ��̼�
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

void CAnimation::Create(CD2DImage* pImg,	// �ִϸ��̼��� �̹���
	fPoint leftTop,		// �ִϸ��̼� ���� ������ �»�� ��ǥ
	fPoint scale,		// �ִϸ��̼� �������� ũ��
	fPoint step,		// �ִϸ��̼� ������ �ݺ� ��ġ
	fPoint size,      // �ִϸ��̼� ������
	UINT column,		// ��� �� ����
	float duration,		// �ִϸ��̼� ������ ���� �ð�
	UINT frmCount)		// �ִϸ��̼� ������ ����
{
	m_pImg = pImg;

	tAnimFrm frm = {};
	for (UINT i = 0; i < frmCount; ++i)
	{
		frm.fDuration = duration;	// ���� �ð�
		frm.fptTexScale = size;	// �ؽ����� ũ��

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

		// leftTop + ���� ������ �̹��������� �Ÿ� * ���� ������ ī��Ʈ
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
//	// �ð� ���� > fDuration -> m_iCurFrm++
//	m_fAccTime += fDT;
//
//	if (m_fAccTime >= m_vecAnimFrm[m_iCurFrm].fDuration)
//	{
//		// ���� �ð� -> fDuration ��ŭ �ٽ� ���� -> 0���� �ʱ�ȭ���ٴ� ��Ȯ
//		m_fAccTime -= m_vecAnimFrm[m_iCurFrm].fDuration;
//
//		m_iCurFrm++;
//
//		if (m_bIsLoop)
//		{
//			// �ִϸ��̼ǿ� ���� ���������� ó�� ���������� ���ư�
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
//	// �׸� ��ġ
//	fPoint fptDrawPos = pObj->GetPos();
//	// ���� �׷����� �������� �ִϸ��̼�
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
//void CAnimation::Create(CD2DImage* pImg,	// �ִϸ��̼��� �̹���
//	fPoint leftTop,		// �ִϸ��̼� ���� ������ �»�� ��ǥ
//	fPoint scale,		// �ִϸ��̼� �������� ũ��
//	fPoint step,		// �ִϸ��̼� ������ �ݺ� ��ġ
//	UINT column,		// ��� �� ����
//	float duration,		// �ִϸ��̼� ������ ���� �ð�
//	UINT frmCount)		// �ִϸ��̼� ������ ����
//{
//	m_pImg = pImg;
//
//	tAnimFrm frm = {};
//	for (UINT i = 0; i < frmCount; ++i)
//	{
//		frm.fDuration = duration;	// ���� �ð�
//		frm.fptTexScale = scale;	// �ؽ����� ũ��
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
//		// leftTop + ���� ������ �̹��������� �Ÿ� * ���� ������ ī��Ʈ
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
////void CAnimation::Create(CD2DImage* img,     // �ִϸ��̼��� �̹���
////                        fPoint lt,          // �ִϸ��̼� ���� �������� �»�� ��ǥ
////                        fPoint slice,       // �ִϸ��̼� �������� ũ��
////                        fPoint step,        // �ִϸ��̼� �������� �ݺ� ��ġ
////                        float duration,     // �ִϸ��̼� ������ ���ӽð�
////                        UINT frmCount)      // �ִϸ��̼� ������ ����
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
//void CAnimation::Create(CD2DImage* pImg,	// �ִϸ��̼��� �̹���
//    fPoint leftTop,		// �ִϸ��̼� ���� ������ �»�� ��ǥ
//    fPoint scale,		// �ִϸ��̼� �������� ũ��
//    fPoint step,		// �ִϸ��̼� ������ �ݺ� ��ġ
//    UINT column,		// ��� �� ����
//    float duration,		// �ִϸ��̼� ������ ���� �ð�
//    UINT frmCount)		// �ִϸ��̼� ������ ����
//{
//    m_pImg = pImg;
//
//    tAnimFrm frm = {};
//    for (UINT i = 0; i < frmCount; ++i)
//    {
//        frm.fDuration = duration;	// ���� �ð�
//        frm.fptTexScale = scale;	// �ؽ����� ũ��
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
//        // leftTop + ���� ������ �̹��������� �Ÿ� * ���� ������ ī��Ʈ
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
