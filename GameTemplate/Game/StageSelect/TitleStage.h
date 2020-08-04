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
	//ステージ1
	CVector3 GetPos() {
		return m_pos;
	}
	void SetPos(const CVector3& pos) {
		m_pos = pos;
	}
	CVector3 GetScale() {
		return m_scale;
	}
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	//ステージ２
	CVector3 GetPos2() {
		return m_pos2;
	}
	void SetPos2(const CVector3& pos) {
		m_pos2 = pos;
	}
	CVector3 GetScale2() {
		return m_scale2;
	}
	void SetScale2(const CVector3& scale)
	{
		m_scale2 = scale;
	}
	//ステージ３
	CVector3 GetPos3() {
		return m_pos3;
	}
	void SetPos3(const CVector3& pos) {
		m_pos3 = pos;
	}
	CVector3 GetScale3() {
		return m_scale3;
	}
	void SetScale3(const CVector3& scale)
	{
		m_scale3 = scale;
	}
private:
	PhysicsStaticObject physics;
	//空。つまり背景
	SkinModelRender* skyModel=nullptr;
	SpriteRender* m_SelectSprite = nullptr;
	//床
	SkinModel m_floorModel;

	SpriteRender* m_Stage1Sprite = nullptr;
	CVector3 m_Sprite1Pos = { 0.0f,170.0f,0.0f };

	SpriteRender* m_Stage2Sprite = nullptr;
	CVector3 m_Sprite2Pos = { -800.0f,670.0f,0.0f };
	CVector3 m_SpriteScale = CVector3::Zero();

	bool m_IsClear1 = false;
	//Iwa* m_Iwa = nullptr;

	CVector3 m_floorPos = CVector3::Zero();
	//ステージ１
	SkinModel m_model;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	//ステージ２
	SkinModel m_model2;
	CVector3 m_pos2 = {0.0f,0.0f,0.0f};
	CVector3 m_scale2 = CVector3::One();
	Sprite m_copymainRendrTarget;
	//ステージ２
	SkinModel m_model3;
	CVector3 m_pos3 = { 0.0f,0.0f,0.0f };
	CVector3 m_scale3 = CVector3::One();
	//Sprite m_copymainRendrTarget;
};

