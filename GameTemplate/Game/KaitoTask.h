#pragma once
//class TitleStage;

#include "Player.h"
class GameCamera;
class KaitoTask : public IGameObject
{
public:
	KaitoTask();
	~KaitoTask();

	/// <summary>
	/// �v�������_�[
	/// <para>shadowMap�֘A�̏���</para>
	/// </summary>
	/// <remarks>
	/// Player�N���X�ɂ�����Player1����SkinModel�����Ƃ�Ȃ��̂�
	/// �����ɏ����܂��B
	/// </remarks>
	void PreRender();

private:
	//TitleStage*7
	GameCamera* m_GameCamera = nullptr;
    Player* m_Player[2] = {};

};