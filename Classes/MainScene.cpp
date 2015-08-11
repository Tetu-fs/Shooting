﻿//cocos_test.hっていうヘッダーファイルを読む
#include "MainScene.h"
#include "SimpleAudioEngine.h"
//名前空間cocos2dを使うという宣言
USING_NS_CC;

//MainSceneクラスのコンストラクタ
//_stage(nullptr)を例にすると「MainSceneクラスのpirvate変数_stageに無を代入する」の意
MainScene::MainScene()
	:_stage(nullptr)
	,_player(nullptr)
	,_bullet(nullptr)

{
	shotCount = 0;

}
//MainSceneのデストラクタ
MainScene::~MainScene()
{
	//メモリ解放。ヘッダーでCC_SYNTHESIZE_RETAINしたらこれをかかないといけない。
	//MainSceneクラスのpirvate変数_stageにの中身を削除してメモリを開放している。
	CC_SAFE_RELEASE_NULL(_stage);
	CC_SAFE_RELEASE_NULL(_player);
	CC_SAFE_RELEASE_NULL(_bullet);

}
//戻り値の型がScene*のMainSceneクラスのcreateSceneという関数を作る
Scene* MainScene::createScene()
{
	//Sceneという型のsceneという変数をつくる
	auto scene = Scene::create();

	//MainSceneという型のlayerという変数をつくる
	auto layer = MainScene::create();
	
	//変数sceneを変数layerの子に加える
	scene->addChild(layer);

	//変数sceneを返り値に返す
	return scene;
}

//voidという返り値を返さない型のMainSceneクラスのupdate(float dt)という関数を作る
void MainScene::update(float dt) {

	//Vec2型の_velocityという変数を整数値に直す？
	_velocity.normalize();
	//SPEEDという定数
	const int SPEED = 5;
	//自身の位置を、現在地＋ベクトル＊SPEEDの値にする
	_player->setPosition(_player->getPosition() + _velocity * SPEED);

	_Bvelocity.normalize();
	const int BSPEED = 15;
	this->setPosition(this->getPosition() + _Bvelocity * BSPEED);

	Vec2 kawazPosition = _player->getPosition();

	auto winSize = Director::getInstance()->getWinSize();

	if (kawazPosition.x <= 0)
	{
		_velocity.x = 0;
		_player->setPositionX(0);
	}
	else if (kawazPosition.x >= winSize.width)
	{
		_velocity.x = 0;
		_player->setPositionX(winSize.width);
	}

	if (kawazPosition.y <= 0)
	{
		_velocity.y = 0;
		_player->setPositionY(0);
	}
	else if (kawazPosition.y >= winSize.height)
	{
		_velocity.y = 0;
		_player->setPositionY(winSize.height);
	}

}

void MainScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("shooting_loop.wav", true);
}

// tlue falseをとるboolという型のMainSceneクラスのinitという関数を作る
bool MainScene::init()
{
	//もしもLayerクラスのinitでなければfalseを返す
	if (!Layer::init())
	{
		return false;
	}
	//Stageクラスのポインタ変数stageを作る
	auto stage = Stage::create();
	//MainSceneの子にstageを加える
	this->addChild(stage);
	//MainSceneで_stageにstageをセットする
	this->setStage(stage);

	//Playerクラスのポインタ変数kawaztanを作る
	auto kawaztan = Player::create();
	//kawaztanをX64,Y240の位置にセットする
	kawaztan->setPosition(Vec2(64, 240));
	//MainSceneの子にkawaztanを加える
	this->addChild(kawaztan);
	//MainSceneで_playerにkawaztanをセットする
	this->setPlayer(kawaztan);
	//取得したkawaztanのテクスチャに対して設定を与えている
	kawaztan->getTexture()->setAliasTexParameters();
	//kawaztanの表示サイズを2倍にする
	kawaztan->setScale(2.0f);

	//cocos2d::EventListenerKeyboard型のポインタ変数keyboardListenerを宣言し、EventListenerKeyboard::createを代入
	auto keyboardListener = EventListenerKeyboard::create();
	//キーボードが押された時の処理を書く関数？
	//詳細よくわからない
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event *event) {

		//Playerクラスのポインタ変数myBulletを作る
		auto myBullet = Bullet::create();
		//もし押されたキーがスペースキーだったら
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {

			//Playerクラスのポインタ変数myBulletを作る
			auto myBullet = Bullet::create();
			//myBulletをkawaztanの現在位置にセットする
			myBullet->setPosition(_player->getPosition());
			//MainSceneの子にmyBulletを加える
			this->addChild(myBullet);
			//MainSceneでsetBulletにmyBulletをセットする
			this->setBullet(myBullet);
			//取得したmyBulletのテクスチャに対して設定を与えている
			myBullet->getTexture()->setAliasTexParameters();
			//Shot()関数を走らせる
			_bullet->Shot();
			//cocos2d::Spriteが格納できるポインタ配列（？）_bulletsに弾を生成
			_bullet->_bullets.pushBack(myBullet);
			log("%i", (int)_bullet->_bullets.size());
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("shot_se.wav");

		}


		//もし押されたキーが←だったら
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
			//X方向の速度を-1にする
			_velocity.x = -1;


		}
		//そうではなくもし、キーが→だったら
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			//X方向の速度を1にする
			_velocity.x = 1;

		}
		//もし押されたキーが↑だったら
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {

			//Y方向の速度を1にする
			_velocity.y = 1;
			
			//playAnimation(int index)の変数indexに1を代入
			//上方向へのアニメーションを再生
			_player->playAnimation(1);

		}
		//そうではなくもし押されたキーが↓だったら
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			//Y方向の速度を-1にする
			_velocity.y = -1;
			//playAnimation(int index)の変数indexに2を代入
			//下方向へのアニメーションを再生
			_player->playAnimation(2);
		}
	};

	//たぶんキーを離した時の処理　詳細わかんない
	keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event *event) {
		//もしも離されたキーが←、または→だったら
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			//X方向の速度を0に戻す
			_velocity.x = 0.0f;
		}
		//もしも離されたキーが↑、または↓だったら
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			//X方向の速度を0に戻す
			_velocity.y = 0.0f;
			//playAnimation(int index)の変数indexに0を代入
			//アニメーションを待機、横移動のものへ戻す
			_player->playAnimation(0);
		}

	};

	//キーボードの処理を書いた後のおまじないみたいなもの。
	//(ぎぎさんのコメントより抜粋→)EventListenerってのにキーを押したときとか、話したときみたいな処理を紐付けておいて
	//最後にEventDispatcherっていうものに、今作ったEventListenerを登録して、「よしなにお願いします」って伝える処理
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// 上記の通りアニメーションを初期化
	_player ->playAnimation(0);

	//毎フレーム更新する
	this->scheduleUpdate();
	//MainSceneを毎フレーム更新する
	this->scheduleUpdate();



	//初期化処理
	return true;
}


