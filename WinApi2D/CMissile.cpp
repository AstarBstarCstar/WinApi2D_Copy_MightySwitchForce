#include "framework.h"
#include "CMissile.h"
#include "CCollider.h"
#include "CTile.h"
CMissile* CMissile::Clone()
{
	return new CMissile(*this);
}

CMissile::CMissile()
{
	SetScale(fPoint(70.f, 35.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"Missile_Player");

	CreateCollider();
	GetCollider()->SetScale(fPoint(50.f, 25.f));
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

	//if (pos.x < 0 || pos.x > 30000
	//	|| pos.y < 0 || pos.y >30000)
	//	DeleteObj(this);
}

void CMissile::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(pos);

	CRenderManager::GetInst()->RenderEllipse(
		fptRenderPos.x,
		fptRenderPos.y,
		scale.x / 2.f,
		scale.y / 2.f);

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
