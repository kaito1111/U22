#pragma once
class GameObjectScythe : public IGameObject
{
public:
	GameObjectScythe();
	~GameObjectScythe();
	bool Start();
	void Update();
	void Draw();

	void Move();//�U��q�^��
private:
	SkinModel m_model;							 //�X�L�����f��
	CVector3 m_pos = CVector3::Zero();			 //���W
	CQuaternion m_rot = CQuaternion::Identity(); //��]��
	float rot = 0.0f;                            //��]���Ă��
	float spinSpeed = 0.0f;						 //��]���x
	bool spinChange = false;                     //��]������؂�ւ���t���O
	bool speedChange = false;                    //��]���x��؂�ւ���t���O

};

