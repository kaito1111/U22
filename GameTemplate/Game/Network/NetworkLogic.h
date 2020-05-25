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
	/// �V���L�J�A�A�A�A�A�A
	/// </summary>
	void Start();
	/// <summary>
	/// �T�[�o�[�ɓ���
	/// <para>photon�g���O�ɌĂяo�����ƁB</para>
	/// </summary>
	void Connect();
	/// <summary>
	/// �T�[�o�[����ؒf
	/// <para>photon�̎g�p���I������Ƃ��ɌĂяo�����ƁB</para>
	/// </summary>
	void Disconnect();
	/// <summary>
	/// �ꉞ���Ă�p�ӂ��Ă郋�[���쐬�֐��B
	/// <para>��{CreateRoomOrJoin��OK</para>
	/// </summary>
	void CreateRoom();
	/// <summary>
	/// �ꉞ���Ă�p�ӂ��Ă郋�[���Q���֐��B
	/// <para>��{CreateRoomOrJoin��OK</para>
	/// </summary>
	void Join();
	/// <summary>
	/// ���[���̍쐬
	/// </summary>
	/// <param name="roomName">�����̖��O</param>
	/// <param name="maxPlayer">�ő�Player��</param>
	void CreateRoom(const JString& roomName, nByte maxPlayer);
	/// <summary>
	/// ���[���쐬�܂��͎Q��
	/// <para>���[��������Ă���Ȃ�Q���A����Ă��Ȃ��Ȃ�쐬</para>
	/// <para>��{�I�ɍ쐬�A�Q���͂��̊֐����g���̂ł����Ǝv���܂��B</para>
	/// </summary>
	/// <param name="roomName">���[���̖��O</param>
	/// <param name="maxPlayers">�ő�Player��</param>
	void CreateRoomOrJoin(const JString& roomName, nByte maxPlayers = 5, bool CreateRoom = true);
	/// <summary>
	/// �T�[�o�[�̍X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// ���X�i�[�̎擾
	/// </summary>
	/// <returns>���X�i�[</returns>
	LoadBalancingListener* GetLBL()
	{
		return mpLbl;
	}

	/// <summary>
	/// �N���C�A���g�̎擾
	/// </summary>
	/// <returns>�N���C�A���g</returns>
	Client* GetLBC() {
		return mpLbc;
	}
private:
	ExitGames::LoadBalancing::Client* mpLbc;	//�N���C�A���g
	LoadBalancingListener* mpLbl = nullptr;		//lb���X�i�[
	TestView m_testview;
};

static inline NetworkLogic& INetworkLogic() {
	return NetworkLogic::GetInstance();
}