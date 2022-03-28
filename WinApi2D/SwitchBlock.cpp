#include "framework.h"
#include "SwitchBlock.h"
#include "framework.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "SwitchBlock.h"

SwitchBlock::SwitchBlock()
{
	CD2DImage* m_pActSW = CResourceManager::GetInst()->LoadD2DImage(L"ACT_SW", L"texture\\Object\\SwitchBlock\\SwitchBlock.png");
	CD2DImage* m_pUnActSW = CResourceManager::GetInst()->LoadD2DImage(L"UNACT_SW", L"texture\\Object\\SwitchBlock\\SwitchBlock_unAct.png");
	CSoundManager::GetInst()->AddSound(L"Switching", L"sound\\Switch.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Flip", L"sound\\Flip.wav", false, false);
	SetName(L"SwitchBlock");
	SetScale(fPoint(192 * 0.7, 192 * 0.7));

	CreateCollider();
	GetCollider()->SetScale(fPoint(100.f, 100.f));

	CreateAnimator();
	//GetAnimator()->CreateAnimation(L"IdleHool", m_pActSW, fPoint(0, 0), fPoint(192.f, 192.f), fPoint(192.f, 0), 1.f, 1);

	//GetAnimator()->CreateAnimation(L"IdleHool", m_pUnActSW, fPoint(0, 0), fPoint(192.f, 192.f), fPoint(192.f, 0), 1.f, 1);

	SW = 0;
}

SwitchBlock::~SwitchBlock()
{
}

void SwitchBlock::update()
{
}

void SwitchBlock::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::GetInst()->GetRenderPos(pos);

	component_render();
}

void SwitchBlock::Switch()
{
	if (SW == 0)
	{
		SW = 1;
	}
	else if (SW == 1)
	{
		SW = 0;
	}
	CSoundManager::GetInst()->Play(L"Switching");
	CSoundManager::GetInst()->Play(L"Flip");
}
//TODO:애니메이션 개편하기
//TODO:스위치 블럭 충돌처리
//TODO++:x y 좌표 나오게 디버그 모드 만들기
//#include "framework.h"
//#include "CPlatform.h"
//#include "CTexture.h"
//#include "CCollider.h"
//
//CPlatform::CPlatform()
//{
//	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Platform_Floor", L"texture\\Map\\TutorialScene\\Floor\\brotherhood_floor.png");
//
//	InitObject(fPoint(627.f, 370.f), fPoint(403.f, 110.f));
//
//	CreateCollider();
//	GetCollider()->SetFinalPos(GetPos());
//	GetCollider()->SetOffsetPos(fPoint(0.f, 60.f));
//	GetCollider()->SetScale(fPoint(GetScale().x * 2.f, GetScale().y - 10.f));
//}
//
//CPlatform::~CPlatform()
//{
//}
//
//CPlatform* CPlatform::Clone()
//{
//	return new CPlatform(*this);
//}
//
//void CPlatform::update()
//{
//}
//
//void CPlatform::render()
//{
//	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(GetPos());
//
//	CRenderManager::GetInst()->RenderFrame(
//		m_pImg,
//		fptRenderPos.x - GetScale().x,
//		fptRenderPos.y - GetScale().y * 1.3f,
//		fptRenderPos.x + GetScale().x,
//		fptRenderPos.y + GetScale().y,
//		0.f, 0.f,
//		GetScale().x, GetScale().y
//	);
//
//	component_render();
//}