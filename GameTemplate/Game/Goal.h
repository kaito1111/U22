#pragma once
class Player;
class Goal : public IGameObject
{
public:
	Goal(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/);
	~Goal();

	//Start,Update,Drawはジェネレーターからアクセスするので、
	//publicメンバ変数に入れています
	bool Start();
	void Update();
	void Draw();
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
	bool GetClear() {
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