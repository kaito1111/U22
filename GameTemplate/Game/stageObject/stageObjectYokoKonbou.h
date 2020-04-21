#pragma once
class stageObjectYokoKonbou : public IGameObject
{
public:
	stageObjectYokoKonbou();
	//stageObjectYokoKonbou(const wchar_t * modelName, CVector3 pos, CQuaternion rot);
	~stageObjectYokoKonbou();
	bool Start();
	void Update();
	void Draw();

private:
	SkinModel m_model;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();

};

