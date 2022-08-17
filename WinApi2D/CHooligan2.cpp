#include "framework.h"
#include "CHooligan2.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"

CHooligan2::CHooligan2()
{
	srand(time(NULL));
	CD2DImage* m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Hooligan2", L"texture\\Animation\\Hooligan\\Host2\\Idle\\Host2_260_260.png");
	SetName(L"Hooligan2");
	SetScale(fPoint(260 * 0.7, 260 * 0.7));

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 120.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IdleHool2", m_pImg, fPoint(0, 0), fPoint(260.f, 260.f), fPoint(260.f, 0),fPoint(260.f, 260.f),0, 0.1f, 25,true,true);

	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\JUSTICESERVED1.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\JUSTICESERVED2.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\GOTCHA.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Collect", L"Sound\\COLLECTHOOLIGAN.wav", false, false);
}

CHooligan2::~CHooligan2()
{
}
void CHooligan2::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		CGameObject::holiganSave++;
		Count++;
	}
	if (Count > 1)
	{
		int R = rand() % 3;
		DeleteObj(this);
		CSoundManager::GetInst()->Play(L"Collect");

		if (CGameObject::holiganSave > 5)
			return;

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

CHooligan2* CHooligan2::Clone()
{
	return new CHooligan2(*this);
}

void CHooligan2::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::GetInst()->GetRenderPos(pos);

	component_render();
}

void CHooligan2::update()
{

	if (CGameObject::Switching != true)
	{
		GetAnimator()->update();
		GetAnimator()->Play(L"IdleHool2");
	}

	else if (CGameObject::Switching == true)
	{
	}
}
