#include "stdafx.h"
#include "BaseView.h"
#include "OutputListener.h"
#include "LoadBalancingListener.h"
#include "NetworkLogic.h"
#include "Console.h"
#include "TestView.h"
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
	//delete mpView;
}

void LoadBalancingListener::setLBC(ExitGames::LoadBalancing::Client* pLbc)
{
	this->mpLbc = pLbc;
}

void LoadBalancingListener::connect(const JString& userName)
{
	mpLbc->connect(AuthenticationValues().setUserID(JString() + GETTIMEMS()), userName);
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
	Console::get().writeLine(JString("player ") + playerNr + L" " + player.getName() + L" has joined the game");
	if (m_playerNum == 20) 
	{ 
		m_playerNum = playerNr; 
	}
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
	ExitGames::Common::Hashtable eventContent = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContentObj).getDataCopy();

	switch (eventCode) {
	case 0:
		//nByte Key = 1;
		//int blueTeamScore, orangeTeamScore;
		//ExitGames::Common::Hashtable hashData;
		//hashData = (ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContent.getValue(Key))).getDataCopy();

		//if (eventContent.getValue(Key)) {

		//	hashData = (ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContent.getValue(Key))).getDataCopy();

		//	if (hashData.getValue((nByte)1)) {
		//		blueTeamScore = (ExitGames::Common::ValueObject<nByte>(hashData.getValue((nByte)1))).getDataCopy();
		//	}
		//	if (hashData.getValue((nByte)2)) {
		//		orangeTeamScore = (ExitGames::Common::ValueObject<nByte>(hashData.getValue((nByte)2))).getDataCopy();
		//	}
		//	printf("custom event action orange score %d, blue %d\n", orangeTeamScore, blueTeamScore);
		//}
		break;
	case 1:
		/*
		padデータ（ボタン、pad入力）を送信側から受け取る処理。
		*/

		//キーの初期化
		nByte Key = 1;


		Hashtable playerData;

		playerData = (ValueObject<Hashtable>(eventContent.getValue(Key))).getDataCopy();
		auto a = eventContent.getValue(Key);
		//イベント
		if (eventContent.getValue(Key)) 
		{
			playerData = (ValueObject<Hashtable>(eventContent.getValue(Key))).getDataCopy();
			for (int i = 0; i < 15; i++) 
			{
				if (playerData.getValue((nByte)i))
				{
					Trigger[i] = ValueObject<nByte>(playerData.getValue((nByte)i)).getDataCopy();
				}
			}

			for (int i = 16; i < 20; i++)
			{
				if (playerData.getValue((nByte)i))
				{
					if (playerData.getValue((nByte)i))
					{
						if (i == 16) 
						{
							padLX = ValueObject<nByte>(playerData.getValue((nByte)i++)).getDataCopy();
						}
						if (i == 17)
						{
							padLY = ValueObject<nByte>(playerData.getValue((nByte)i++)).getDataCopy();
						}
						if (i == 18) 
						{
							padRX = ValueObject<nByte>(playerData.getValue((nByte)i++)).getDataCopy();
						}
						if (i == 19)
						{
							padRY = ValueObject<nByte>(playerData.getValue((nByte)i++)).getDataCopy();
						}
					}
				}
			}
		}
		break;
	}
}

void LoadBalancingListener::disconnectReturn(void)
{
	updateState();
	Console::get().writeLine(L"disconnected");
	printf("disconnected\n");
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

	auto a = hash.getValue((nByte)1);

	auto b = hash.getValue((nByte)2);

	ev.put((nByte)1, hash);

	//データの送信
	//customEventActionが呼ばれる
	//送信なので自分のcustomEventActionは呼ばれない。
	mpLbc->opRaiseEvent(false, ev, 0);
	printf("data raise event\n");
}

void LoadBalancingListener::putData(nByte i, float f) {
	playerData.put(i, f);
}

void LoadBalancingListener::putData(nByte i, bool b) {
	playerData.put(i, b);
}

void LoadBalancingListener::RaisePlayerData()
{
	//送るデータのコンテナ(eventContent)
	Hashtable ev;

	//コンテナにplayerデータの情報を積む
	ev.put((nByte)1, playerData);

	//データの送信
	//customEventActionが呼ばれる
	//送信なので自分のcustomEventActionは呼ばれない。
	mpLbc->opRaiseEvent(false, ev, 1);
	//printf("playerdata raise event\n");
}
