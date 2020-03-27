#pragma once
class TitleStage : public IGameObject
{
public:
	//タイトルで使うステージ。オブジェクト取っ払ったモデルを出す。
	TitleStage();
	~TitleStage();
	bool Start();
	void Update();
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
	//ステージ２
	SkinModel m_model2;
	CVector3 m_pos2 = {2000.0f,0.0f,0.0f};
	CVector3 m_scale2 = CVector3::One();
};

