/// <summary>
/// ��������������X�i�[�N���X
/// </summary>
/// <remarks>
/// sdk...Demo_typeSupport���Q�l�ɍ쐬
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
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="lib">photon���C�u����</param>
			/// <param name="logger">CommonLogger</param>
			myListener(CPhotonlib& lib, ExitGames::Common::Logger& logger);
			/// <summary>
			/// �f�X�g���N�^
			/// </summary>
			virtual ~myListener(void);

		private:
			/// <summary>
			/// �f�o�b�O��\�����������̂�����
			/// </summary>

			/// <summary>
			/// �f�o�b�O�̌��ʕԂ��Ă������
			/// <para>�R�����g�s�\���Ȃ̂ŗ���������ǉ����邱��</para>
			/// </summary>
			/// <param name="debugLevel"></param>
			/// <param name="string"></param>
			virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string);

		private:
			/// <summary>
			/// ���������G���[�n���h��������
			/// </summary>

			/// <summary>
			/// �ڑ����̃G���[�̌���
			/// </summary>
			/// <param name="errorCode">�G���[�R�[�h</param>
			virtual void connectionErrorReturn(int errorCode);
			/// <summary>
			/// �N���C�A���g�̃G���[����
			/// </summary>
			/// <param name="errorCode">�G���[�R�[�h</param>
			virtual void clientErrorReturn(int errorCode);
			/// <summary>
			/// �x��
			/// </summary>
			/// <param name="warningCode">�x���̃R�[�h</param>
			virtual void warningReturn(int warningCode);
			/// <summary>
			/// �T�[�o�[�̃G���[����
			/// </summary>
			/// <param name="errorCode">�G���[�R�[�h</param>
			virtual void serverErrorReturn(int errorCode);

		private:
			/// <summary>
			/// �v���C���[�̓���̓���ŌĂ΂��C�x���g
			/// </summary>

			virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);

			virtual void leaveRoomEventAction(int playerNr, bool isInactive);

			virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);

		private:
			/// <summary>
			/// PhotonLoadBalancing�T�[�o�ł̃R�[���o�b�N
			/// </summary>

			/// <summary>
			/// �ڑ��̃R�[���o�b�N
			/// </summary>
			/// <param name="errorCode">�G���[�R�[�h</param>
			/// <param name="errorString">�G���[���b�Z�[�W�H</param>
			/// <param name="region">�̈�H�H</param>
			/// <param name="cluster">�N���X�^�[</param>
			virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster);
			/// <summary>
			/// �ؒf�̃R�[���o�b�N
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

