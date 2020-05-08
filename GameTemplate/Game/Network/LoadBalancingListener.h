#pragma once
#include "LoadBalancing-cpp/inc/Client.h"
#include "BaseView.h"

//プレイヤーの応答速度間隔
#define PLAYER_UPDATE_INTERVAL_MS 500

//名前空間定義
using namespace ExitGames::Common;
using namespace ExitGames::LoadBalancing;

/// <summary>
/// リスナークラス
/// </summary>
/// <remarks>
/// 各処理時のエラーや動作に対しイベントを起こす監視者
/// 分類としてはマネージャ系列みたいな感じだと思う。
/// </remarks>
class LoadBalancingListener : public ExitGames::LoadBalancing::Listener
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pView">基底ビュー</param>
	LoadBalancingListener(BaseView* pView);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~LoadBalancingListener();
	/// <summary>
	/// LBClientの設定
	/// </summary>
	/// <param name="pLbc">LBClient</param>
	void setLBC(ExitGames::LoadBalancing::Client* pLbc);
	/// <summary>
	/// サーバーに接続
	/// </summary>
	/// <param name="userName">ユーザーネーム</param>
	void connect(const ExitGames::Common::JString& userName);
	/// <summary>
	/// サーバーから切断
	/// </summary>
	void disconnect();
	/// <summary>
	/// ルームの作成
	/// </summary>
	void createRoom(void);
	/// <summary>
	/// Updateで呼び出さないといけないやつ
	/// </summary>
	/// <remarks>
	/// 応答速度の遅延みてるのかな？
	/// </remarks>
	void service();
	//Test
	void RaiseGameScore(int blue, int orange);

private:

	//From Common::BaseListener

	// receive and print out debug out here
	virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string);

	//From LoadBalancing::LoadBalancingListener

	// implement your error-handling here
	virtual void connectionErrorReturn(int errorCode);
	virtual void clientErrorReturn(int errorCode);
	virtual void warningReturn(int warningCode);
	virtual void serverErrorReturn(int errorCode);
	// events, triggered by certain operations of all players in the same room
	virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
	virtual void leaveRoomEventAction(int playerNr, bool isInactive);
	virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);

	// callbacks for operations on PhotonLoadBalancing server
	virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster);
	virtual void disconnectReturn(void);
	virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void gotQueuedReturn(void);
	virtual void joinLobbyReturn(void);
	virtual void leaveLobbyReturn(void);
	virtual void onRoomListUpdate(void);
	virtual void onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
	virtual void onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
	virtual void onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes);
	virtual void onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& /*availableRegions*/, const ExitGames::Common::JVector<ExitGames::Common::JString>&) override;
	void updateState(void);
	void afterRoomJoined(int localPlayerNr);

private:
	ExitGames::LoadBalancing::Client* mpLbc;
	BaseView* mpView;
	int m_maxPlayer = 2;
	unsigned long lastUpdateTime;
};

