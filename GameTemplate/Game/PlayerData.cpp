#include "stdafx.h"
#include "PlayerData.h"
#include "Player.h"
#include "Stage.h"
#include<tuple>
#include <fstream>
bool PlayerData::Start()
{
	
	return true;
}
PlayerData::PlayerData()
{
}


PlayerData::~PlayerData()
{
}

void PlayerData::SavePlayerData()
{
	//static const char PlayerMax = 2;//プレイヤーの最大数
	
	for (nowSavePlayer = 1;         //これから名付けるプレイヤーの番号
		nowSavePlayer <= g_PlayerNum; //プレイヤーの最大数よりfor文が回ってないなら
		nowSavePlayer++) {			//回し続けるよ

		char PlayerName[256] = {};//名前
		sprintf(PlayerName, "player%d", nowSavePlayer );
		player[nowSavePlayer - 1] = FindGO<GamePlayer>(PlayerName);
	}
		//ファイルの保存
		FILE* file = fopen("../PlayerData.txt", "wb");
		if (file != nullptr) {
			//ファイルのオープンに失敗
		}
		stage = FindGO<Stage>("stage");
		stageNum = stage->GetNowStage();
		player1Pos = player[0]->GetPosition();
		player2Pos = player[1]->GetPosition();
		fwrite(&stageNum, sizeof(int), 1, file);
		fwrite(&player1Pos, sizeof(CVector3), 1, file);//引数の１はコピーされる数（なんじゃね？）
		fwrite(&player2Pos, sizeof(CVector3), 1, file);
		fclose(file);
}

void PlayerData::LoadPlayerData()
{
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//ファイルに初期値を保存しておくためだけのもの。１回通せたら消す。
	//ファイルの保存
	//FILE* files = fopen("../PlayerData.txt", "wb");
	//if (files != nullptr) {
	//	//ファイルのオープンに失敗
	//}
	//fwrite(&stageNum, sizeof(int), 1, files);
	//fwrite(&player1Pos, sizeof(CVector3), 1, files);//引数の１はコピーされる数（なんじゃね？）
	//fwrite(&player2Pos, sizeof(CVector3), 1, files);
	//fclose(files);
	//////////////////////////////////////////////////////////////////////////////////////////////
	//ファイル天界
	FILE* file = fopen("../PlayerData.txt", "rb");
	if (file != nullptr) {
		//ファイルの読み込みに失敗
	}
	fread(&stageNum, sizeof(int), 1, file);
	fread(&player1Pos, sizeof(CVector3), 1, file);
	fread(&player2Pos, sizeof(CVector3), 1, file);
	fclose(file);
	
}



