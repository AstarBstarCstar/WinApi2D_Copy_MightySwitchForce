#include "framework.h"
#include "CGameObject.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CGameObject::CGameObject()
{
	m_fptPos = {};
	m_fptScale = {};
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_bAlive = true;
}

CGameObject::CGameObject(const CGameObject& other)
{
	m_strName	= other.m_strName;
	m_fptPos	= other.m_fptPos;
	m_fptScale	= other.m_fptScale;
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_bAlive	= true;

	if (nullptr != other.m_pCollider)
	{
		m_pCollider = new CCollider(*other.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (nullptr != other.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*other.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}

CGameObject::~CGameObject()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}
	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
	}
}

void CGameObject::SetPos(fPoint pos)
{
	m_fptPos = pos;
}

void CGameObject::SetScale(fPoint scale)
{
	m_fptScale = scale;
}

void CGameObject::SetName(wstring name)
{
	m_strName = name;
}

fPoint CGameObject::GetPos()
{
	return m_fptPos;
}

fPoint CGameObject::GetScale()
{
	return m_fptScale;
}

wstring CGameObject::GetName()
{
	return m_strName;
}

bool CGameObject::isDead()
{
	return !m_bAlive;
}

void CGameObject::SetDead()
{
	m_bAlive = false;
}

void CGameObject::finalupdate()
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->finalupdate();
	}
}

void CGameObject::render()
{
	// 절대 위치를 넘기고, 랜더링 위치를 받아옴
	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(m_fptPos);

	// 카메라를 기준으로 그려져야하는 위치
	CRenderManager::GetInst()->RenderRectangle(
		fptRenderPos.x - m_fptScale.x / 2,
		fptRenderPos.y - m_fptScale.y / 2,
		fptRenderPos.x + m_fptScale.x / 2,
		fptRenderPos.y + m_fptScale.y / 2);

	component_render();
}

void CGameObject::component_render()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render();
	}
	if (nullptr != m_pCollider)
	{
		m_pCollider->render();
	}
}

void CGameObject::debug_render()
{

	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(m_pCollider->GetFinalPos());

	CRenderManager::GetInst()->RenderText(m_strName,
		fptRenderPos.x*1.3 - m_fptScale.x,
		fptRenderPos.y*1.3 - m_fptScale.y,
		fptRenderPos.x + m_fptScale.x,
		fptRenderPos.y,
		20, RGB(255, 0, 0));

	WCHAR posX[10] = {};
	WCHAR posY[10] = {};
	swprintf_s(posX, L"%.f", m_pCollider->GetFinalPos().x);
	swprintf_s(posY, L"%.f", m_pCollider->GetFinalPos().y);
	wstring strObjPos = L"(";
	strObjPos += posX;
	strObjPos += L", ";
	strObjPos += posY;
	strObjPos += L")";


	CRenderManager::GetInst()->RenderText(strObjPos,
		fptRenderPos.x + 150.f,
		(fptRenderPos.y-150) - m_fptScale.y / 2.f,
		fptRenderPos.x + m_fptScale.x + 50.f,
		fptRenderPos.y,
		13, RGB(255, 0, 0));


	if (nullptr != m_pAnimator && nullptr != m_pAnimator->m_pCurAni)
	{
		wstring strAnim = L"";
		strAnim += m_pAnimator->m_pCurAni->GetName();

		CRenderManager::GetInst()->RenderText(strAnim,
			fptRenderPos.x +150.f,
			fptRenderPos.y - m_fptScale.y / 2.f,
			fptRenderPos.x + m_fptScale.x + 50.f,
			fptRenderPos.y,
			13, RGB(255, 0, 0));
	}
}

CCollider* CGameObject::GetCollider()
{
	return m_pCollider;
}

void CGameObject::CreateCollider()
{
	m_pCollider = new CCollider();
	m_pCollider->m_pOwner = this;
}

CAnimator* CGameObject::GetAnimator()
{
	return m_pAnimator;
}

void CGameObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}
