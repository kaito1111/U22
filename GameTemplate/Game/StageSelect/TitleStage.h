#pragma once
#include"physics/physicsStaticObject.h"
class TitleStage : public IGameObject
{
public:
	//�^�C�g���Ŏg���X�e�[�W�B�I�u�W�F�N�g������������f�����o���B
	TitleStage();
	~TitleStage();
	bool Start();
	void Update();
	void Draw();
	void PostRender();
	
private:
	SkinModel m_stage[3] = {};

	CVector3 m_pos[3] = {};
	Sprite m_copymainRendrTarget;
};

