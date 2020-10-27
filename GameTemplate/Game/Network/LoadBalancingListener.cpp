#include "stdafx.h"
#include "BaseView.h"
#include "OutputListener.h"
#include "LoadBalancingListener.h"
#include "NetworkLogic.h"
#include "Console.h"
#include "TestView.h"
#include "common-cpp/inc/object.h"
#include <fstream>
#include <string>

/// <summary>
/// リスナークラス
/// </summary>
/// <remarks>
/// 各処理時のエラーや動作に対しイベントを起こす監視者
/// 分類としてはマネージャ系列みたいな感じだと思う。
/// </remarks>

//TODO : Raise系で重複した処理をまとめる
XINPUT_STATE g_netPadState;

const JString PeerStatesStr[] = {
	L"Uninitialized",
	L"PeerCreated",
	L"ConnectingToNameserver",
	L"ConnectedToNameserver",
	L"DisconnectingFromNameserver",
	L"Connecting",
	L"Connected",
	L"WaitingForCustomAuthenticationNextStepCall",
	L"Authenticated",
	L"JoinedLobby",
	L"DisconnectingFromMasterserver",
	L"ConnectingToGameserver",
	L"ConnectedToGameserver",
	L"AuthenticatedOnGameServer",
	L"Joining",
	L"Joined",
	L"Leaving",
	L"Left",
	L"DisconnectingFromGameserver",
	L"ConnectingToMasterserver",
	L"ConnectedComingFromGameserver",
	L"AuthenticatedComingFromGameserver",
	L"Disconnecting",
	L"Disconnected"
};

// TODO: update PeerStatesStr when PeerStates changes
// Checker below checks count match only
class PeerStatesStrChecker
{
public:
	PeerStatesStrChecker(void)
	{
		DEBUG_ASSERT(sizeof(PeerStatesStr) / sizeof(JString) == PeerStates::Disconnected + 1);
	}
} checker;

//LocalPlayer::LocalPlayer(void) : x(0), y(0),z(0), lastUpdateTime(0)
//{
//}


LoadBalancingListener::LoadBalancingListener(BaseView* pView)
{
	mpLbc = NULL;
	mpView = pView;
}

LoadBalancingListener::~LoadBalancingListener(void)
{
	//ファイルを閉じる。
	//fclose(fp);
	//delete mpView;
}

void LoadBalancingListener::setLBC(ExitGames::LoadBalancing::Client* pLbc)
{
	this->mpLbc = pLbc;
}

void LoadBalancingListener::connect(const JString& userName)
{
	mpLbc->connect(AuthenticationValues().setUserID(JString() + GETTIMEMS()), userName);
	//mpLbc->connect(m_UserData[m_Num++].setUserID(JString() + GETTIMEMS()), userName);
}

void LoadBalancingListener::disconnect() {
	mpLbc->disconnect();
}

void LoadBalancingListener::debugReturn(int debugLevel, const JString& string)
{
	Console::get().debugReturn(debugLevel, string);
}

void LoadBalancingListener::connectionErrorReturn(int errorCode)
{
	Console::get().writeLine(JString(L"connection failed with error ") + errorCode);
	updateState();
}

void LoadBalancingListener::clientErrorReturn(int errorCode)
{
	Console::get().writeLine(JString(L"received error ") + errorCode + L" from client");
	updateState();
}

/// <summary>
/// 警告
/// </summary>
/// <param name="warningCode">警告コード(番号)</param>
void LoadBalancingListener::warningReturn(int warningCode)
{
	Console::get().writeLine(JString(L"received warning ") + warningCode + " from client");
}

void LoadBalancingListener::serverErrorReturn(int errorCode)
{
	Console::get().writeLine(JString(L"received error ") + errorCode + " from server");
	updateState();
}

