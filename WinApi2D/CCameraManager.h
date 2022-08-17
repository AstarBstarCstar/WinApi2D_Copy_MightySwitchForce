#pragma once
class CTexture;
class CGameObject;
class CD2DImage;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	SHAKING,

	NONE
};

struct tCamEffect
{
};

class CCameraManager
{
	SINGLETON(CCameraManager);

private:
	fPoint m_fptLookAt;			// 보고 있는 위치
	fPoint m_fptCurLookAt;		// 카메라가 지금 보는 위치
	fPoint m_fptPrevLookAt;		// 카메라가 이전에 보던 위치

	CGameObject* m_pTargetObj;	// 트래킹 할 오브젝트

	fPoint m_fptDiff;			// 보여지는 위치 , 보정 계산후 저장
	fPoint m_fCollection;

	fPoint m_fptLastLT;		// 그 이상으로 갈 수 없음
	fPoint m_fptLastRB;		// 그 이상으로 갈 수 없음
	bool   m_bContectX;
	bool	  m_bContectY;
	bool	  m_bBoundary;

	float m_fTime ;			// 타겟을 따라가는 총시간
	float m_fAccTime;			// 타겟을 따라간 소요시간
	float m_fSpeed;				// 타겟을 따라가는 속도
	float m_fPrevSpeed;			// 목적지까지의 속도
	float m_fAccelGravity;		// 목적지까지 가는 가속도
	float m_fAccIncrement;		// 가속도 증감

	list<tCamEffect> m_listCamEffect;
	CTexture* m_pImg;
	CAM_EFFECT m_eEffect;
	float fDuration;
	float fCurTime;

public:
	void init();
	void update();
	void render();

	void InitCameraPos(fPoint pos);
	void SetLookAt(fPoint lookAt);
	/*void SetTargetObj(CGameObject* target);*/
	void FollowTargetObj(CGameObject* targetObj, bool flwX, bool flwY);

	fPoint GetLookAt();			// 현재 카메라 위치 반환
	fPoint GetRenderPos(fPoint objPos);
	fPoint GetRealPos(fPoint renderPos);
	fPoint GetLerpPoint();

	void FadeIn(float duration);
	void FadeOut(float duration);
	void Shake(float duration);

	void Scroll(fVec2 vec, float velocity);
	void SetBoundary(fPoint LT, fPoint RB);
	void SetBoundary(bool Boundary);
	void LerpDiff(fPoint pos);
	void CheckBoundary();
private:
	void CalDiff();
};