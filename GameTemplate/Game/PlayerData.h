#pragma once
class GamePlayer;
class Stage;
class PlayerData : public IGameObject
{
private:
	bool Start();
	GamePlayer* player[g_PlayerNum] = {};
	CVector3 player1Pos = CVector3::Zero();
	CVector3 player2Pos = CVector3::Zero();
	int nowSavePlayer = 0;//for���ŉ񂷂��߂Ɏg�����
	int stageNum = 0; //�ۑ������肷��X�e�[�W�̔ԍ�
public:
	PlayerData();
	~PlayerData();
	Stage* stage = nullptr;
	void SavePlayerData(/*GamePlayer* playerptr*/); //�Z�[�u
	void  LoadPlayerData();//���[�h
	CVector3 player1(){
		return player1Pos;
	}
	CVector3 player2(){
		return player2Pos;
	}
	int GetStage(){
		return stageNum;
	}
};
