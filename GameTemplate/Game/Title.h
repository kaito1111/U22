#pragma once
class stageObjectJenerator;
class TitleStage;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void stageSelect();
private:
	TitleStage* titleStage = nullptr;
	stageObjectJenerator* generator;
	SpriteRender m_sprite;             //�X�v���C�g
	CVector2 m_spritePos;              //�X�v���C�g�̍��W�B
	const int stageMax = 2;            //�X�e�[�W�̐�.���
	int nowStage = 0;                  //���ݑI�����Ă���X�e�[�W 
	bool LStageChange = false;          //�X�e�[�W��؂�ւ���t���O
	bool RStageChange = false;
	const CVector3 littleScale = { 0.1f,0.1f,0.1f };//�I�΂�ĂȂ��X�e�[�W�̃T�C�Y
	const CVector3 halfScale = { 0.5f,0.5f,0.5f };

	
};