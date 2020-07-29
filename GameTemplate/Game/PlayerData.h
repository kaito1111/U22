#pragma once
class Player;
class Stage;
class PlayerData : public IGameObject
{
private:
	Player* player[2] = {};
	CVector3 player1Pos = CVector3::Zero();
	CVector3 player2Pos = CVector3::Zero();
	int nowSavePlayer = 0;//for文で回すために使うやつ
	int stageNum = 0; //保存したりするステージの番号
public:
	PlayerData();
	~PlayerData();
	Stage* stage = nullptr;
	void SavePlayerData(); //セーブ
	void  LoadPlayerData();//ロード
	


	//前回のプレイヤーの座標を返す処理
	std::tuple<const CVector3&, //player1
		const CVector3&,        //player2
		const int>				//ステージ番号
		GetLastTimePos();		//関数名
	//前回のステージ番号を返す
};

