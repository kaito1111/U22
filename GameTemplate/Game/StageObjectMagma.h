#pragma once
class Player;
class StageObjectMagma : public IGameObject
{
public:
	StageObjectMagma();
	~StageObjectMagma();
	bool Start();
	void Update();
	void Draw();

	void PlayerKill();
private:
	Player* player = nullptr;
	CVector3 m_pos = CVector3::Zero();//���W
	SkinModel m_model;//�����G�t�F�N�g�ɕς��񂶂�Ȃ�����
	CQuaternion m_rot = CQuaternion::Identity();

	
};