void LoadBalancingListener::joinRoomEventAction(int playerNr, const JVector<int>& playernrs, const Player& player)
{
	if (m_once == false) {
		//printf("your playerID is %d.\n", playerNr);
		//ゲームを立ち上げて一回のみよばれる。
		m_playerNum = playerNr;;
		m_once = true;
	}

	if (m_playerNum == 1) {
		//最初のひとり
		//printf("Created room.\n");
		//printf("waiting for other player.\n");
		//fp = fopen("Assets/log/Plog.log", "w");
		//char text[64];
		//sprintf(text, "record Start\n");
		//fputs(text, fp);
	}
	if (m_playerNum == 2) {
		//printf("joined room\n");
		//fp = fopen("Assets/log/Nlog.log", "w");
		//char text[64];
		//sprintf(text, "record Start\n");
		//fputs(text, fp);
	}
	if (playerNr == m_maxPlayer){
		//全員そろった。
		m_NetworkReady = true;
		//printf("GameStart.\n");
	}
	if (playerNr > m_maxPlayer) {
		//printf("playerCount is invalid.\n");
		//プレイヤーの人数不正
		throw;
	}
	Console::get().writeLine(JString("player ") + playerNr + L" " + player.getName() + L" has joined the game");
}

void LoadBalancingListener::leaveRoomEventAction(int playerNr, bool isInactive)
{
	if (isInactive) {
		Console::get().writeLine(JString(L"player ") + playerNr + L" has suspended the game");
		wprintf(JString(L"player ") + playerNr + L" has suspended the game");
	}
	else
	{
		Console::get().writeLine(JString(L"player ") + playerNr + L" has abandoned the game");
		wprintf(JString(L"player ") + playerNr + L" has abandoned the game");
	}
}

void LoadBalancingListener::onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers)
{
	wprintf(L"onAvailableRegions: %ls / %ls", availableRegions.toString().cstr(), availableRegionServers.toString().cstr());
	Console::get().writeLine(L"onAvailableRegions: " + availableRegions.toString() + L" / " + availableRegionServers.toString());
	// select first region from list
	Console::get().writeLine(L"selecting region: " + availableRegions[0]);
	//mpLbc->selectRegion(availableRegions[5]);
	mpLbc->selectRegion("jp");
}

