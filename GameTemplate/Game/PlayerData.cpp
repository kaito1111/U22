#include "stdafx.h"
#include "PlayerData.h"
#include "Player.h"
#include "Stage.h"
#include<tuple>
#include <fstream>
#include "Player.h"
#include"GameCamera.h"
PlayerData::PlayerData()
{
}


PlayerData::~PlayerData()
{
}

void PlayerData::SavePlayerData(/*GamePlayer* playerptr*/)
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//ファイルに初期値を保存しておくためだけのもの。１回通せたら消す。
	//ファイルの保存
	//FILE* files = fopen("../PlayerData.txt", "wb");
	//if (files != nullptr) {
	//	return;
	//	//ファイルのオープンに失敗
	//}
	//fwrite(&stageNum, sizeof(int), 1, files);
	//fwrite(&player1Pos, sizeof(CVector3), 1, files);//引数の１はコピーされる数（なんじゃね？）
	//fwrite(&player2Pos, sizeof(CVector3), 1, files);
	//fclose(files);
	////////////////////////////////////////////////////////////////////////////////////////////
	//ファイルの保存
	FILE* files = fopen("../PlayerData.txt", "wb");
	if (files != nullptr) {
		//ファイルのオープンに失敗
		//return;
	}
	player[0] = FindGO<GamePlayer>("player1");
	player[1] = FindGO<GamePlayer>("player2");
	stage	  =	FindGO<Stage>("stage");
	gCamera	  = FindGO<GameCamera>("camera");
	player1Pos = player[0]->GetPosition();
	player2Pos = player[1]->GetPosition();


	stageNum = stage->GetNowStage();
	//player1Pos = playerptr->GetPosition();
	
	fwrite(&stageNum, sizeof(int), 1, files);
	fwrite(&player1Pos, sizeof(CVector3), 1, files);//引数の１はコピーされる数（なんじゃね？）
	fwrite(&player2Pos, sizeof(CVector3), 1, files);
	fclose(files);
	DeleteGO(gCamera);
	DeleteGO(player[0]);
	DeleteGO(player[1]);
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



