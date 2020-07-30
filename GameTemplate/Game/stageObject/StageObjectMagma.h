#pragma once
class GamePlayer;
class StageObjectMagma : public IGameObject
{
public:
	StageObjectMagma(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/);
	~StageObjectMagma();
	bool Start();
	void Update();
	void Draw();
	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}
	void PlayerKill();
private:
	GamePlayer* player1 = nullptr;
	GamePlayer* player2 = nullptr;
	CVector3 m_pos = CVector3::Zero();//���W
	SkinModel m_model;//�����G�t�F�N�g�ɕς��񂶂�Ȃ�����
	CQuaternion m_rot = CQuaternion::Identity();

	
};