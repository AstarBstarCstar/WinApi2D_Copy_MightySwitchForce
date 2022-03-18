#include "framework.h"
//#include "CGravity.h"
//#include "CGravity.h" 
//
//CObject::CObject()
//, m_pRigidBody(nullptr)
//, m_pGravity(nullptr)
//, m_bAlive(true)
//{
//}
//
//CObject::CObject(const CObject& _origin)
//, m_pRigidBody(nullptr)
//, m_pGravity(nullptr)
//, m_bAlive(true)
//{
//
//        if (_origin.m_pGravity)
//        {
//            m_pGravity = new CGravity(*_origin.m_pGravity);
//            m_pGravity->m_pOwner = this;
//        }
//}
//
//CObject::~CObject()
//{
//    if (nullptr != m_pCollider)
//        delete m_pCollider;
//
//    if (nullptr != m_pAnimator)
//        delete m_pAnimator;
//
//    if (nullptr != m_pRigidBody)
//        delete m_pRigidBody;
//
//    if (nullptr != m_pGravity)
//        delete m_pGravity;
//}
//
//void CObject::finalupdate()
//{
//    if (m_pCollider)
//        m_pCollider->finalupdate();
//
//    if (m_pAnimator)
//        m_pAnimator->finalupdate();
//
//    if (m_pGravity)
//        m_pGravity->finalupdate();
//
//    if (m_pRigidBody)
//        m_pRigidBody->finalupdate();
//}
//
//void CObject::render(HDC _dc) { ... }
//
//void CObject::component_render(HDC _dc) { ... }
//
//
//void CObject::CreateCollider() { ... }
//
//void CObject::CreateAnimator() { ... }
//
//void CObject::CreateRigidBody() { ... }
//
//void CObject::CreateGravity()
//{
//    m_pGravity = new CGravity;
//    m_pGravity->m_pOwner = this;
//}