#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
	//�J�������������B
	g_camera3D.SetPosition({ -300.0f, 100.0f, 1000.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	for (int i = 0; i < m_PlayerNum + 1; i++) {
		char PlayerNo[256] = {};
		sprintf(PlayerNo, "player%d", m_PlayerNum + 1);
		QueryGOs<Player>(PlayerNo, [&](Player* player)->bool {
			m_Player[m_PlayerNum] = player;
			m_PlayerNum++;
			return true;
		});
	}
	return true;
}

void GameCamera::Update()
{
	CVector3 Target = CVector3::Zero();

	//PlayerNum��0�����炱������ĂȂ�
	for (int i = 0; i < m_PlayerNum; i++) {
	Target += m_Player[i]->GetPosition();
	Target.y += 100.0f;

	}
	//��ŃJ�����̈ʒu����������ĂȂ��̂Ŗ�����蒲��
	//�㒼����������Ă�
	//Target.y += 100.0f;

	//�v���C���[��2�l�ȏア�邩��^�񒆂��Ƃ�
	Target /= m_PlayerNum;

	//���̌��E���X�V
	/*if (Decline < Target.y) {
		Decline = Target.y;
	}
	else {
		Target.y = Decline;
	}*/

	//�v���C���[���E��
	if (m_Player[0]->GetPosition().y < Target.y - 200.0f) {
		m_Player[0]->SIBOU();
	}

	if (Target.x > 300.0f) {
		Target.x = 300.0f;
	}
	if (Target.x < 200.0f) {
		Target.x = 200.0f;
	}
	if (Target.y < 190.0f) {
		Target.y = 190.0f;
	}
	CVector3 pos = Target;
	pos.z += 500.0f;
	g_camera3D.SetTarget(Target); 
	g_camera3D.SetPosition(pos);
	//�J�����̍X�V�B
	g_camera3D.Update();

	//�f�o�b�O�p�̃J����
	{
		////�����_���王�_�Ɍ������ĐL�т�x�N�g�����v�Z����B
		//CVector3 toPos = g_camera3D.GetPosition() - g_camera3D.GetTarget();
		////�J�������񂷃N�H�[�^�j�I�����쐬����B
		//CQuaternion qAddRot;
		////�Q�[���p�b�h�̍��X�e�B�b�N�ŃJ���������B
		////�Q�[���p�b�h���Ȃ��l�̓L�[�{�[�h��'a'��'d'�ŉ񂹂��B
		//qAddRot.SetRotation(CVector3::AxisY(), 0.01f);
		////�����_���王�_�Ɍ������ĐL�т�x�N�g�����񂷁B
		//qAddRot.Multiply(toPos);
		////�V�������_���v�Z����B
		//g_camera3D.SetPosition(g_camera3D.GetTarget() + toPos);
		//g_camera3D.Update();
	}
}
