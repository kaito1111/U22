#include "stdafx.h"
#include "PlayerData.h"
#include "Player.h"
#include "Stage.h"
#include<tuple>
PlayerData::PlayerData()
{
}


PlayerData::~PlayerData()
{
}

bool PlayerData::Start()
{
	stage = FindGO<Stage>("stage");
	//プレイヤーのインスタンスに名前を付ける
	static const char PlayerMax = 2;//プレイヤーの最大数
	for (nowSavePlayer = 1;         //これから名付けるプレイヤーの番号
		nowSavePlayer <= PlayerMax; //プレイヤーの最大数よりfor文が回ってないなら
		nowSavePlayer++) {			//回し続けるよ

		char PlayerName[256] = {};//名前
		sprintf(PlayerName, "player%d", nowSavePlayer + 1);
		player[nowSavePlayer - 1] = FindGO<Player>(0, PlayerName);
	}

	LoadPlayerData();

	return true;
}

void PlayerData::SavePlayerData()
{
		//ファイルの保存
		FILE* file = fopen("../PlayerData.text", "wb");
		if (file != nullptr) {
			//ファイルのオープンに失敗
		}
		stageNum = stage->GetNowStage();
		fwrite(&stageNum, sizeof(int),1, file);
		fwrite(&player1Pos, sizeof(CVector3), 1, file);
		fwrite(&player2Pos, sizeof(CVector3), 1, file);
		fclose(file);
}

void PlayerData::LoadPlayerData()
{
	//ファイルの保存
	FILE* file = fopen("../PlayerData.text", "rb");
	if (file != nullptr) {
		//ファイルの読み込みに失敗
	}
	fread(&stageNum, sizeof(int), 1, file);
	fread(&player1Pos, sizeof(CVector3), 1, file);
	fread(&player2Pos, sizeof(CVector3), 1, file);
	fclose(file);
	
}

std::tuple<const CVector3&, const CVector3&> PlayerData::GetLastTimePos()
{
	LoadPlayerData();
	return std::forward_as_tuple(player1Pos, player2Pos);
	//受け取り方1例
	//int a;
	//int b;
	//std::tie(a,b) = GetPos();
}