//opRaiseEventでイベントが送信されるとこの関数が呼ばれる
void LoadBalancingListener::customEventAction(int playerNr, nByte eventCode, const Object& eventContentObj)
{
	//送られてきたデータ
	ExitGames::Common::Hashtable eventContent = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContentObj).getDataCopy();
	nByte Key;
	ExitGames::Common::Hashtable hashData;

	if (eventCode == 0) {
		Key = 1;
		int blueTeamScore, orangeTeamScore;
		hashData = (ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContent.getValue(Key))).getDataCopy();

		if (eventContent.getValue(Key)) {

			hashData = (ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContent.getValue(Key))).getDataCopy();

			if (hashData.getValue((nByte)1)) {
				blueTeamScore = (ExitGames::Common::ValueObject<nByte>(hashData.getValue((nByte)1))).getDataCopy();
			}
			if (hashData.getValue((nByte)2)) {
				orangeTeamScore = (ExitGames::Common::ValueObject<nByte>(hashData.getValue((nByte)2))).getDataCopy();
			}
			//printf("custom event action orange score %d, blue %d\n", orangeTeamScore, blueTeamScore);
		}
	}
	else if (eventCode == (m_playerNum == 1 ? 2 : 1)) {
		/*
		padデータ（ボタン、pad入力）を送信側から受け取る処理。
		*/
		//ネットワークパッドにデータを入れていく。
		g_netPadState.Gamepad.sThumbLX = ValueObject<SHORT>(eventContent.getValue(1)).getDataCopy();		//左スティックのX軸
		g_netPadState.Gamepad.sThumbLY = ValueObject<SHORT>(eventContent.getValue(2)).getDataCopy();		//左スティックのY軸
		g_netPadState.Gamepad.sThumbRX = ValueObject<SHORT>(eventContent.getValue(3)).getDataCopy();		//右スティックのX軸
		g_netPadState.Gamepad.sThumbRY = ValueObject<SHORT>(eventContent.getValue(4)).getDataCopy();		//右スティックのY軸
		g_netPadState.Gamepad.wButtons = (WORD)ValueObject<int>(eventContent.getValue(5)).getDataCopy();	//XYBA
		g_netPadState.Gamepad.bLeftTrigger = ValueObject<BYTE>(eventContent.getValue(6)).getDataCopy();
		g_netPadState.Gamepad.bRightTrigger = ValueObject<BYTE>(eventContent.getValue(7)).getDataCopy();
		int frameNo = ValueObject<int>(eventContent.getValue(8)).getDataCopy();
		//photonからパッドデータを取得した。
		m_isReceiveNetPadData = true;
		//ネットワークからとってきたパッド情報をバッファリングする。
		g_Pad[1].XInputStateBufferringFromNetPadData(frameNo);
		//パッドデータをバッファリングした時の、フレーム数。
		//printf("Buffering NetworkPadState frameNo = %d\n", frameNo);
		
		//if (fp != nullptr) {
		//	char text[4096];
		//	if (m_playerNum == 1) {
		//		//p1
		//		sprintf(
		//			text,
		//			"P1:xInputState.Gamepad.sThumbLX = %x receved \n"
		//			"P1:xInputState.Gamepad.wButtons = %x receved \n"
		//			"P1:xInputState.Gamepad.bLeftTrigger = %x receved \n"
		//			"P1:xInputState.Gamepad.bRightTrigger = %x receved \n"
		//			"FrameNo = %d\n",
		//			&g_netPadState.Gamepad.sThumbLX,
		//			&g_netPadState.Gamepad.wButtons,
		//			&g_netPadState.Gamepad.bLeftTrigger,
		//			&g_netPadState.Gamepad.bRightTrigger,
		//			frameNo
		//		);
		//	}
		//	else {
		//		//p2
		//		sprintf(
		//			text,
		//			"P2:xInputState.Gamepad.sThumbLX = %x receved \n"
		//			"P2:xInputState.Gamepad.wButtons = %x receved \n"
		//			"P2:xInputState.Gamepad.bLeftTrigger = %x receved \n"
		//			"P2:xInputState.Gamepad.bRightTrigger = %x receved \n"
		//			"FrameNo = %d\n",
		//			&g_netPadState.Gamepad.sThumbLX,
		//			&g_netPadState.Gamepad.wButtons,
		//			&g_netPadState.Gamepad.bLeftTrigger,
		//			&g_netPadState.Gamepad.bRightTrigger,
		//			frameNo
		//		);
		//	}

		//	//文字列かきこみ。
		//	fputs(text, fp);
		//}
	}
}

void LoadBalancingListener::disconnectReturn(void)
{
	updateState();
	Console::get().writeLine(L"disconnected");
	//printf("disconnected\n");
}

void LoadBalancingListener::createRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"room has been created");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"Warn: opCreateRoom() failed: " + errorString);
}

void LoadBalancingListener::joinOrCreateRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"room has been entered");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"Warn: opJoinOrCreateRoom() failed: " + errorString);
}

void LoadBalancingListener::joinRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"game room has been successfully joined");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"opJoinRoom() failed: " + errorString);
}

void LoadBalancingListener::joinRandomRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::NO_MATCH_FOUND)
		createRoom();
	else if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"game room has been successfully joined");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"opJoinRandomRoom() failed: " + errorString);
}

void LoadBalancingListener::leaveRoomReturn(int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
		Console::get().writeLine(L"game room has been successfully left");
	else
		Console::get().writeLine(L"opLeaveRoom() failed: " + errorString);
}

void LoadBalancingListener::gotQueuedReturn(void)
{
	updateState();
}

void LoadBalancingListener::joinLobbyReturn(void)
{
	Console::get().writeLine(L"joined lobby");
	updateState();
}

void LoadBalancingListener::leaveLobbyReturn(void)
{
	Console::get().writeLine(L"left lobby");
	updateState();
}

