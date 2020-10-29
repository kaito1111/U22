#pragma once
class GamePlayer;
class Goal : public IGameObject
{
public:
	Goal(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/);
	~Goal();

	//Start,Update,Drawはジェネレーターからアクセスするので、
	//publicメンバ変数に入れています
	bool Start();
	void Update();
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
	bool IsClear() {
		return isClear;
	}
	void SetLast(bool Is) {
		Last = Is;
	}
private:	
	void OnDestroy()override;
	bool isClear = false;
	SkinModelRender* m_SkinRender = nullptr;
	CVector3 m_Position = CVector3::Zero();
	GamePlayer* m_player[g_PlayerNum] = {};
	CQuaternion m_rot = CQuaternion::Identity();
	SpriteRender* m_ClearSprite = nullptr;
	SoundSource m_Se;
	CFontRender* m_FinishFont = nullptr;
	bool Last = false;
};