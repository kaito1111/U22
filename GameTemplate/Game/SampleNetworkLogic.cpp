#include "stdafx.h"
#include "SampleNetworkLogic.h"


//SampleNetworkLogic::SampleNetworkLogic(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion)
//	: m_LoadBalancingClient(myListener, appID, appVersion)
//	, myListener(*pLib, mLogger)
//{
//
//}
//
//void SampleNetworkLogic::connect(void)
//{
//	//�ڑ����s�@connect�֐������Ă�H
//	if (!m_LoadBalancingClient.connect()) {
//		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"Could not connect.");
//	}
//}
//void SampleNetworkLogic::debugReturn(int debugLevel, const ExitGames::Common::JString& string)
//{
//}
//
//int main(void)
//{
//	//app���̏�����
//	static const ExitGames::Common::JString	appID = L"62a270e7-a9c5-480d-bc87-4f66ceeee673";	//�����̃A�v���P�[�V����ID
//	static const ExitGames::Common::JString	appVersion = L"1.0";								//�o�[�W����
//
//	//SampleNet�̏�����
//	SampleNetworkLogic networkLogic(appID, appVersion);
//
//	//�ڑ�
//	networkLogic.connect();
//}