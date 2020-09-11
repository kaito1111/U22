#include "stdafx.h"
#include "NetworkLogic.h"
#include "LoadBalancingListener.h"
#include "LoadBalancing-cpp/inc/Client.h"
#include "TestView.h"
#include "Console.h"

/// <summary>
/// photon�l�b�g���[�N�𓮂������
/// </summary>
/// <remarks>
/// ���󂵂���l�b�g���[�N�ϗ�
/// </remarks>

//photon��appID photon���Ⴄ�T�[�o�[�̏ꍇ�A�Ή�����appID�����
static const ExitGames::Common::JString appID = L"62a270e7-a9c5-480d-bc87-4f66ceeee673";
//photon�T�[�o�[��appVersion
static const ExitGames::Common::JString appVersion = L"1.0";
//photon�ō�����T�[�o�[�l�[�� �Ⴄ�T�[�o�[�̏ꍇ�A�Ή������T�[�o�[�������
static ExitGames::Common::JString gameName = L"photonTest";

//static const ExitGames::Common::JString PLAYER_NAME = L"user";
static const int MAX_SENDCOUNT = 100;

//���O��Ԓ�`
using namespace ExitGames::LoadBalancing;
using namespace ExitGames::Common;
using namespace ExitGames::Photon;

/// <summary>
/// �f�X�g���N�^
/// <para>Start�ō쐬����Listener��Client�̍폜</para>
/// </summary>
NetworkLogic::~NetworkLogic()
{
	delete mpLbl;
	delete mpLbc;
}

/// <summary>
/// �T�[�o�[�ɐڑ�
/// <para>NV + �o�ߎ��ԂŒl���擾�������̂�PlayerID��</para>
/// </summary>
void NetworkLogic::Connect() {
	mpLbl->connect(JString(L"NV") + GETTIMEMS());
}

/// <summary>
/// �T�[�o�[����ؒf
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
/// ����������
/// </summary>
void NetworkLogic::Start() {
	//lb���X�i�[�̍쐬
	mpLbl = new LoadBalancingListener(&m_testview);
	//�N���C�A���g�̍쐬
	mpLbc = new Client(*mpLbl, appID, appVersion, ExitGames::Photon::ConnectionProtocol::TCP,true, RegionSelectionMode::BEST);
	//�f�o�b�O�o�̓��x���̐ݒ�H
	mpLbc->setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS));
	//�x�[�X���X�i�[�̐ݒ�
	ExitGames::Common::Base::setListener(mpLbl);
	//�x�[�X�f�o�b�O�o�̓��x���̐ݒ�H
	ExitGames::Common::Base::setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS));
	//	pLbc->setCRCEnabled(true);
	//�N���C�A���g�̐ݒ�
	mpLbl->setLBC(mpLbc);
	//�ʐM�̏�Ԃ�True�ɐݒ�@�ʐM�J�n�̍��}�Ă��ȁH
	mpLbc->setTrafficStatsEnabled(true);
	//�ڑ���
//	Console::get().writeLine(L"LBC: connecting...");
	//�ڑ�(PlayerID)
	mpLbl->connect(JString(L"NV") + GETTIMEMS());
}


void NetworkLogic::Update() {
	//�N���C�A���g�̍X�V
	mpLbc->service();
	//���X�i�[�̍X�V
	mpLbl->service();
}

