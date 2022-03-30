#include "framework.h"
#include "SwitchBlock.h"
#include "framework.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "SwitchBlock.h"
/*push*/
SwitchBlock::SwitchBlock()
{
	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"SWBlock", L"texture\\Object\\SwitchBlock\\SwitchBlock.png");
	CSoundManager::GetInst()->AddSound(L"Switching", L"sound\\Switch.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Flip", L"sound\\Flip.wav", false, false);
	SetName(L"SwitchBlock");
	SetScale(fPoint(192, 192));

	CreateCollider();
	GetCollider()->SetScale(fPoint(190.f, 190.f));

	m_bSW = true;
	m_fAlp = 100.f;
}

SwitchBlock::~SwitchBlock()
{
}

SwitchBlock* SwitchBlock::Clone()
{
	return new SwitchBlock(*this);
}

void SwitchBlock::update()
{
	if (KeyDown('C'))
	{
		CSoundManager::GetInst()->Play(L"Switching");
		CSoundManager::GetInst()->Play(L"Flip");
		if (m_fAlp >= 100)//활성화 된 스위치블럭 상태에서 c 누를시
		{
			m_bSW = false;
			m_fAlp = 50;
		}
		else//활성화 안 된 스위치블럭 상태에서 c 누를시
		{
			m_bSW = true;
			m_fAlp = 100;
		}
	}
	//swPress 변화를 시작하는 변수 지속시간 몇초동안? 0.5~0.7
	if (m_bSW = false)//블럭을 반투명하게 하는 처리
	{
	}
	else
	{
	}
}

void SwitchBlock::render()
{
	//fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(GetPos());
	fPoint scale = GetScale();
	fPoint pos = CCameraManager::GetInst()->GetRenderPos(GetPos());
	CRenderManager::GetInst()->RenderImage(m_pImg, pos.x - scale.x*0.5, pos.y - scale.y*0.5, pos.x + scale.x*0.5, pos.y + scale.y*0.5, m_fAlp*0.01);//그냥 값넣으면 하면 원래 크기의 두배를 렌더 하지 않아?

	component_render();
}

void SwitchBlock::Switch()
{
	if (m_bSW == 0)
	{
		m_bSW = 1;
	}
	else if (m_bSW == 1)
	{
		m_bSW = 0;
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
//InitObject(fPoint(627.f, 370.f), fPoint(403.f, 110.f));
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