#pragma once
class Player;
class stageObject2: public IGameObject
{
public:
	stageObject2();
	~stageObject2();
	bool Start();
	void Update();
	CVector3 GetMarutogePosition() {//���W�����
		return m_position;
	};

	Player* player = nullptr;//�v���C���[�N���X
private:

	SkinModel* m_model = nullptr;			         //�X�L�����f��
	CVector3 m_position = CVector3::Zero();          //���W
	CQuaternion m_rotation = CQuaternion::Identity();//��]
	CVector3 scale = CVector3::One();				 //�g��
	void Draw();

};