#pragma once
#include "SampleGround.h"
#include "Sample/DebugMan.h"

static const float GRAVITY = -1.0f;

class SampleScene : public IGameObject
{
public:
	SampleScene();		//コンストラクタ
	~SampleScene();	//デストラクタ
	bool Start() override { return true; } ;		//スタート
	void Update() override;							//アップデート
	//static const float GRAVITY;						//重力は共通  重力はSceneの寿命切れたらいらない。

private:
	SampleGround* m_ground = nullptr;
	DebugMan* m_debugMan = nullptr;
	
};
//const float SampleScene::GRAVITY = -1.0f;