void LoadBalancingListener::onLobbyStatsUpdate(const JVector<LobbyStatsResponse>& res)
{
	Console::get().writeLine(L"===================== lobby stats update");
	for (unsigned int i = 0; i < res.getSize(); ++i)
		Console::get().writeLine(res[i].toString());

	// lobby stats request test
	JVector<LobbyStatsRequest> ls;
	ls.addElement(LobbyStatsRequest());
	ls.addElement(LobbyStatsRequest(L"AAA"));
	ls.addElement(LobbyStatsRequest(L"BBB"));
	ls.addElement(LobbyStatsRequest(L"CCC", LobbyType::DEFAULT));
	ls.addElement(LobbyStatsRequest(L"AAA", LobbyType::SQL_LOBBY));
	mpLbc->opLobbyStats(ls);
}

void LoadBalancingListener::onLobbyStatsResponse(const ExitGames::Common::JVector<LobbyStatsResponse>& res)
{
	Console::get().writeLine(L"===================== lobby stats response");
	for (unsigned int i = 0; i < res.getSize(); ++i)
		Console::get().writeLine(res[i].toString());
}

void LoadBalancingListener::onRoomListUpdate()
{
	const JVector<Room*>& rooms = mpLbc->getRoomList();
	JVector<JString> names(rooms.getSize());
	for (unsigned int i = 0; i < rooms.getSize(); ++i)
		names.addElement(rooms[i]->getName());
	//mpView->updateRoomList(names);
}

void LoadBalancingListener::onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes)
{
}

void LoadBalancingListener::updateState()
{
	int state = mpLbc->getState();
	mpView->updateState(state, PeerStatesStr[state], state == PeerStates::Joined ? mpLbc->getCurrentlyJoinedRoom().getName() : JString());
}


void LoadBalancingListener::afterRoomJoined(int localPlayerNr)
{
	Console::get().writeLine(JString(L"afterRoomJoined: localPlayerNr=") + localPlayerNr);
	MutableRoom& myRoom = mpLbc->getCurrentlyJoinedRoom();
	Hashtable props = myRoom.getCustomProperties();
}

void LoadBalancingListener::createRoom()
{
	JString name =
#ifdef __UNREAL__
		JString(L"UE-")
#else
		JString(L"native-")
#endif
		+ (rand() % 100);
	//Hashtable props;
	//props.put(L"m", mMap);
	//RoomOptions roomOptions(bool isVisible = true, bool isOpen = true, nByte maxPlayers = 2);
	//mpLbc->opCreateRoom(name, RoomOptions().setCustomRoomProperties(props));

	mpLbc->opCreateRoom(name, RoomOptions().setMaxPlayers(m_maxPlayer));
	Console::get().writeLine(L"Creating room " + name);
}

void LoadBalancingListener::connectReturn(int errorCode, const JString& errorString, const JString& region, const JString& cluster)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"connected to cluster " + cluster + L" of region " + region);
		mpLbc->opJoinRandomRoom(Hashtable(), m_maxPlayer);
	}
	else
		Console::get().writeLine(JString(L"Warn: connect failed ") + errorCode + L" " + errorString);
}

void LoadBalancingListener::service()
{
	//応答時間の取得？
	unsigned long t = GETTIMEMS();

	//遅延時間の割り出し？ 
	if ((t - lastUpdateTime) > PLAYER_UPDATE_INTERVAL_MS)
	{
		lastUpdateTime = t;
		if (mpLbc->getState() == PeerStates::Joined) {
			int a = 0;
		}
	}
}


void LoadBalancingListener::RaiseGameScore(int blue, int orange) {
	//mapみたいなkeyとvalueでできてるクラス
	Hashtable ev;
	//
	ExitGames::Common::Hashtable hash;

	//登録
	hash.put((nByte)1, (nByte)blue);
	//登録
	hash.put((nByte)2, (nByte)orange);

	const Object* Data = hash.getValue((nByte)1);

	auto b = hash.getValue((nByte)2);

	ev.put((nByte)1, hash);

	//データの送信
	//customEventActionが呼ばれる
	//送信なので自分のcustomEventActionは呼ばれない。
	mpLbc->opRaiseEvent(false, ev, 0);
	//printf("data raise event\n");
}

