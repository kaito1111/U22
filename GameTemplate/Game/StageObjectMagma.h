#pragma once
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
	CVector3 m_pos = CVector3::Zero();//���W
	SkinModel m_model;//�����G�t�F�N�g�ɕς��񂶂�Ȃ�����

	
};