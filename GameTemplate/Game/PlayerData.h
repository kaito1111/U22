#pragma once
class Player;
class Stage;
class PlayerData : public IGameObject
{
private:
	bool Start();
	Player* player[2] = {};
	CVector3 player1Pos = CVector3::Zero();
	CVector3 player2Pos = CVector3::Zero();
	int nowSavePlayer = 0;//for���ŉ񂷂��߂Ɏg�����
	int stageNum = 0; //�ۑ������肷��X�e�[�W�̔ԍ�
public:
	PlayerData();
	~PlayerData();
	Stage* stage = nullptr;
	void SavePlayerData();
	void  LoadPlayerData();
	


	//�O��̃v���C���[�̍��W��Ԃ�����
	std::tuple<const CVector3&, //player1
		const CVector3&>        //player2
		GetLastTimePos();		//�֐���
};

