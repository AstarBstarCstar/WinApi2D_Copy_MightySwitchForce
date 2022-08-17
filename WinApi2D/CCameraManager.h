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
	fPoint m_fptLookAt;			// ���� �ִ� ��ġ
	fPoint m_fptCurLookAt;		// ī�޶� ���� ���� ��ġ
	fPoint m_fptPrevLookAt;		// ī�޶� ������ ���� ��ġ

	CGameObject* m_pTargetObj;	// Ʈ��ŷ �� ������Ʈ

	fPoint m_fptDiff;			// �������� ��ġ , ���� ����� ����
	fPoint m_fCollection;

	fPoint m_fptLastLT;		// �� �̻����� �� �� ����
	fPoint m_fptLastRB;		// �� �̻����� �� �� ����
	bool   m_bContectX;
	bool	  m_bContectY;
	bool	  m_bBoundary;

	float m_fTime ;			// Ÿ���� ���󰡴� �ѽð�
	float m_fAccTime;			// Ÿ���� ���� �ҿ�ð�
	float m_fSpeed;				// Ÿ���� ���󰡴� �ӵ�
	float m_fPrevSpeed;			// ������������ �ӵ�
	float m_fAccelGravity;		// ���������� ���� ���ӵ�
	float m_fAccIncrement;		// ���ӵ� ����

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

	fPoint GetLookAt();			// ���� ī�޶� ��ġ ��ȯ
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