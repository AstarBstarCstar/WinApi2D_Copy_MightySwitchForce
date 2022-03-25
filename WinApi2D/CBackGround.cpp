#include "framework.h"
#include "CBackGround.h"
#include "CD2DImage.h"

CBackGround::CBackGround()
{
    m_pImg = nullptr;
}

CBackGround::~CBackGround()
{

}

void CBackGround::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::GetInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 1.3f, m_pImg->GetHeight() * 1.3f));
}

CBackGround* CBackGround::Clone()
{
    return nullptr;
}

void CBackGround::update()
{
}

void CBackGround::render()
{
    if (nullptr == m_pImg)
    {
        return;
    }
    fPoint pos = GetPos();
    fPoint scale = GetScale();
    fPoint renderPos = CCameraManager::GetInst()->GetRenderPos(pos);
    renderPos = pos + (renderPos - pos) / 5;   

    CRenderManager::GetInst()->RenderImage(
        m_pImg,
        renderPos.x,
        renderPos.y+300,
        renderPos.x+300 + scale.x,
        renderPos.y +300+ scale.y
    );
}