void LoadBalancingListener::putData(int i, float f) {
	playerData.put((nByte)i, (nByte)f);
}

void LoadBalancingListener::putData(nByte i, bool b) {
	playerData.put(i, b);
}

void LoadBalancingListener::RaisePlayerData(float Vx)
{
	//送るデータのコンテナ(eventContent)
	Hashtable hash;

	//右スティックの移動量を送る。
	hash.put(1, Vx);

	//データの送信
	//customEventActionが呼ばれる
	//送信なので自分のcustomEventActionは呼ばれない。
	mpLbc->opRaiseEvent(false, hash, 1);
	//printf("playerdata raise event\n");
}

void LoadBalancingListener::RaisePadData()
{
	//送るデータのコンテナ(eventContent)
	Hashtable hash;

	//自パッドのデータ送信。
	XINPUT_STATE& xInputState = g_Pad[0].GetXInputPadState();
	////右スティックの移動量を送る。
	//printf("xInputState.Gamepad.sThumbLX = %x\n", xInputState.Gamepad.sThumbLX);
	//printf("xInputState.Gamepad.sThumbLY = %x\n", xInputState.Gamepad.sThumbLY);
	hash.put(1, xInputState.Gamepad.sThumbLX);
	hash.put(2, xInputState.Gamepad.sThumbLY);
	hash.put(3, xInputState.Gamepad.sThumbRX);
	hash.put(4, xInputState.Gamepad.sThumbRY);
	//ボタンの情報を送る。
	hash.put(5, (int)xInputState.Gamepad.wButtons);
	hash.put(6, xInputState.Gamepad.bLeftTrigger);
	hash.put(7, xInputState.Gamepad.bRightTrigger);
	hash.put(8, Engine().GetTwoP_Pad().GetFrameNum());


	//if (fp != nullptr) {
	//	char text[4096];
	//	if (m_playerNum == 1) {
	//		//p1
	//		sprintf(
	//			text,
	//			"P1:xInputState.Gamepad.sThumbLX = %x sent \n"
	//			"P1:xInputState.Gamepad.wButtons = %x sent \n"
	//			"P1:xInputState.Gamepad.bLeftTrigger = %x sent \n"
	//			"P1:xInputState.Gamepad.bRightTrigger = %x sent \n"
	//			"FrameNo = %d\n",
	//			&xInputState.Gamepad.sThumbLX,
	//			&xInputState.Gamepad.wButtons,
	//			&xInputState.Gamepad.bLeftTrigger,
	//			&xInputState.Gamepad.bRightTrigger,
	//			Engine().GetTwoP_Pad().GetFrameNum()
	//		);
	//	}
	//	else {
	//		//p2
	//		sprintf(
	//			text,
	//			"P2:xInputState.Gamepad.sThumbLX = %x sent \n"
	//			"P2:xInputState.Gamepad.wButtons = %x sent \n"
	//			"P2:xInputState.Gamepad.bLeftTrigger = %x sent \n"
	//			"P2:xInputState.Gamepad.bRightTrigger = %x sent \n"
	//			"FrameNo = %d\n",
	//			&xInputState.Gamepad.sThumbLX,
	//			&xInputState.Gamepad.wButtons,
	//			&xInputState.Gamepad.bLeftTrigger,
	//			&xInputState.Gamepad.bRightTrigger,
	//			Engine().GetTwoP_Pad().GetFrameNum()
	//		);
	//	}

	//	//文字列かきこみ。
	//	fputs(text, fp);
	//}


	//データの送信
	//customEventActionが呼ばれる
	//送信なので自分のcustomEventActionは呼ばれない。
	bool result = mpLbc->opRaiseEvent(false, hash, m_playerNum);
	//printf("%dtimes send\n", ++m_sentTimes);
	if (result == false) {
		//printf("送信失敗\n");
	}
	//printf("playerdata raise event\n");
}