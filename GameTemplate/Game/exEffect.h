/// <summary>
/// �G�t�F�N�g�̃T���v���R�[�h
/// </summary>

#pragma once

#include "Player.h"
class exEffect : public IGameObject
{
public:
	exEffect();
	~exEffect();
	void Update();
private:
	Player* player = FindGO<Player>("player", false);	//�f�o�b�O���Ɏg�������Ȃ̂Œʏ�͕K�v�Ȃ��ł��B
	Effect* effect = NewGO<Effect>(0); 					//�G�t�F�N�g�̍쐬
	CVector3 m_pos = CVector3::Zero();					//���W
};

