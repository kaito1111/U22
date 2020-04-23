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
private:
	PhysicsStaticObject physics;
	//空。つまり背景
	SkinModel skyModel;
	//床
	SkinModel m_floorModel;
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
};

