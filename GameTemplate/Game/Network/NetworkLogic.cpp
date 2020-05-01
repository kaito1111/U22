#include "stdafx.h"
#include "NetworkLogic.h"
#include "LoadBalancingListener.h"
#include "LoadBalancing-cpp/inc/Client.h"
#include "TestView.h"
#include "Console.h"

static const ExitGames::Common::JString appID = L"62a270e7-a9c5-480d-bc87-4f66ceeee673";
static const ExitGames::Common::JString appVersion = L"1.0";

static ExitGames::Common::JString gameName = L"U22";

//static const ExitGames::Common::JString PLAYER_NAME = L"user";
static const int MAX_SENDCOUNT = 100;

using namespace ExitGames::LoadBalancing;
using namespace ExitGames::Common;
using namespace ExitGames::Photon;

NetworkLogic::~NetworkLogic()
{
	delete mpLbl;
	delete mpLbc;
}


void NetworkLogic::Connect() {
	mpLbl->connect(JString(L"NV") + GETTIMEMS());
}

void NetworkLogic::Disconnect() {
	mpLbl->disconnect();
}

void NetworkLogic::Start() {
	mpLbl = new LoadBalancingListener(&m_testview);
	mpLbc = new Client(*mpLbl, appID, appVersion, ExitGames::Photon::ConnectionProtocol::UDP,true, RegionSelectionMode::BEST);
	mpLbc->setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS));
	ExitGames::Common::Base::setListener(mpLbl);
	ExitGames::Common::Base::setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS));
	//	pLbc->setCRCEnabled(true);
	mpLbl->setLBC(mpLbc);
	mpLbc->setTrafficStatsEnabled(true);
	Console::get().writeLine(L"LBC: connecting...");
	mpLbl->connect(JString(L"NV") + GETTIMEMS());
}

void NetworkLogic::Update() {
	mpLbc->service();
	mpLbl->service();
}

