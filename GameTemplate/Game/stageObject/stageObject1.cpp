#include "stdafx.h"
#include "stageObject1.h"
#include "Player.h"

stageObject1::stageObject1(const wchar_t* modelName, CVector3 pos, CQuaternion rot)
{
	
}

stageObject1::~stageObject1()
{
	
}

bool stageObject1::Start()
{
	//�h�b�X������ŁB

	//cmo�t�@�C���̓ǂݍ���
	m_model.Init(L"Assets/modelData/TogeToge.cmo");
	m_characon.Init(100.0f, 0.0f, m_position);

	MaxPlayer = Pad::CONNECT_PAD_MAX;
	for (PadNum = 0; PadNum < MaxPlayer; PadNum++) {
		char pl[256];
		sprintf(pl, "player%d", PadNum+1);

		player[PadNum] = FindGO<Player>(pl);
	}
	return true;
}

void stageObject1::Update()
{
	

	Move();//�������z.

	//���[���h�s��̍X�V
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());

}

void stageObject1::Move()
{

	CVector3 moveSpeed = CVector3::Zero();//�ړ����x
	float DownSpeed = -100.0f;	//�������x
	float UpSpeed = 20.0f;		//�㏸���x
	timer++;				//�����タ����Ǝ~�߂���

	//�㉺�^��
	if (m_position.y >= 1880
		//&& timer >= 120
		&&UpDown == false) {
		moveSpeed.y = DownSpeed;
	}

	//�������������Ƃ�
	if (m_position.y <= 1900
		&& UpDown == false) {
		UpDown = true;
		timer = 0;
	}

	//��������͏����B�܂��ɏ������B
	if (m_position.y <= 3400
		&&UpDown == true
		//&&timer >= 120
		) {
		moveSpeed.y = UpSpeed;
		
	}
	if (m_position.y >= 3300) {
		//timer = 0;
		UpDown = false;
	}
	m_position = m_characon.Execute(1.0f, moveSpeed);

	//�v���C���[���E������

	for (int playerNum = 0; playerNum < Pad::CONNECT_PAD_MAX; playerNum++) {
		CVector3 PPos = player[playerNum]->GetPosition();
		CVector3 ToP = PPos - m_position;
		if (ToP.y <= 50 && ToP.y - 50			//�v���C���[����̃x�N�g��Y�݂̂����
			&& ToP.x >= -50 && ToP.x <= 50) { //     �@�@�@�V�@�@�@�@�@X�݂̂����
			//�����Ƀv���C���[���E����������
			CVector3 CheckPoint = CVector3::Zero();

			//��Ń`�F�b�N�|�C���g�����
			player[playerNum]->SetPosition(CheckPoint);
		}
		if (playerNum >= Pad::CONNECT_PAD_MAX) {
			playerNum = 0;
		}
	}

}

void stageObject1::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}