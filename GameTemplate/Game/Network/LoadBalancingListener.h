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
	/// <summary>
	/// �v���C���[�̏���]��
	/// </summary>
	void RaisePlayerData();

public:

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
	/// <summary>
	/// �C�x���g�̃A�N�V����
	/// <para>�f�[�^�̑��M�Ɏg���Ă��������B</para>
	/// <para>opRaiseEvent���ĂԂƂ��̊֐����Ă΂�܂��B</para>
	/// </summary>
	/// <remarks>
	/// ���M����customEventAction�͌Ă΂�܂���B
	/// ��M����customEventAction���Ă΂�܂��B
	/// </remarks>
	/// <param name="playerNr"></param>
	/// <param name="eventCode"></param>
	/// <param name="eventContent"></param>
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
	/// <summary>
	/// ���X�g�ɐς�
	/// </summary>
	/// <param name="i">�L�[</param>
	/// <param name="f">����l(float)</param>
	void putData(nByte i, float f);
	/// <summary>
	/// ���X�g�ɐς�
	/// </summary>
	/// <param name="i">�L�[</param>
	/// <param name="f">����l(float)</param>
	void putData(nByte i, bool b);

	int GetplayerNum() {
		return m_playerNum;
	}
	/// <summary>
	/// �p�b�h�̒l���Ƃ�
	/// </summary>
	/// <param name="padNo">�ق����p�b�h�̔ԍ�</param>
	/// <returns>�p�b�h�̒l</returns>
	int GetPlayerPadData(int padNo) {
		return Trigger[padNo];
	}
	int GetPlayerStickLXData() {
		if (padLX != 0) {
			printf("tyu");
		}
		return padLX;
	}
	int GetPlayerStickLYData() {
		return padLY;
	}
	int GetPlayerStickRXData() {
		if (padRX != 0) {
			printf("tyu");
		}
		return padRX;
	}
	int GetPlayerStickRYData() {
		return padRY;
	}
	int& GetPlayerNum() {
		return m_playerNum;
	}
	/// <summary>
	/// ���[�U�[�̃l�[�����擾
	/// </summary>
	/// <returns></returns>
	const JString& GetUser(int playerNo)
	{
		return m_UserData[playerNo].getUserID();
	}
private:
	ExitGames::LoadBalancing::Client* mpLbc;
	int m_Num = 0;
	AuthenticationValues m_UserData[2];	//User�̃f�[�^(�ԍ�)
	Hashtable playerData;				//�v���C���[���i�[�p
	BaseView* mpView;
	int m_maxPlayer = 2;
	unsigned long lastUpdateTime;
	int m_playerNum = 0;					//�t�H�g���̍ő�Q���l���A���ꂪ�����̎Q���ԍ��ɂȂ�
	//pad�̓���
	float padLX = 0, padLY = 0, padRX = 0, padRY = 0;
	bool m_once = false;		//��x�̂�
	//�g���K�[
	int Trigger[16] = {};
};

