#pragma once
class TitleStage : public IGameObject
{
public:
	//�^�C�g���Ŏg���X�e�[�W�B�I�u�W�F�N�g������������f�����o���B
	TitleStage();
	~TitleStage();
	bool Start();
	void Update();
	//�X�e�[�W1
	CVector3 GetPos() {
		return m_pos;
	}
	void SetPos(const CVector3& pos) {
		m_pos = pos;
	}
	CVector3 GetScale() {
		return m_scale;
	}
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	//�X�e�[�W�Q
	CVector3 GetPos2() {
		return m_pos2;
	}
	void SetPos2(const CVector3& pos) {
		m_pos2 = pos;
	}
	CVector3 GetScale2() {
		return m_scale2;
	}
	void SetScale2(const CVector3& scale)
	{
		m_scale2 = scale;
	}
private:
	//�X�e�[�W�P
	SkinModel m_model;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	//�X�e�[�W�Q
	SkinModel m_model2;
	CVector3 m_pos2 = {2000.0f,0.0f,0.0f};
	CVector3 m_scale2 = CVector3::One();
};

