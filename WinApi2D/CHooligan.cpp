#include "framework.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CHooligan.h"

CHooligan::CHooligan()
{
	srand(time(NULL));
	CD2DImage* m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Hooligan", L"texture\\Animation\\Hooligan\\Host1\\Idle\\Host1_144_240.png"); 
	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\JUSTICESERVED1.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\JUSTICESERVED2.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"JusticeServed1", L"Sound\\GOTCHA.wav", false, false);
	CSoundManager::GetInst()->AddSound(L"Collect", L"Sound\\COLLECTHOOLIGAN.wav", false, false);
	SetName(L"Hooligan");
	SetScale(fPoint(144 * 0.7, 240 * 0.7));

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 120.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IdleHool", m_pImg, fPoint(0, 0), fPoint(144.f, 240.f), fPoint(144.f, 0),fPoint(144.f, 240.f),0, 0.1f, 20,true,false);
	/*애니메이션이름,다렉이름,왼쪽위,*/
}

CHooligan::~CHooligan()
{
}
void CHooligan::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	
	if (pOtherObj->GetName() == L"Player")
	{
		Count++;
		CGameObject::holiganSave++;
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


	if (CGameObject::Switching != true)
	{
		GetAnimator()->update();
		GetAnimator()->Play(L"IdleHool");
	}

	else if (CGameObject::Switching == true)
	{
	}
}
