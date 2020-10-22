#pragma once

class TitleCamera :public IGameObject
{
	//�^�C�g��
public:
	TitleCamera();
	~TitleCamera();

	void SetTarget(const CVector3& target) {
		m_Target = target;
	}
private:
	bool Start()override;
	void Update()override;

	void Move();

	CVector3 m_Pos = CVector3::Zero();
	CVector3 m_Target = CVector3::Zero();   //�����_
};

