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
	//static const char PlayerMax = 2;//�v���C���[�̍ő吔

	////�v���C���[�ɖ��O���Ă�
	//for (nowSavePlayer = 1;
	//	nowSavePlayer <= g_PlayerNum;
	//	nowSavePlayer++) {

	//	char PlayerName[256] = {};//���O
	//	sprintf(PlayerName, "player%d", nowSavePlayer);
	//	player[nowSavePlayer - 1] = FindGO<GamePlayer>(PlayerName);
	//}
	//�t�@�C���̕ۑ�
	FILE* file = fopen("../PlayerData.txt", "wb");
	if (file != nullptr) {
		//�t�@�C���̃I�[�v���Ɏ��s
		return;
	}
	stage = FindGO<Stage>("stage");
	stageNum = stage->GetNowStage();
	player1Pos = playerptr->GetPosition();
	fwrite(&stageNum, sizeof(int), 1, file);
	fwrite(&player1Pos, sizeof(CVector3), 1, file);//�����̂P�̓R�s�[����鐔�i�Ȃ񂶂�ˁH�j
	fwrite(&player2Pos, sizeof(CVector3), 1, file);
	fclose(file);
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



