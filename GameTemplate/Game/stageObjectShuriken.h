#pragma once
class stageObjectShuriken : public IGameObject
{
public:
	stageObjectShuriken();
	~stageObjectShuriken();
	//レベル君で呼ぶからパブリック！
	bool Start();
	void Update();
private:
	SkinModel m_model;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();


};

