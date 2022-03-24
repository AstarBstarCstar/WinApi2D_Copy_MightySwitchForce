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
	GetAnimator()->CreateAnimation(L"IdleHool", m_pActSW, fPoint(0, 0), fPoint(192.f, 192.f), fPoint(192.f, 0), 1.f, 1);

	GetAnimator()->CreateAnimation(L"IdleHool", m_pUnActSW, fPoint(0, 0), fPoint(192.f, 192.f), fPoint(192.f, 0), 1.f, 1);

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
