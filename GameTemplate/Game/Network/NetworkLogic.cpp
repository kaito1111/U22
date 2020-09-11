#include "stdafx.h"
#include "NetworkLogic.h"
#include "LoadBalancingListener.h"
#include "LoadBalancing-cpp/inc/Client.h"
#include "TestView.h"
#include "Console.h"

/// <summary>
/// photonネットワークを動かすやつ
/// </summary>
/// <remarks>
/// 直訳したらネットワーク倫理
/// </remarks>

//photonのappID photonを違うサーバーの場合、対応したappIDを入力
static const ExitGames::Common::JString appID = L"62a270e7-a9c5-480d-bc87-4f66ceeee673";
//photonサーバーのappVersion
static const ExitGames::Common::JString appVersion = L"1.0";
//photonで作ったサーバーネーム 違うサーバーの場合、対応したサーバー名を入力
static ExitGames::Common::JString gameName = L"photonTest";

//static const ExitGames::Common::JString PLAYER_NAME = L"user";
static const int MAX_SENDCOUNT = 100;

//名前空間定義
using namespace ExitGames::LoadBalancing;
using namespace ExitGames::Common;
using namespace ExitGames::Photon;

/// <summary>
/// デストラクタ
/// <para>Startで作成したListenerとClientの削除</para>
/// </summary>
NetworkLogic::~NetworkLogic()
{
	delete mpLbl;
	delete mpLbc;
}

/// <summary>
/// サーバーに接続
/// <para>NV + 経過時間で値を取得したものがPlayerIDに</para>
/// </summary>
void NetworkLogic::Connect() {
	mpLbl->connect(JString(L"NV") + GETTIMEMS());
}

/// <summary>
/// サーバーから切断
/// </summary>
void NetworkLogic::Disconnect() {
	mpLbl->disconnect();
}

void NetworkLogic::CreateRoom()
{
	mpLbl->createRoom();
}

void NetworkLogic::CreateRoom(const JString& roomName, nByte maxPlayers)
{
	mpLbc->opCreateRoom(roomName, RoomOptions().setMaxPlayers(maxPlayers));
}

void NetworkLogic::Join()
{
	Hashtable expectedCustomRoomProperties;
	expectedCustomRoomProperties.put(L"map", 1);
	mpLbc->opJoinRandomRoom(expectedCustomRoomProperties);
}

void NetworkLogic::CreateRoomOrJoin(const JString& roomName, nByte maxPlayers, bool CreateRoom)
{
	CreateRoom = mpLbc->opJoinOrCreateRoom(roomName, RoomOptions().setMaxPlayers(maxPlayers));
}

/// <summary>
/// 初期化処理
/// </summary>
void NetworkLogic::Start() {
	//lbリスナーの作成
	mpLbl = new LoadBalancingListener(&m_testview);
	//クライアントの作成
	mpLbc = new Client(*mpLbl, appID, appVersion, ExitGames::Photon::ConnectionProtocol::TCP,true, RegionSelectionMode::BEST);
	//デバッグ出力レベルの設定？
	mpLbc->setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS));
	//ベースリスナーの設定
	ExitGames::Common::Base::setListener(mpLbl);
	//ベースデバッグ出力レベルの設定？
	ExitGames::Common::Base::setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS));
	//	pLbc->setCRCEnabled(true);
	//クライアントの設定
	mpLbl->setLBC(mpLbc);
	//通信の状態をTrueに設定　通信開始の合図てきな？
	mpLbc->setTrafficStatsEnabled(true);
	//接続中
//	Console::get().writeLine(L"LBC: connecting...");
	//接続(PlayerID)
	mpLbl->connect(JString(L"NV") + GETTIMEMS());
}


void NetworkLogic::Update() {
	//クライアントの更新
	mpLbc->service();
	//リスナーの更新
	mpLbl->service();
}

