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
	//�v���C���[�̃C���X�^���X�ɖ��O��t����
	static const char PlayerMax = 2;//�v���C���[�̍ő吔
	for (nowSavePlayer = 1;         //���ꂩ�疼�t����v���C���[�̔ԍ�
		nowSavePlayer <= PlayerMax; //�v���C���[�̍ő吔���for��������ĂȂ��Ȃ�
		nowSavePlayer++) {			//�񂵑������

		char PlayerName[256] = {};//���O
		sprintf(PlayerName, "player%d", nowSavePlayer + 1);
		player[nowSavePlayer - 1] = FindGO<Player>(0, PlayerName);
	}

	LoadPlayerData();

	return true;
}

void PlayerData::SavePlayerData()
{
		//�t�@�C���̕ۑ�
		FILE* file = fopen("../PlayerData.text", "wb");
		if (file != nullptr) {
			//�t�@�C���̃I�[�v���Ɏ��s
		}
		stageNum = stage->GetNowStage();
		fwrite(&stageNum, sizeof(int),1, file);
		fwrite(&player1Pos, sizeof(CVector3), 1, file);
		fwrite(&player2Pos, sizeof(CVector3), 1, file);
		fclose(file);
}

void PlayerData::LoadPlayerData()
{
	//�t�@�C���̕ۑ�
	FILE* file = fopen("../PlayerData.text", "rb");
	if (file != nullptr) {
		//�t�@�C���̓ǂݍ��݂Ɏ��s
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
	//�󂯎���1��
	//int a;
	//int b;
	//std::tie(a,b) = GetPos();
}


