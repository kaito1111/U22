#pragma once



#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
//D3Dcompiler.h��艺�ɂ���ƍĒ�`������܂�
#include "Common-cpp/inc/Common.h"
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>
#include <map>
#include <functional>
#include <algorithm>

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

//�G�t�F�N�T�[
#include "Effekseer.h"
#include "EffekseerRendererDX11.h"

//DirectXTK�̃C���N���[�h�t�@�C���B
#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"

#include "physics/Physics.h"
#include "HID/Pad.h"

#include "math/Vector.h"
#include "math/Matrix.h"
#include "graphics/GraphicsEngine.h"

#include "graphics/SkinModel.h"
#include "graphics/Skeleton.h"

#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/Camera.h"

#include "Effect.h"

#include "GameObject/GameObjectManager.h"
#include "GameObject/IGameObject.h"

#include "photon/LoadBalancing-cpp/inc/friendinfo.h"
#include "Photon-cpp/Inc/PhotonPeer.h"

#include "MagnetManager.h"


const float FRAME_BUFFER_W = 1280.0f;				//�t���[���o�b�t�@�̕��B
const float FRAME_BUFFER_H = 720.0f;				//�t���[���o�b�t�@�̍����B

static const int MAX_BONE = 512;	//!<�{�[���̍ő吔�B

using namespace myEngine;

using namespace MyMagnet;