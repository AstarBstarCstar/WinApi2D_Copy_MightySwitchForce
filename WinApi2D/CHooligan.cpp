#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CHooligan.h"

CHooligan::CHooligan()
{
	CD2DImage* m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Hooligan", L"texture\\Animation\\Hooligan\\Host1\\Idle\\Host1_144_240.png");
	SetName(L"Hooligan");
	SetScale(fPoint(100, 200));

	CreateCollider();
	GetCollider()->SetScale(fPoint(70.f, 180.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IdleHool", m_pImg, fPoint(0, 0), fPoint(144.f, 240.f), fPoint(144.f, 0), 0.1f, 20);
	
}

CHooligan::~CHooligan()
{
}

CHooligan* CHooligan::Clone()
{
	return new CHooligan(*this);
}

void CHooligan::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::GetInst()->GetRenderPos(pos);

	component_render();
}

void CHooligan::update()
{
	GetAnimator()->Play(L"IdleHool");
}
