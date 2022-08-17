#pragma once

class CCollider;
class CAnimator;
enum class GROUP_GAMEOBJ;

class CGameObject
{
	friend class CEventManager;

private:
	wstring m_strName;
	fPoint m_fptPos;
	fPoint m_fptScale;
	GROUP_GAMEOBJ objGroup;

	// Component
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;
	float m_fAccelGravity;

	bool m_bAlive;
	void SetDead();

public:
	static short holiganSave;
	static bool Switching;
	CGameObject();
	CGameObject(const CGameObject& other);
	virtual ~CGameObject();
	void SetHoligan(short num);
	virtual CGameObject* Clone() = 0;

	void SetPos(fPoint pos);
	void SetScale(fPoint scale);
	void SetName(wstring name);

	fPoint GetPos();
	fPoint GetScale();
	wstring GetName();

	bool isDead();


	virtual void update() = 0;			// �ݵ�� ��ӹ��� ��ü�� update�� �����ϵ��� ���������Լ��� ����
	virtual void finalupdate();			// ��ӹ޴� Ŭ������ �������̵� �� �� ���� ���� final Ű����
	virtual void render();
	virtual void component_render();	// ������Ʈ���� ������ ǥ���ϱ� ����

	void debug_render();

	CCollider* GetCollider();				// �浹ü ��ȯ
	void CreateCollider();					// �浹ü ����

	virtual void OnCollision(CCollider* _pOther) {}			// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionExit(CCollider* _pOther) {}		// �����ǿ� Ż�浹 �����Լ�

	CAnimator* GetAnimator();				// �ִϸ����� ��ȯ
	void CreateAnimator();
	GROUP_GAMEOBJ GetGroup();
	void SetGroup(GROUP_GAMEOBJ GROUP);
	void Gravity_Apply();
	// �ִϸ����� ����
};

