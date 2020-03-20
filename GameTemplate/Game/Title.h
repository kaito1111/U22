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
	SpriteRender m_sprite;             //スプライト
	CVector2 m_spritePos;              //スプライトの座標。
	const int stageMax = 2;            //ステージの数.上限
	int nowStage = 0;                  //現在選択しているステージ 
	bool LStageChange = false;          //ステージを切り替えるフラグ
	bool RStageChange = false;
	const CVector3 littleScale = { 0.1f,0.1f,0.1f };//選ばれてないステージのサイズ
	const CVector3 halfScale = { 0.5f,0.5f,0.5f };

	//ステージ1つ目。二つ目以降はコピーして後ろに数字を足してってね。
	SkinModel m_model;                        //モデル
	CVector3 m_pos = CVector3::Zero();        //ステージの座標。
	CVector3 m_scale = halfScale;             //拡縮

	SkinModel m_model2;                        //モデル
	CVector3 m_pos2 = {2000.0f,0.0f,0.0f};     //ステージの座標。
	CVector3 m_scale2 = littleScale;           //拡縮

	



	

	
};