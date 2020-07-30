#pragma once
#include"physics/PhysicsStaticObject.h"
class GamePlayer;
class Floor;
class stageObjectStopFloor : public IGameObject
{
public:
	//stageObjectStopFloor();
	stageObjectStopFloor(/*const wchar_t * modelName, CVector3 pos, CQuaternion rot*/);
	~stageObjectStopFloor();
	bool Start();
	void Update();
	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}
private:
	Floor* floor = nullptr;
	GamePlayer* m_player[2] = {};//�v���C���[�N���X�̏�����
	SkinModel m_model;        //�ʂ�O�̃��f��
	CVector3 playerPosition1 = CVector3::Zero();//player1�̍��W
	CVector3 playerPosition2 = CVector3::Zero();//player2�̍��W
	CVector3 m_pos = CVector3::Zero();          //�����̍��W
	CQuaternion m_rot = CQuaternion::Identity();//��]
	PhysicsStaticObject atarriHantei;			//�ÓI�����I�u�W�F�N�g
	bool upFlag = false;
	bool NewGOModel = false;
};

