#pragma once
#include"physics/physicsStaticObject.h"
class TitleStage : public IGameObject
{
public:
	//タイトルで使うステージ。オブジェクト取っ払ったモデルを出す。
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

