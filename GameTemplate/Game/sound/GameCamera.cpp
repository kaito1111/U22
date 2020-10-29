#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	m_CharaCon.Init(30.0f, 30.0f, m_Pos);
	for (int i = 0; i < m_PlayerNum + 1; i++) {
		char PlayerNo[256] = {}; 
		sprintf(PlayerNo, "player%d", m_PlayerNum + 1);
		QueryGOs<GamePlayer>(PlayerNo, [&](GamePlayer* player)->bool {
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

	for (int i = 0; i < m_PlayerNum; i++) {
		CVector3 m_PlPos = m_Player[i]->GetPosition();


		Target += m_PlPos;
	}
	//��ŃJ�����̈ʒu����������ĂȂ��̂Ŗ�����蒲��
	//�㒼����������Ă�
	//Target.y += 100.0f;

	//�v���C���[��2�l�ȏア�邩��^�񒆂��Ƃ�
	Target /= m_PlayerNum;
	Target.y += 100.0f;

	//���̌��E���X�V
	/*if (Decline < Target.y) {
		Decline = Target.y;
	}
	else {
		Target.y = Decline;
	}*/

	//�v���C���[���E��
	for (int i = 0; i < m_PlayerNum; i++) {
		if (m_Player[i]->GetPosition().y < Target.y - 500.0f) {
			m_Player[i]->SetIsSi();
		}
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
	m_Pos = Target;
	m_Pos.z = 500.0f;
	//CVector3 move = m_Pos - NextPosition;
	//if (move.Length() > 0.01f) {
	//	m_Pos = m_CharaCon.Execute(1.0f, move);
	//}
	//else {
	//	m_Pos = move;
	//}
	//m_Pos.z += 500.0f;
	//m_Pos = NextPosition;
	g_camera3D.SetTarget(Target);
	g_camera3D.SetPosition(m_Pos);
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
