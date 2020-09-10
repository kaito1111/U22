#pragma once
class GamePlayer;
class Stage;
class GameCamera;
class PlayerData : public IGameObject
{
private:
	GamePlayer* player[g_PlayerNum] = {};
	CVector3 player1Pos = CVector3::Zero();
	CVector3 player2Pos = CVector3::Zero();
	int nowSavePlayer = 0;//for文で回すために使うやつ
	int stageNum = 0; //保存したりするステージの番号
	Stage* stage = nullptr;
	GameCamera* gCamera = nullptr;
public:
	PlayerData();
	~PlayerData();
	
	void SavePlayerData(/*GamePlayer* playerptr*/); //セーブ
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