//もしdefineされていなければ
#ifndef __MyGame__cocos_test__
//コンパイル時に置き換える　インクルードガードというらしい。
//ifndefとendifの間に挟むとエラーが出なくなるおまじない。
#define __MyGame__cocos_test__

//ヘッダーファイル等を読み込む
#include "cocos2d.h"
#include "Stage.h"
#include "Player.h"
#include "SimpleAudioEngine.h"


//Layerクラスのpublicで継承クラスMainSceneの宣言　
class MainScene :public cocos2d::Layer
{
	//MainSceneの中でのみ
protected:
	
	//MainSceneのコンストラクタの宣言 （名前が同じだからわかりづらい気がするがそういうものらしい
	MainScene();
	
	//virtualは仮想関数というおまじない　デストラクタの宣言
	virtual ~MainScene();
	
	//CREATE_FUNCを使用するのに必要
	//bool型のinit関数を宣言　overrideはおまじない。
	bool init() override;
	

	//クラス外からでも参照できる
public:
	
	// Bulletが格納できるポインタ配列（？）、_bulletsを定義する
	cocos2d::Vector<Bullet *> _bullets;

	// 消す予定の弾リストを作る
	cocos2d::Vector<Bullet *> deletedBullets;

	// Enemyが格納できるポインタ配列（？）、_enemysを定義する
	cocos2d::Vector<Enemy *> _enemys;

	// 消す予定の敵リストを作る
	cocos2d::Vector<Enemy *> deletedEnemys;

	// クラス関数であるcocos2d::Scene型の*createSceneという関数の宣言
	static cocos2d::Scene* createScene();

	//cocos2d::Vec2という型で_velocityというメンバ変数を定義している
	//この変数はキャラクターの速度を表し、毎フレームこの速度を現在座標に加えることで移動している
	cocos2d::Vec2 _velocity; // 移動量

	// void型のupdate(float dt)という関数の宣言　overrideはおまじない。
	void update(float dt) override;
	//　void型の長い名前の関数の宣言
	void onEnterTransitionDidFinish() override;


	//stageを例にすると、Stage*という型をつくり、MainSceneクラスのprivate変数_stageを作り、getStage/setStageをつくる
	//getStageは_stageを取得し、setStageは_stageを書き換えられる
	CC_SYNTHESIZE_RETAIN(Stage* , _stage, Stage);
	CC_SYNTHESIZE_RETAIN(Player*, _player, Player);

	//auto mainScene = MainScene::create(); と同じ意味。bool init();が必要
	//上記はMainScene型の*mainSceneというポインタ変数にMainScene::create()を代入している
	CREATE_FUNC(MainScene);


};
//ifndefからここまでをコンパイルする　らしい
#endif /*defined(__MyGame__cocos_test__)*/