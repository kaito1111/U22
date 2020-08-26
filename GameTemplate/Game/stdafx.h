#pragma once

static constexpr int NUM_SHADOW_MAP = 3;			//シャドウマップの数

#include <WinSock2.h>
#include <windows.h>
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
//D3Dcompiler.hより下にすると再定義おこります
//#include "Common-cpp/inc/Common.h"
#include <map>
#include <functional>
#include <algorithm>
#include <stack>
//オーディオのインクルード
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>


#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

//エフェクサー
#include "Effekseer.h"
#include "EffekseerRendererDX11.h"

//DirectXTKのインクルードファイル。
#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"

#include "photon/Common-cpp/inc/Common.h"
#include "photon/LoadBalancing-cpp/inc/Client.h"

#include "physics/Physics.h"
#include "HID/Pad.h"

#include "math/Vector.h"
#include "math/Matrix.h"

//エンジン系
#include "myEngine.h"
#include "graphics/GraphicsEngine.h"
#include "Sound/SoundEngine.h"

#include "util/tkStopwatch.h"

#include "graphics/SkinModel.h"
#include "graphics/Skeleton.h"
#include "graphics/SkinModelShaderConst.h"

#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "SkinModelRender.h"


#include "GameObject/GameObjectManager.h"
#include "GameObject/IGameObject.h"

#include "graphics/Camera.h"

#include "Effect/Effect.h"
#include "PostEffect/PostEffect.h"

#include "graphics/2D/Font.h"
#include "graphics/2D/FontRender.h"

#include "sound/SoundSource.h"

#include "Shadow/ShadowMap.h"

//#include "photon/LoadBalancing-cpp/inc/friendinfo.h"
//#include "Photon-cpp/Inc/PhotonPeer.h"

#include "Magnet/MagnetManager.h"

<<<<<<< HEAD
const float FRAME_BUFFER_W = 1280.0f;				//フレームバッファの幅。
const float FRAME_BUFFER_H = 720.0f;				//フレームバッファの高さ。
const int g_PlayerNum = 2;							//プレイヤーの数。
const int g_StageMAX = 3;							//ステージの最大数。
=======
const float FRAME_BUFFER_W = 1280.0f;					//フレームバッファの幅。
const float FRAME_BUFFER_H = 720.0f;					//フレームバッファの高さ。
const int	g_PlayerNum = 2;							//プレイヤーの数
const DWORD	TIME_ONE_FRAME = 32;						//1フレームの時間(単位:ミリ秒)。
>>>>>>> 825d87f71ee442e3c193d816933c4cbe44c7546c

static const int MAX_BONE = 512;	//!<ボーンの最大数。

using namespace myEngine;

using namespace MyMagnet;