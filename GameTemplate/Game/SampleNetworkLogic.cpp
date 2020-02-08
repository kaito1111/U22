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
//	//接続失敗　connect関数動いてる？
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
//	//app情報の初期化
//	static const ExitGames::Common::JString	appID = L"62a270e7-a9c5-480d-bc87-4f66ceeee673";	//自分のアプリケーションID
//	static const ExitGames::Common::JString	appVersion = L"1.0";								//バージョン
//
//	//SampleNetの初期化
//	SampleNetworkLogic networkLogic(appID, appVersion);
//
//	//接続
//	networkLogic.connect();
//}