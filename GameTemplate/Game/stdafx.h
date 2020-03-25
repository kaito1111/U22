#pragma once

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
//D3Dcompiler.h��艺�ɂ���ƍĒ�`������܂�
//#include "Common-cpp/inc/Common.h"
#include <map>
#include <functional>
#include <algorithm>
//�I�[�f�B�I�̃C���N���[�h
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>


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

//�G���W���n
#include "myEngine.h"
#include "graphics/GraphicsEngine.h"
#include "Sound/SoundEngine.h"

#include "graphics/SkinModel.h"
#include "graphics/Skeleton.h"

#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/Camera.h"

#include "Effect.h"

#include "sound/SoundSource.h"

#include "GameObject/GameObjectManager.h"
#include "GameObject/IGameObject.h"

//#include "photon/LoadBalancing-cpp/inc/friendinfo.h"
//#include "Photon-cpp/Inc/PhotonPeer.h"

#include "Magnet/MagnetManager.h"


const float FRAME_BUFFER_W = 1280.0f;				//�t���[���o�b�t�@�̕��B
const float FRAME_BUFFER_H = 720.0f;				//�t���[���o�b�t�@�̍����B
const int g_PlayerNum = 2;							//�v���C���[�̐��B

static const int MAX_BONE = 512;	//!<�{�[���̍ő吔�B

using namespace myEngine;

using namespace MyMagnet;