#pragma once
#include "graphics/2D/Sprite.h"
#include "graphics/2D/SpriteRender.h"

class Game : public IGameObject
{
public:
	Game();
	~Game();

private:
	/// <summary>
	/// �X�^�[�g
	/// </summary>
	/// <returns></returns>
	bool Start()override;
	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;
	/// <summary>
	/// �T���v��
	/// <para>�������ς��A�T���v�������ς�</para>
	/// </summary>
	void Sample();						
	SpriteRender* m_test=nullptr;		//�X�v���C�g�����_�[
	SoundSource	m_se;					//�T�E���h�\�[�X
	Effect* effect = nullptr;			//�G�t�F�N�g
};