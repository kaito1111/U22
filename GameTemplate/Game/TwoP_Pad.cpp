#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Network/NetworkLogic.h"


TwoP_Pad::TwoP_Pad() 
{

}
TwoP_Pad::~TwoP_Pad()
{
}


void TwoP_Pad::Update()
{
	if(INetworkLogic().GetLBL()->GetReady()) {
		//�Q�[�����J�n����Ă���
		while (g_Pad[0].GetNumBufferringXInputData() < MAX_BUFFERRING) {
			//���̃��[�v�̓Q�[���J�n���ɂ�������Ȃ��͂��B
			//�o�b�t�@�����O����B
			g_Pad[0].XInputStateBufferring();
			//�o�b�t�@�����O�������e�𑊎�ɑ���B
			//�p�b�h���𑊎�ɑ���B
			LBLobj()->RaisePadData();
			m_frameNo++;
			//1�t���[�����Q��B
			//Sleep(TIME_ONE_FRAME);
		}
		//�l�b�g���[�N�p�b�h�̃o�b�t�@�����O�B
		while (g_Pad[1].GetNumBufferringXInputData() < MAX_BUFFERRING) {
			//�����͑���Ȃ��Ȃ邱�Ƃ�����͂��Ȃ̂ŁA�Q�[����������\��������B
			NetworkLogic::GetInstance().Update();
			if (LBLobj()->getReceiveFlag() == false) {
				//�܂��l�b�g���[�N�p�b�h�̃f�[�^����M�ł��Ă��Ȃ��B
				//1�t���[���ҋ@�B
				//Sleep(TIME_ONE_FRAME);
			}
			else {
				//�l�b�g���[�N�p�b�h�̃f�[�^����M�����B
				LBLobj()->SetReceiveFlag(false);
			}
		}

		//�o�b�t�@�����O���ꂽ�����g���ăQ�[����i�s������B
		//�܂��V�����p�b�h�����o�b�t�@�����O����B
		if (g_Pad[0].GetNumBufferringXInputData() == MAX_BUFFERRING - 1) {
			//�o�b�t�@�����O�f�[�^������Ȃ��B
			g_Pad[0].XInputStateBufferring();
			//�o�b�t�@�����O�������e�𑊎�ɑ���B
			//�p�b�h���𑊎�ɑ���B
			LBLobj()->RaisePadData();
			//�����ăl�b�g���[�N�p�b�h�B
			NetworkLogic::GetInstance().Update();
		}

		//if (LBLobj()->getReceiveFlag() == true) {
		//	LBLobj()->SetReceiveFlag(false);
		//}
		//else {
		//	//���̃t���[���Ԃɍ���Ȃ������Ƃ��Ă������B�҂��Ȃ��B
		//	//�l�b�g���[�N�p�b�h�̓o�b�t�@�����O���͊������璙�߂�B
		//}
		//printf("Pad::Update Start\n");
		//�o�b�t�@�����O���ꂽ�������ƂɃp�b�h�����X�V����B
		g_Pad[0].Update(true);
		g_Pad[1].UpdateFromNetPadData();
		//printf("Pad::Update End\n");
		m_frameNo++;
	}
	else {
		//�p�b�h�̍X�V
		//�Q�[�����J�n����Ă��Ȃ��B
		//�Q�[���n�܂��ĂȂ��̂ŁA�o�b�t�@�����O���͎g�p���Ȃ��B
		g_Pad[0].Update(false);
		NetworkLogic::GetInstance().Update();
	}

	LBLobj()->SetReceiveFlag(false);
}

