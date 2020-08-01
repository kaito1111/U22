#pragma once
class PlayerPad;
class NetworkPad;

class TwoP_Pad: public IGameObject
{
	//using NetworkPad = PlayerPad;
public:
	TwoP_Pad();
	~TwoP_Pad();

	void Update() override;

	//�V���O���g��
	static TwoP_Pad& GetInstance()
	{
		static TwoP_Pad Instance;
		return Instance;
	}

	/// <summary>
	/// �v���C���[�p�b�h�̎擾
	/// </summary>
	/// <returns></returns>
	PlayerPad* GetPPad()
	{
		return m_playerPad;
	}
	/// <summary>
	/// �l�b�g���[�N�p�b�h�̎擾
	/// </summary>
	/// <returns></returns>
	NetworkPad* GetNPad()
	{
		return m_networkPad;
	}

private:
	enum KeyState
	{
		Jump,
		MagN,
		MagS,
		NoMag,
		ShotN,
		ShotS,
		Start
	};
	void PostRender();
	Sprite m_copyMainRtToFrameBufferSprite;	//���C��RTV�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g
	SpriteRender* m_ManualSprite = nullptr;

	//Player* player[2] = {};
	bool UpdateStop = true;			//Update���~�߂�t���Ofalse��Update����B
	int m_PlayerPadNum = 0;

	//bool Start()override;
	bool NewGOPlayer = false;		//�v���C���[��NewGO���邩�ǂ���
	float m_Manual_W = 0.0f;
	SpriteRender* m_ButtonSprite = nullptr;

	PlayerPad* m_playerPad;			//�v���C���[�̃p�b�h
	NetworkPad* m_networkPad;		//�l�b�g���[�N�̃p�b�h
};

/// <summary>
/// TwoP_Pad�̃C���X�^���X�擾
/// </summary>
/// <returns></returns>
static inline TwoP_Pad& twoP_Pad()
{
	return TwoP_Pad::GetInstance();
}
