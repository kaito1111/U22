#pragma once
class Player;
class NPole;
class SPole : public IGameObject
{
public:

	SPole();
	~SPole();
	//�i�ޕ��������߂�
	void SetMoveDir(CVector3 MoveDir) {
		m_move = MoveDir;
	}
	void SetPosition(CVector3 pos) {
		m_position=pos;
	}
	CVector3 GetPosition() {
		return m_position;
	}
	void magunetTask(CVector3& Position);
private:


	bool Start()override;
	void Update()override;
	void Draw()override;

	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_move = CVector3::Zero();
	Player* m_player = nullptr;
	NPole* m_npole = nullptr;

	void deleteRange();
	void idou();
};