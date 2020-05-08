#pragma once
#include "LoadBalancing-cpp/inc/Client.h"
#include "BaseView.h"

//�v���C���[�̉������x�Ԋu
#define PLAYER_UPDATE_INTERVAL_MS 500

//���O��Ԓ�`
using namespace ExitGames::Common;
using namespace ExitGames::LoadBalancing;

/// <summary>
/// ���X�i�[�N���X
/// </summary>
/// <remarks>
/// �e�������̃G���[�⓮��ɑ΂��C�x���g���N�����Ď���
/// ���ނƂ��Ă̓}�l�[�W���n��݂����Ȋ������Ǝv���B
/// </remarks>
class LoadBalancingListener : public ExitGames::LoadBalancing::Listener
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pView">���r���[</param>
	LoadBalancingListener(BaseView* pView);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~LoadBalancingListener();
	/// <summary>
	/// LBClient�̐ݒ�
	/// </summary>
	/// <param name="pLbc">LBClient</param>
	void setLBC(ExitGames::LoadBalancing::Client* pLbc);
	/// <summary>
	/// �T�[�o�[�ɐڑ�
	/// </summary>
	/// <param name="userName">���[�U�[�l�[��</param>
	void connect(const ExitGames::Common::JString& userName);
	/// <summary>
	/// �T�[�o�[����ؒf
	/// </summary>
	void disconnect();
	/// <summary>
	/// ���[���̍쐬
	/// </summary>
	void createRoom(void);
	/// <summary>
	/// Update�ŌĂяo���Ȃ��Ƃ����Ȃ����
	/// </summary>
	/// <remarks>
	/// �������x�̒x���݂Ă�̂��ȁH
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

