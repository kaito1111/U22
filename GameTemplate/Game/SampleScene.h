#pragma once

#include "Sample/DebugMan.h"

class SampleGround;

static const float GRAVITY = -1.0f;

class SampleScene : public IGameObject
{
public:
	SampleScene();		//コンストラクタ
	~SampleScene();	//デストラクタ
	bool Start() override;		//スタート
	void Update() override;							//アップデート
	void PostRender();
	//static const float GRAVITY;						//重力は共通  重力はSceneの寿命切れたらいらない。

private:
	SampleGround* m_ground = nullptr;		
	DebugMan* m_debugMan = nullptr;
	CVector3 Target = CVector3::Zero();
	Sprite m_copyMainRtToFrameBufferSprite;
};
//const float SampleScene::GRAVITY = -1.0f;

