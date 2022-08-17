#include "framework.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "SwitchBlock.h"
#include "CPlayer.h"
SwitchBlock::SwitchBlock()
{
	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"SWBlock", L"texture\\Object\\SwitchBlock\\SwitchBlock.png");
	SetScale(fPoint(192, 192));
	SetName(L"SwitchBlock");

	CreateCollider();
	GetCollider()->SetScale(fPoint(190.f, 190.f));

	m_bSW = true;
	fCurTime = 0.f;
	m_eChanger = BLOCK_CHANGE::OPEN;
	fDuration = 0.5f;

}
bool CGameObject::Switching;
SwitchBlock::~SwitchBlock()
{
}

SwitchBlock* SwitchBlock::Clone()
{
	return new SwitchBlock(*this);
}

void SwitchBlock::update()
{
	
	//bool?
	//if bool true �϶� ��ϸ� ������Ʈ  
	//GetSwitching();
	if (KeyDown('C'))
	{
		if (m_bSW == true)//Ȱ��ȭ �� ����ġ�� ���¿��� c ������
		{
			m_eChanger = BLOCK_CHANGE::CLOSE;
			fDuration = 0.5;
			fCurTime = 0.f;
			m_bSW = false;
		}
		else//Ȱ��ȭ �� �� ����ġ�� ���¿��� c ������
		{
			m_eChanger = BLOCK_CHANGE::OPEN;
			fDuration = 0.5;
			fCurTime = 0.f;
			m_bSW = true;
			SetName(L"Switching");
			CGameObject::Switching = true;
		}
	}
}

void SwitchBlock::render()
{
	if(CPlayer::debugMode)
	CGameObject::debug_render();//����׿� ���� ǥ��
	fCurTime += (float)fDT;

	float fRatio = fCurTime / fDuration;
	float fAlpha = 1;
	if (BLOCK_CHANGE::CLOSE == m_eChanger)
	{
		fAlpha = 1.f - fRatio;
		if (fAlpha <= 0.5f)
		{
			fAlpha = 0.5f;
			SetName(L"SWB");
		}
	}
	else if (BLOCK_CHANGE::OPEN == m_eChanger)
	{
		fAlpha =0.5f+ fRatio; 
		if (fAlpha >= 1.f)
		{
			SetName(L"SwitchBlock");
			Switching = false;
		}
	}

	fPoint scale = GetScale();
	fPoint pos = CCameraManager::GetInst()->GetRenderPos(GetPos());
	CRenderManager::GetInst()->RenderImage(m_pImg, pos.x - scale.x*0.5, pos.y - scale.y*0.5, pos.x + scale.x*0.5, pos.y + scale.y*0.5, fAlpha);//�׳� �������� �ϸ� ���� ũ���� �ι踦 ���� ���� �ʾ�?

	component_render();
}