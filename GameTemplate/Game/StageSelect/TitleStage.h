#pragma once
#include"physics/physicsStaticObject.h"
class TitleStage : public IGameObject
{
public:
	//�^�C�g���Ŏg���X�e�[�W�B�I�u�W�F�N�g������������f�����o���B
	TitleStage();
	~TitleStage();
	bool Start();
	void Update();
	void Draw();
	void PostRender();
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
	//�X�e�[�W�R
	CVector3 GetPos3() {
		return m_pos3;
	}
	void SetPos3(const CVector3& pos) {
		m_pos3 = pos;
	}
	CVector3 GetScale3() {
		return m_scale3;
	}
	void SetScale3(const CVector3& scale)
	{
		m_scale3 = scale;
	}
private:
	PhysicsStaticObject physics;
	//��B�܂�w�i
	SkinModel skyModel;
	//��
	SkinModel m_floorModel;
	CVector3 m_floorPos = CVector3::Zero();
	//�X�e�[�W�P
	SkinModel m_model;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	//�X�e�[�W�Q
	SkinModel m_model2;
	CVector3 m_pos2 = {0.0f,0.0f,0.0f};
	CVector3 m_scale2 = CVector3::One();
	Sprite m_copymainRendrTarget;
	//�X�e�[�W�Q
	SkinModel m_model3;
	CVector3 m_pos3 = { 0.0f,0.0f,0.0f };
	CVector3 m_scale3 = CVector3::One();
	//Sprite m_copymainRendrTarget;
};
