#include "framework.h"
#include "CHooligan3.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CIdleState.h"
#include "CTraceState.h"

CHooligan3::CHooligan3()
{
	srand(time(NULL));
	CD2DImage* m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Hooligan3", L"texture\\Animation\\Hooligan\\Host3\\Idle\\Host3_168_236.png");
	SetName(L"Hooligan3");
	SetScale(fPoint(168 * 0.7, 236 * 0.7));

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 120.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IdleHool3", m_pImg, fPoint(0, 0), fPoint(168.f, 236.f), fPoint(168.f, 0), 0.1f, 12);

	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\JUSTICESERVED1.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\JUSTICESERVED2.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\GOTCHA.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Collect", L"Sound\\COLLECTHOOLIGAN.wav", false, false);
}

CHooligan3::~CHooligan3()
{
}
void CHooligan3::OnCollisionEnter(CCollider* pOther)
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

CHooligan3* CHooligan3::Clone()
{
	return new CHooligan3(*this);
}

void CHooligan3::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::GetInst()->GetRenderPos(pos);

	component_render();
}

void CHooligan3::update()
{
	GetAnimator()->update();
	GetAnimator()->Play(L"IdleHool3");
}
