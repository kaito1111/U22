#pragma once
class Player;
class GameObjectScythe : public IGameObject
{
public:
	GameObjectScythe(const wchar_t* modelName, CVector3 pos, CQuaternion rot);
	//GameObjectScythe();
	~GameObjectScythe();
	bool Start();
	void Update();
	void Draw();
	void PlayerKill();
	void Move();//�U��q�^��
	void SetPos(const CVector3& pos) {
		m_pos = pos;
	};
private:
	Player* player1 = nullptr;
	Player* player2 = nullptr;
	SkinModel m_model;							 //�X�L�����f��
	CVector3 m_pos = CVector3::Zero();			 //���W
	CQuaternion m_rot = CQuaternion::Identity(); //��]��
	float rot = 0.0f;                            //��]���Ă��
	float spinSpeed = 0.0f;						 //��]���x
	bool spinChange = false;                     //��]������؂�ւ���t���O
	bool speedChange = false;                    //��]���x��؂�ւ���t���O

	//���ʉE��
	CVector3 m_front = CVector3::Front();
	CVector3 m_right = CVector3::Right();
	CVector3 m_up = CVector3::Up();
	/*const CVector3 xy = { 400.0f,500.0f,0.0f };
	m_pos = xy;*/

};

