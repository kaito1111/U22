#pragma once
#include "Player.h"
class Goal : public IGameObject
{
public:
	Goal(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/);
	~Goal();

	//Start,Update,Draw�̓W�F�l���[�^�[����A�N�Z�X����̂ŁA
	//public�����o�ϐ��ɓ���Ă��܂�
	bool Start();
	void Update();
	void Draw();
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
	bool IsClear() {
		return isClear;
	}
private:	
	bool isClear = false;
	SkinModel m_Skin;
	CVector3 m_Position = CVector3::Zero();
	Player* m_player[2] = {};
	CQuaternion m_rot = CQuaternion::Identity();
	SpriteRender* m_ClearSprite = nullptr;
	SoundSource m_Se;
};