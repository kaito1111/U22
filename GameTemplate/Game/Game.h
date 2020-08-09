#pragma once
#include "graphics/2D/Sprite.h"
#include "graphics/2D/SpriteRender.h"
#include "Stage.h"
class KaitoTask;

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
	/// �`��
	/// </summary>
	void Draw();
public:
	/// <summary>
	/// �Q�[���̃C���X�^���X�擾
	/// </summary>
	/// <returns></returns>
	static Game& getGameInstance()
	{
		static Game Instance;
		return Instance;
	}
private:
	SpriteRender* m_test = nullptr;							//�X�v���C�g�����_�[
	KaitoTask* m_task = nullptr;							//�v���C���[����Ă�N���X�B
	Stage* stage = nullptr;									//�X�e�[�W
};

static inline Game& GameObj()
{
	return Game::getGameInstance();
}