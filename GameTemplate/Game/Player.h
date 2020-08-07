#pragma once
#include "character/CharacterController.h"
#include "graphics/2D/SpriteRender.h"
#include "Magnet/Magnet.h"
class PlayerPad;
class NetworkPad;
class IPad;

class GamePlayer : public IGameObject
{
public:
	GamePlayer();//コンストラクタ
	~GamePlayer();//デストラクタ
	CVector3 GetPosition() { //位置を返す
		return m_position; 
	}
	void SetPosition(CVector3 pos, CVector3 moveSpeed = CVector3::Zero()) 
	/// <summary>
	/// 位置を決める
	/// </summary>
	/// <param name="pos">		プレイヤーの移動先を入れる</param>
	/// <param name="moveSpeed">プレイヤーの移動量を決める。
	///							あまり使わない</param>
	{
		m_characon.SetPosition(pos);
		if (moveSpeed.Length() > 1.0f) {
			m_position = m_characon.Execute(1.0f, moveSpeed);
		}
	}
	void SetPoint(CVector3 point) {//リスポーン位置を設定
		m_CheckPoint = point;
	}
	SkinModel* GetModel() {//モデルを返す
		return &m_model;
	}

	/// <summary>
	/// padの初期化
	/// <para>ポリモーフィズムしていないIPadを送らないこと。</para>
	/// </summary>
	/// <remarks>
	/// ---padの処理について---
	/// 1.twoP_PadでPadの識別(対応した型にポリモーフィズム)と初期化をして、
	/// 2.kaitoTask(プレイヤーのインスタンス作成時)で、どのPadを使って操作するかの設定。
	/// ---exp---
	/// ポリモーフィズムすることで関数を一つに集約
	/// </remarks>
	/// <param name="pad">ポリモーフィズムされたIPad</param>
	void SetPad(IPad* pad);				//コントローラーを設定する
	void SIBOU();						
	void Press();						//何度も呼ぶ
	void MagumaDead();					//何度も呼ぶ
	void Cut();							//何度も呼ぶ

	void SetPlayerNum(int n)//何Pか決める
	{
		m_PlayerNum = n;
	}

	void ReSpown();//リスポーン地点で復活する
	
	void SetCheckPoint(CVector3 spownPoint)//リスポーン地点を決める
	{
		m_CheckPoint = spownPoint;
	}
private:
	bool Start();//すたーと
	void Update();//あぷでーど
	void Draw();//どろー
	int GetPadNo() const;//コントローラーの番号を返す
	SkinModel m_model;										//スキンモデル。
	SkinModel m_FrontModel;									//スキンモデル。
	SkinModel m_BuckModel;									//スキンモデル。
	CharacterController m_characon;							//キャラコン
	CVector3 m_position = CVector3::Zero();					//位置
	CQuaternion	m_rot = CQuaternion::Identity();			//向き
	float m_rotAngle = 0.0f;								//回転率
	enum Dir{//方向
		L,//Left　左
		R,//Right 右
		U,//Up    上
		D,//Down  下
		num
	};
	Dir dir = L;											//向いてる向き
	bool m_IsSi = false;									//死亡しているかどうか
	CVector3 m_Scale	 = CVector3::One();					//大きさ
	bool m_PlayerCut	= false;							//切られたかどうか
	CQuaternion	m_DefeatRot	 = CQuaternion::Identity();	//倒れているときの回転率(前側)
	CQuaternion	m_ReverseDefeatRot = CQuaternion::Identity(); //倒れているときの回転率(後側)
	float rate = 0.0f;										//切られたときに倒れる角度
	CVector3 m_CheckPoint = { 0.0f,0.0f,0.0f };		//リスポーン地点
	SoundSource m_Se;					//ジャンプ音
	SoundSource m_Se2;					//m_Seが流れているときに流れるサブ音声

	SpriteRender* m_ThisNumSprite = nullptr;				//何Pかを表す絵
	int	m_PlayerNum = 0;									//何P？
	SpriteRender* m_DieSprite = nullptr;					//死んだら赤くなる

	MyMagnet::Magnet* m_Magnet = nullptr;					//磁力
	bool HaveMagnet = false;								//磁力を持っているかどうか
	CVector3 movespeed = CVector3::Zero();					//移動量
//	ShadowMap* m_shadowMap = nullptr;				//シャドウマップ

	enum enAniCli {
		Wait,
		Run,
		Junp,
		AnimaitionNum
	};
	AnimationClip m_AnimeClip[enAniCli::AnimaitionNum];		//アニメーションリスト
	Animation m_Animetion;									//アニメーション
	void SpawnPole();										//磁極を呼ぶ
	void Move();											//移動する
	void MyMagnet();										//磁極を変更する
	SoundSource m_Asioto;									//足音

	IPad* m_Pad = nullptr;									//パッド

	SpriteRender* m_SpriteN = nullptr;
	SpriteRender* m_SpriteS = nullptr;
	SpriteRender* m_SpriteJump = nullptr;
	SpriteRender* m_SpriteBase = nullptr;
	SpriteRender* m_SpriteDel = nullptr;
};