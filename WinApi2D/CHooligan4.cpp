#include "framework.h"
#include "CHooligan4.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CIdleState.h"
#include "CTraceState.h"

CHooligan4::CHooligan4()
{
	srand(time(NULL));
	CD2DImage* m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Hooligan4", L"texture\\Animation\\Hooligan\\Host4\\Idle\\Host4_220_200.png");
	SetName(L"Hooligan4");
	SetScale(fPoint(220 * 0.7, 200 * 0.7));

	CreateCollider();
	GetCollider()->SetScale(fPoint(50.f, 120.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IdleHool4", m_pImg, fPoint(0, 0), fPoint(220.f, 200.f), fPoint(220.f, 0), fPoint(220.f, 200.f),0, 0.1f, 24,true,true);

	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\JUSTICESERVED1.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\JUSTICESERVED2.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\GOTCHA.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Collect", L"Sound\\COLLECTHOOLIGAN.wav", false, false);
}

CHooligan4::~CHooligan4()
{
}

CHooligan4* CHooligan4::Clone()
{
	return new CHooligan4(*this);
}
void CHooligan4::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		Count++;
	}
	if (Count > 1)
	{
		int R = rand() % 3;
		DeleteObj(this);
		CSoundManager::GetInst()->Play(L"Collect");
		switch (R)
		{
		case 0:
		{
			CSoundManager::GetInst()->Play(L"JusticeServed1");
			break;
		}
		case 1:
		{
			CSoundManager::GetInst()->Play(L"JusticeServed2");
			break;
		}
		case 2:
		{
			CSoundManager::GetInst()->Play(L"Gotcha");
			break;
		}
		}
	}
}

void CHooligan4::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::GetInst()->GetRenderPos(pos);

	component_render();
}

void CHooligan4::update()
{
	GetAnimator()->update();
	GetAnimator()->Play(L"IdleHool4");
}
