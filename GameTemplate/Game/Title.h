#pragma once
class stageObjectJenerator;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void stageSelect();
private:
	stageObjectJenerator* generator;
	SpriteRender m_sprite;             //�X�v���C�g
	CVector2 m_spritePos;              //�X�v���C�g�̍��W�B
	const int stageMax = 2;            //�X�e�[�W�̐�.���
	int nowStage = 0;                  //���ݑI�����Ă���X�e�[�W 
	bool LStageChange = false;          //�X�e�[�W��؂�ւ���t���O
	bool RStageChange = false;
	const CVector3 littleScale = { 0.1f,0.1f,0.1f };//�I�΂�ĂȂ��X�e�[�W�̃T�C�Y
	const CVector3 halfScale = { 0.5f,0.5f,0.5f };

	//�X�e�[�W1�ځB��ڈȍ~�̓R�s�[���Č��ɐ����𑫂��Ă��ĂˁB
	SkinModel m_model;                        //���f��
	CVector3 m_pos = CVector3::Zero();        //�X�e�[�W�̍��W�B
	CVector3 m_scale = halfScale;             //�g�k

	SkinModel m_model2;                        //���f��
	CVector3 m_pos2 = {2000.0f,0.0f,0.0f};     //�X�e�[�W�̍��W�B
	CVector3 m_scale2 = littleScale;           //�g�k

	



	

	
};