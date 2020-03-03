#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
	//�J�������������B
	g_camera3D.SetPosition({ 100.0f, 100.0f, 0.0f });
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
	//for (int i = 0; i < m_PlayerNum; i++) {
	Target += m_Player[0]->GetPosition();
	Target.y += 100.0f;

	//}
	//��ŃJ�����̈ʒu����������ĂȂ��̂Ŗ�����蒲��
	//�㒼����������Ă�
	//Target.y += 100.0f;

	//�v���C���[��2�l�ȏア�邩��^�񒆂��Ƃ�
	//Target /= m_PlayerNum;

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

	CVector3 pos = Target;
	pos.z += 500.0f;
	g_camera3D.SetTarget(Target);
	g_camera3D.SetPosition(pos);
	//�J�����̍X�V�B
	g_camera3D.Update();
}
