/// <summary>
/// 自分が作ったリスナークラス
/// </summary>
/// <remarks>
/// sdk...Demo_typeSupportを参考に作成
/// </remarks>

#include "LoadBalancing-cpp/inc/Client.h"
class CPhotonlib;

#pragma once

//namespace ExitGames
//{
//	namespace LoadBalancing
//	{
		class myListener : public ExitGames::LoadBalancing::Listener
		{
		/*public:
			/// <summary>
			/// コンストラクタ
			/// </summary>
			/// <param name="lib">photonライブラリ</param>
			/// <param name="logger">CommonLogger</param>
			myListener(CPhotonlib& lib, ExitGames::Common::Logger& logger);
			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~myListener(void);

		private:
			/// <summary>
			/// デバッグを表示したいものをかく
			/// </summary>

			/// <summary>
			/// デバッグの結果返してくれるやつ
			/// <para>コメント不十分なので理解したら追加すること</para>
			/// </summary>
			/// <param name="debugLevel"></param>
			/// <param name="string"></param>
			virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string);

		private:
			/// <summary>
			/// 実装したエラーハンドルをかく
			/// </summary>

			/// <summary>
			/// 接続時のエラーの結果
			/// </summary>
			/// <param name="errorCode">エラーコード</param>
			virtual void connectionErrorReturn(int errorCode);
			/// <summary>
			/// クライアントのエラー結果
			/// </summary>
			/// <param name="errorCode">エラーコード</param>
			virtual void clientErrorReturn(int errorCode);
			/// <summary>
			/// 警告
			/// </summary>
			/// <param name="warningCode">警告のコード</param>
			virtual void warningReturn(int warningCode);
			/// <summary>
			/// サーバーのエラー結果
			/// </summary>
			/// <param name="errorCode">エラーコード</param>
			virtual void serverErrorReturn(int errorCode);

		private:
			/// <summary>
			/// プレイヤーの特定の動作で呼ばれるイベント
			/// </summary>

			virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);

			virtual void leaveRoomEventAction(int playerNr, bool isInactive);

			virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);

		private:
			/// <summary>
			/// PhotonLoadBalancingサーバでのコールバック
			/// </summary>

			/// <summary>
			/// 接続のコールバック
			/// </summary>
			/// <param name="errorCode">エラーコード</param>
			/// <param name="errorString">エラーメッセージ？</param>
			/// <param name="region">領域？？</param>
			/// <param name="cluster">クラスター</param>
			virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster);
			/// <summary>
			/// 切断のコールバック
			/// </summary>
			virtual void disconnectReturn(void);

			virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);

			virtual void joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);

			virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);

			virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);

			virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);

			virtual void joinLobbyReturn(void);

			virtual void leaveLobbyReturn(void);

		private:
			CPhotonlib& cPhotonlib;
			ExitGames::Common::Logger& mLogger;*/
		};
//	}
//}

