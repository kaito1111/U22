#pragma once
#include "LoadBalancingListener.h"
#include "LoadBalancing-cpp/inc/Client.h"
#include "TestView.h"

class TestView;


class NetworkLogic// : Noncopyable
{
public:
	static NetworkLogic& GetInstance() {
		static NetworkLogic instance;
		return instance;
	}
	~NetworkLogic();
	/// <summary>
	/// ショキカアアアアアア
	/// </summary>
	void Start();
	/// <summary>
	/// サーバーに入場
	/// <para>photon使う前に呼び出すこと。</para>
	/// </summary>
	void Connect();
	/// <summary>
	/// サーバーから切断
	/// <para>photonの使用を終了するときに呼び出すこと。</para>
	/// </summary>
	void Disconnect();
	/// <summary>
	/// 一応がてら用意してるルーム作成関数。
	/// <para>基本CreateRoomOrJoinでOK</para>
	/// </summary>
	void CreateRoom();
	/// <summary>
	/// 一応がてら用意してるルーム参加関数。
	/// <para>基本CreateRoomOrJoinでOK</para>
	/// </summary>
	void Join();
	/// <summary>
	/// ルームの作成
	/// </summary>
	/// <param name="roomName">部屋の名前</param>
	/// <param name="maxPlayer">最大Player数</param>
	void CreateRoom(const JString& roomName, nByte maxPlayer);
	/// <summary>
	/// ルーム作成または参加
	/// <para>ルームが作られているなら参加、作られていないなら作成</para>
	/// <para>基本的に作成、参加はこの関数を使うのでいいと思います。</para>
	/// </summary>
	/// <param name="roomName">ルームの名前</param>
	/// <param name="maxPlayers">最大Player数</param>
	void CreateRoomOrJoin(const JString& roomName, nByte maxPlayers = 5, bool CreateRoom = true);
	/// <summary>
	/// サーバーの更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// リスナーの取得
	/// </summary>
	/// <returns>リスナー</returns>
	LoadBalancingListener* GetLBL()
	{
		return mpLbl;
	}

	/// <summary>
	/// クライアントの取得
	/// </summary>
	/// <returns>クライアント</returns>
	Client* GetLBC() {
		return mpLbc;
	}
private:
	ExitGames::LoadBalancing::Client* mpLbc;	//クライアント
	LoadBalancingListener* mpLbl = nullptr;		//lbリスナー
	TestView m_testview;
};

static inline NetworkLogic& INetworkLogic() {
	return NetworkLogic::GetInstance();
}