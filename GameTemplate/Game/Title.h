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
	SpriteRender m_sprite;             //スプライト
	CVector2 m_spritePos;              //スプライトの座標。
	const int stageMax = 2;            //ステージの数.上限
	int nowStage = 0;                  //現在選択しているステージ 
	bool LStageChange = false;          //ステージを切り替えるフラグ
	bool RStageChange = false;
	const CVector3 littleScale = { 0.1f,0.1f,0.1f };//選ばれてないステージのサイズ
	const CVector3 halfScale = { 0.5f,0.5f,0.5f };

	
};