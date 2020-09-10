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
	//�t�@�C���ɏ����l��ۑ����Ă������߂����̂��́B�P��ʂ���������B
	//�t�@�C���̕ۑ�
	//FILE* files = fopen("../PlayerData.txt", "wb");
	//if (files != nullptr) {
	//	return;
	//	//�t�@�C���̃I�[�v���Ɏ��s
	//}
	//fwrite(&stageNum, sizeof(int), 1, files);
	//fwrite(&player1Pos, sizeof(CVector3), 1, files);//�����̂P�̓R�s�[����鐔�i�Ȃ񂶂�ˁH�j
	//fwrite(&player2Pos, sizeof(CVector3), 1, files);
	//fclose(files);
	////////////////////////////////////////////////////////////////////////////////////////////
	//�t�@�C���̕ۑ�
	FILE* files = fopen("../PlayerData.txt", "wb");
	if (files != nullptr) {
		//�t�@�C���̃I�[�v���Ɏ��s
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
	fwrite(&player1Pos, sizeof(CVector3), 1, files);//�����̂P�̓R�s�[����鐔�i�Ȃ񂶂�ˁH�j
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
	//�t�@�C���ɏ����l��ۑ����Ă������߂����̂��́B�P��ʂ���������B
	//�t�@�C���̕ۑ�
	//FILE* files = fopen("../PlayerData.txt", "wb");
	//if (files != nullptr) {
	//	//�t�@�C���̃I�[�v���Ɏ��s
	//}
	//fwrite(&stageNum, sizeof(int), 1, files);
	//fwrite(&player1Pos, sizeof(CVector3), 1, files);//�����̂P�̓R�s�[����鐔�i�Ȃ񂶂�ˁH�j
	//fwrite(&player2Pos, sizeof(CVector3), 1, files);
	//fclose(files);
	//////////////////////////////////////////////////////////////////////////////////////////////
	//�t�@�C���V�E
	FILE* file = fopen("../PlayerData.txt", "rb");
	if (file != nullptr) {
		//�t�@�C���̓ǂݍ��݂Ɏ��s
		return;
	}
	fread(&stageNum, sizeof(int), 1, file);
	fread(&player1Pos, sizeof(CVector3), 1, file);
	fread(&player2Pos, sizeof(CVector3), 1, file);
	fclose(file);

}



