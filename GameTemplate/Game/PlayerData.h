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
	int nowSavePlayer = 0;//for文で回すために使うやつ
	int stageNum = 0; //保存したりするステージの番号
public:
	PlayerData();
	~PlayerData();
	Stage* stage = nullptr;
	void SavePlayerData(GamePlayer* playerptr); //セーブ
	void  LoadPlayerData();//ロード
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

