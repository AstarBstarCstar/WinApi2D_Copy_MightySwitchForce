#pragma once
#include "CUI.h"
class CD2DImage;
class CHeartHUD:public CUI
{
	private:
		fPoint m_fptPos;
		const fPoint m_fptPos0 = { 1250.f, 70.f };
		const fPoint m_fptPos1 = { 1370.f, 70.f };
		const fPoint m_fptPos2 = { 1490.f, 70.f };
		fPoint m_fptScale;

		CD2DImage* m_pImg2;


	public:
		CHeartHUD();
		virtual ~CHeartHUD();

		virtual void update();
		virtual void render();
		virtual CHeartHUD* Clone();

		void SetPos(const fPoint& fptPos) { m_fptPos = fptPos; }
		const fPoint& GetPos() { return m_fptPos; }

		void SetScale(const fPoint& fptScale) { m_fptScale = fptScale; }
		const fPoint& GetScale() { return m_fptScale; }
		void SetImage(CD2DImage* pImg) { m_pImg2 = pImg; }

};

