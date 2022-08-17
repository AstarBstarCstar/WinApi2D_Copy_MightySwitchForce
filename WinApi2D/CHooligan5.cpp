#include "framework.h"
#include "CHooligan5.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"

CHooligan5::CHooligan5()
{
	srand(time(NULL));
	CD2DImage* m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Hooligan5", L"texture\\Animation\\Hooligan\\Host5\\Idle\\Host5_164_240.png");
	SetName(L"Hooligan5");
	SetScale(fPoint(164*0.7, 240*0.7));

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 120.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IdleHool5", m_pImg, fPoint(0, 0), fPoint(164.f, 240.f), fPoint(164.f, 0), fPoint(164.f, 240.f),0, 0.1f, 20,true,true);

	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\JUSTICESERVED1.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"JusticeServed2", L"Sound\\JUSTICESERVED2.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Gotcha", L"Sound\\GOTCHA.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Collect", L"Sound\\COLLECTHOOLIGAN.wav", false, false);
}

CHooligan5::~CHooligan5()
{
}

CHooligan5* CHooligan5::Clone()
{
	return new CHooligan5(*this);
}
void CHooligan5::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		CGameObject::holiganSave;
		CGameObject::holiganSave++;
		Count++;
	}
	if (Count > 1)
	{
		int R = rand()%3;
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

void CHooligan5::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::GetInst()->GetRenderPos(pos);

	component_render();
}

void CHooligan5::update()
{

	if (CGameObject::Switching != true)
	{
		GetAnimator()->Play(L"IdleHool5");
		GetAnimator()->update();
	}

	else if (CGameObject::Switching == true)
	{
	}
}
