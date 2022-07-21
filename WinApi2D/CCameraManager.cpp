#include "framework.h"
#include "CCameraManager.h"
#include "CGameObject.h"
#include "CTexture.h"

CCameraManager::CCameraManager()
{
	m_fptLookAt = {};
	//m_fptCurLookAt = m_fptLookAt;
	//m_fptPrevLookAt = m_fptLookAt;
	m_fTime = 2.f;
	m_pTargetObj = nullptr;
	m_fAccTime = m_fTime;
	m_fSpeed = 877;
	m_pImg = nullptr;
}

CCameraManager::~CCameraManager()
{

}

void CCameraManager::init()
{
	m_pImg = CResourceManager::GetInst()->CreateTexture(L"CameraTexure", WINSIZEX, WINSIZEY);
}

void CCameraManager::update()
{
	if (m_bBoundary)
	{
		CheckBoundary();
	}
	else
	{
		if (m_pTargetObj != nullptr)
		{
			if (m_pTargetObj->isDead())
			{
				m_pTargetObj = nullptr;
			}
			else
			{
				if (m_bContectX)
					m_fptLookAt.x = m_pTargetObj->GetPos().x;

				if (m_bContectY)
					m_fptLookAt.y = m_pTargetObj->GetPos().y;
			}
		}
	}

	CalDiff();
}

void CCameraManager::render()
{
	if (CAM_EFFECT::NONE == m_eEffect) return;

	fCurTime += (float)fDT;
	if (fDuration < fCurTime)
	{
		m_eEffect = CAM_EFFECT::NONE;
		return;
	}

	float fRatio = fCurTime / fDuration;
	float fAlpha = 0;
	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		fAlpha = fRatio;
	}
	else if (CAM_EFFECT::FADE_IN == m_eEffect)
	{
		fAlpha = 1.f - fRatio;
	}
	else if (CAM_EFFECT::SHAKINGPLUS == m_eEffect)
	{
		int random;
		random = rand() % 30-15;
		m_fptLookAt.x += random;
	}
	else if (CAM_EFFECT::SHAKINGMINUS == m_eEffect)
	{
		int random;
		random = rand() % 30 - 15;
		m_fptLookAt.x += random;
		m_fptLookAt.y += random;
	}

	CRenderManager::GetInst()->RenderFillRectangle(
		-1.f, -1.f,
		WINSIZEX + 1, WINSIZEY + 1,
		RGB(0, 0, 0), fAlpha
	);
}



void CCameraManager::InitCameraPos(fPoint pos)
{
	m_fptPrevLookAt = pos;
}

void CCameraManager::SetLookAt(fPoint lookAt)
{
	m_fptLookAt = lookAt;
	float fMoveDist = (m_fptLookAt - m_fptPrevLookAt).Length();

	m_fTime = fMoveDist / m_fSpeed;
	m_fAccTime = 0.f;
}

void CCameraManager::FollowTargetObj(CGameObject* targetObj, bool flwX, bool flwY)
{
	m_pTargetObj = targetObj;
	m_bContectX = flwX;
	m_bContectY = flwY;
}

//void CCameraManager::SetTargetObj(CGameObject* target)
//{
//	//m_pTargetObj = target;
//}

fPoint CCameraManager::GetLookAt()
{
	return m_fptLookAt;
}

fPoint CCameraManager::GetRenderPos(fPoint objPos)
{
	return objPos - m_fptDiff;
}

fPoint CCameraManager::GetRealPos(fPoint renderPos)
{
	// 렌더링 좌표에서 차이값만큼 더해주면 절대 좌표가 나옴.
	return renderPos + m_fptDiff;
}

fPoint CCameraManager::GetLerpPoint()
{
	return m_fCollection;
}

void CCameraManager::FadeIn(float duration)
{
	m_eEffect = CAM_EFFECT::FADE_IN;
	fDuration = duration;
	fCurTime = 0.f;
}
void CCameraManager::ShakeP(float duration)
{
	m_eEffect = CAM_EFFECT::SHAKINGPLUS;
	fDuration = duration;
	fCurTime = 0.f;
}
void CCameraManager::ShakeM(float duration)
{
	m_eEffect = CAM_EFFECT::SHAKINGMINUS;
	fDuration = duration;
	fCurTime = 0.f;
}

void CCameraManager::FadeOut(float duration)
{
	m_eEffect = CAM_EFFECT::FADE_OUT;
	fDuration = duration;
	fCurTime = 0.f;
}

void CCameraManager::Scroll(fVec2 vec, float velocity)
{
	m_fptLookAt = m_fptLookAt + vec * velocity * fDT;
	m_fptCurLookAt = m_fptCurLookAt + vec * velocity * fDT;

	fPoint fptCenter = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_fptDiff = m_fptCurLookAt - fptCenter;
}

void CCameraManager::LerpDiff(fPoint targetPos)
{
	if (targetPos.x == 0 && targetPos.y == 0)
	{
		m_fCollection = m_pTargetObj->GetPos();
		return;
	}

	float x = (targetPos.x - m_pTargetObj->GetPos().x) / 2.f;
	float y = (targetPos.y - m_pTargetObj->GetPos().y) / 2.f;
	m_fCollection = fPoint(x, y);
}

void CCameraManager::CalDiff()
{
	m_fAccTime += fDT;
	fVec2 lookDir = m_fptLookAt - m_fptPrevLookAt;

	//시간이 지나면 도착한것으로 간주
	if (m_fTime <= m_fAccTime)
	{
		m_fptCurLookAt = m_fptLookAt;
	}
	else
	{
		m_fptCurLookAt = m_fptPrevLookAt + lookDir.Normalize() * m_fSpeed * fDT;
		m_fptPrevLookAt = m_fptCurLookAt;
	}

	fPoint fptCenter = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_fptDiff = m_fptCurLookAt - fptCenter;
}

void CCameraManager::CheckBoundary()
{
	if (m_pTargetObj != nullptr)
	{
		if (m_bContectX)
			m_fptLookAt.x = m_pTargetObj->GetPos().x;

		if (m_bContectY)
			m_fptLookAt.y = m_pTargetObj->GetPos().y;
	}

	if (m_fptLookAt.x - WINSIZEX / 2.f < m_fptLastLT.x)
	{
		m_fptLookAt.x = m_fptLastLT.x + WINSIZEX / 2.f;
	}

	if (m_fptLookAt.y - WINSIZEY / 2.f < m_fptLastLT.y)
	{
		m_fptLookAt.y = m_fptLastLT.y + WINSIZEY / 2.f;
	}

	if (m_fptLookAt.x + WINSIZEX / 2.f > m_fptLastRB.x)
	{
		m_fptLookAt.x = m_fptLastRB.x - WINSIZEX / 2.f;
	}

	if (m_fptLookAt.y + WINSIZEY / 2.f > m_fptLastRB.y)
	{
		m_fptLookAt.y = m_fptLastRB.y - WINSIZEY / 2.f;
	}

	float fMoveDist = (m_fptLookAt - m_fptPrevLookAt).Length();
	m_fTime = fMoveDist / m_fSpeed;
	m_fAccTime = 0;
}

void CCameraManager::SetBoundary(fPoint LT, fPoint RB)
{
	m_bBoundary = true;

	m_fptLastLT = LT;
	m_fptLastRB = RB;
}

void CCameraManager::SetBoundary(bool Boundary)
{
	m_bBoundary = Boundary;
}