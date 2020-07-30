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

void PlayerData::SavePlayerData()
{
	//static const char PlayerMax = 2;//�v���C���[�̍ő吔
	
	for (nowSavePlayer = 1;         //���ꂩ�疼�t����v���C���[�̔ԍ�
		nowSavePlayer <= g_PlayerNum; //�v���C���[�̍ő吔���for��������ĂȂ��Ȃ�
		nowSavePlayer++) {			//�񂵑������

		char PlayerName[256] = {};//���O
		sprintf(PlayerName, "player%d", nowSavePlayer );
		player[nowSavePlayer - 1] = FindGO<GamePlayer>(PlayerName);
	}
		//�t�@�C���̕ۑ�
		FILE* file = fopen("../PlayerData.text", "wb");
		if (file != nullptr) {
			//�t�@�C���̃I�[�v���Ɏ��s
		}
		stage = FindGO<Stage>("stage");
		stageNum = stage->GetNowStage();
		player1Pos = player[0]->GetPosition();
		player2Pos = player[1]->GetPosition();
		fwrite(&stageNum, sizeof(int), 1, file);
		fwrite(&player1Pos, sizeof(CVector3), 1, file);//�����̂P�̓R�s�[����鐔�i�Ȃ񂶂�ˁH�j
		fwrite(&player2Pos, sizeof(CVector3), 1, file);
		fclose(file);
}

void PlayerData::LoadPlayerData()
{
	//�t�@�C���V�E
	FILE* file = fopen("../PlayerData.text", "rb");
	if (file != nullptr) {
		//�t�@�C���̓ǂݍ��݂Ɏ��s
	}
	fread(&stageNum, sizeof(int), 1, file);
	fread(&player1Pos, sizeof(CVector3), 1, file);
	fread(&player2Pos, sizeof(CVector3), 1, file);
	fclose(file);
	
}

std::tuple<const CVector3&, const CVector3&, const int> PlayerData::GetLastTimePos()
{
	LoadPlayerData();
	return std::forward_as_tuple(player1Pos, player2Pos, stageNum);
	//�󂯎���1��
	//int a;
	//int b;
	//std::tie(a,b) = GetPos();
}


