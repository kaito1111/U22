#include "stdafx.h"
#include "PlayerData.h"
#include "Player.h"
#include "Stage.h"
#include<tuple>
#include <fstream>
#include "Player.h"
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

void PlayerData::SavePlayerData(GamePlayer* playerptr)
{
	//static const char PlayerMax = 2;//プレイヤーの最大数

	////プレイヤーに名前つけてる
	//for (nowSavePlayer = 1;
	//	nowSavePlayer <= g_PlayerNum;
	//	nowSavePlayer++) {

	//	char PlayerName[256] = {};//名前
	//	sprintf(PlayerName, "player%d", nowSavePlayer);
	//	player[nowSavePlayer - 1] = FindGO<GamePlayer>(PlayerName);
	//}
	//ファイルの保存
	FILE* file = fopen("../PlayerData.txt", "wb");
	if (file != nullptr) {
		//ファイルのオープンに失敗
		return;
	}
	stage = FindGO<Stage>("stage");
	stageNum = stage->GetNowStage();
	player1Pos = playerptr->GetPosition();
	fwrite(&stageNum, sizeof(int), 1, file);
	fwrite(&player1Pos, sizeof(CVector3), 1, file);//引数の１はコピーされる数（なんじゃね？）
	fwrite(&player2Pos, sizeof(CVector3), 1, file);
	fclose(file);
	DeleteGO(stage);
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
		return;
	}
	fread(&stageNum, sizeof(int), 1, file);
	fread(&player1Pos, sizeof(CVector3), 1, file);
	fread(&player2Pos, sizeof(CVector3), 1, file);
	fclose(file);

}



