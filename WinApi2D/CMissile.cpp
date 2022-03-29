#include "framework.h"
#include "CMissile.h"
#include "CCollider.h"
#include "CTile.h"
#include "CAnimator.h"
#include "CAnimation.h"
CMissile* CMissile::Clone()
{
	return new CMissile(*this);
}

CMissile::CMissile()
{
	CD2DImage* m_Bullet = CResourceManager::GetInst()->LoadD2DImage(L"Bullet", L"texture\\Object\\Bullet_112_60.png");
	CD2DImage* m_BulletHit = CResourceManager::GetInst()->LoadD2DImage(L"BulletHit", L"texture\\Object\\BulletHit_180_176.png");
	SetScale(fPoint(70.f, 35.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"Missile_Player");

	CreateCollider();
	GetCollider()->SetScale(fPoint(50.f, 25.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Bullet", m_Bullet, fPoint(0.f, 0.f), fPoint(112.f, 60.f), fPoint(112.f, 0.f), fPoint(112.f, 60.f), 0, 0.065f, 3, true, false);
	GetAnimator()->CreateAnimation(L"R_Bullet", m_Bullet, fPoint(0.f, 0.f), fPoint(112.f, 60.f), fPoint(112.f, 0.f), fPoint(112.f, 60.f), 0, 0.065f, 3, true, true);
	GetAnimator()->CreateAnimation(L"BulletHit", m_BulletHit, fPoint(0.f, 0.f), fPoint(180.f, 176.f), fPoint(180.f, 0.f), fPoint(180.f, 176.f), 0, 0.065f, 7, true, false);
}

CMissile::~CMissile()
{
}
 
void CMissile::update()
{
	fPoint pos = GetPos();

	pos.x += m_fSpeed * m_fvDir.x * fDT;
	pos.y += m_fSpeed * m_fvDir.y * fDT;

	SetPos(pos);
	GetAnimator()->update();

	if (m_fvDir.x == 1)
	{
		GetAnimator()->Play(L"Bullet");
	}
	else
	{
		GetAnimator()->Play(L"R_Bullet");
	}
}

void CMissile::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(pos);
	component_render();
}

void CMissile::SetDir(fVec2 vec)
{
	m_fvDir = vec.Normalize();
}

void CMissile::SetDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CMissile::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	CTile* pTile = (CTile*)pOtherObj;

	if (pOtherObj->GetName() == L"Monster")
	{
			DeleteObj(this);
	}
	else if (pOtherObj->GetName() == L"Tile")
	{
			DeleteObj(this);
	}
}
