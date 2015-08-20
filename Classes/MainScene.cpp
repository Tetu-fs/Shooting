//cocos_test.hっていうヘッダーファイルを読む
#include "MainScene.h"
//名前空間cocos2dを使うという宣言
USING_NS_CC;

//MainSceneクラスのコンストラクタ
//_stage(nullptr)を例にすると「MainSceneクラスのpirvate変数_stageに無を代入する」の意
MainScene::MainScene()
	: _score(0)
	, _life(5)
	,  _stage(nullptr)
	, _player(nullptr)
	, _scoreLabel(nullptr)
	, _lifeLabel(nullptr)
	, _state(GameState::PLAYING)
{
	popTimer = 0;
	popGuide = 90;
	enemyBusted = 0;
}

//MainSceneのデストラクタ
MainScene::~MainScene()
{
	//メモリ解放。ヘッダーでCC_SYNTHESIZE_RETAINしたらこれをかかないといけない。
	//MainSceneクラスのpirvate変数_stageにの中身を削除してメモリを開放している。
	CC_SAFE_RELEASE_NULL(_stage);
	CC_SAFE_RELEASE_NULL(_player);
	CC_SAFE_RELEASE_NULL(_scoreLabel);
	CC_SAFE_RELEASE_NULL(_lifeLabel);
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
	const int SPEED = 6;
	//自身の位置を、現在地＋ベクトル＊SPEEDの値にする
	_player->setPosition(_player->getPosition() + _velocity * SPEED);

	//移動制限処理
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

	if (_state == GameState::PLAYING){
		//一定時間ごとに敵を出現させる処理
		popTimer++;

		if (popTimer >= popGuide){

			Enemy *enemy = _stage->popEnemy();
			this->addChild(enemy);
			_enemys.pushBack(enemy);

			popTimer = 0;
		}
		if (_life == 0)
		{
			_state = GameState::RESULT;
			this->onResult();
		}

	}
	//消滅処理
	for (Bullet * bullet : _bullets) { // for-loopでbulletを1つずつ見ていく
		Vec2 bulletPosition = bullet->getPosition();
		if (bulletPosition.x > winSize.width || bulletPosition.x < 0) {  // この辺は画面外に出てる判定を自分で書く
			// もし画面外に出てたら
			deletedBullets.pushBack(bullet); // 消す予定リストに弾を追加
			this->removeChild(bullet);
		}
	}	
	for (Enemy * enemy : _enemys) { // for-loopでenemyを1つずつ見ていく
		Vec2 enemyPosition = enemy->getPosition();
		if (enemyPosition.x > winSize.width || enemyPosition.x < 0) {
			// もし画面外に出てたら
			deletedEnemys.pushBack(enemy);
			this->removeChild(enemy);
			_life--;
			_lifeLabel->setString(StringUtils::toString(_life));

		}
	}
		for (Bullet * bullet : _bullets) { // for-loopでbulletを1つずつ見ていく
			for (Enemy * enemy : _enemys) { // for-loopでbulletを1つずつ見ていく

				Vec2 bulletHit = bullet->getPosition();
				Rect boundingBox = enemy->getBoundingBox();
				bool isHit = boundingBox.containsPoint(bulletHit);
				if (isHit) {  // もしも当たったら
					deletedBullets.pushBack(bullet); // 消す予定リストに弾を追加
					this->removeChild(bullet);
					deletedEnemys.pushBack(enemy);
					this->removeChild(enemy);
					enemyBusted++;	
					log("enemyBusted %d", enemyBusted);
					log("popGuide %d", popGuide);
					log("popTimer %d", popTimer);
					_score += 100;
					if (enemyBusted >= 15 && popGuide > 10){
						popGuide -= 10;

					}
					if (enemyBusted == 15)
					{
						_score *= 2;
						enemyBusted = 0;
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("level_se.wav");

					}

					_scoreLabel->setString(StringUtils::toString(_score));
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit_se.wav");


				}
			}
	}
	//log("check_bullets %d", _bullets.size());
	for (Bullet * bullet : deletedBullets) { // 今度は消す予定リストを1つずつ見て行って
		log("delete_bullets %d", _bullets.size());
		_bullets.eraseObject(bullet); // 1つずつ_bulletsから消していく
	}
	deletedBullets.clear(); // 最後に消す予定リストを全部消す

	//消す敵リストに突っ込む
	for (Enemy * enemy : deletedEnemys) {
		log("delete_enemys %d", _enemys.size());
		_enemys.eraseObject(enemy);
	}
	deletedEnemys.clear();

}

void MainScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("shooting_loop.wav", true);
}

void MainScene::onResult(){
	_state = GameState::RESULT;
	auto scoreLabel = Label::createWithSystemFont(StringUtils::toString(_score), "arial", 32);
	scoreLabel->setPosition(Vec2(320, 400));
	this->setScoreLabel(scoreLabel);
	this->addChild(_scoreLabel);

	auto scoreHeader = Label::createWithSystemFont("Score", "arial", 32);
	scoreHeader->setPosition(Vec2(320, 440));
	this->addChild(scoreHeader);

	auto replay_normal = Sprite::create("replay.png");
	auto replay_press = Sprite::create("replay_press.png");
	auto title_normal = Sprite::create("title.png");
	auto title_press = Sprite::create("title_press.png");

	//リプレイボタンの処理
	auto replayButton = MenuItemSprite::create(replay_normal, replay_press , [](Ref* ref)
	{
		auto scene = MainScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	//タイトルボタンの処理
	auto titleButton = MenuItemSprite::create(title_normal, title_press, [](Ref* ref)
	{

	});
	replay_normal->getTexture()->setAliasTexParameters();
	replay_press->getTexture()->setAliasTexParameters();
	title_normal->getTexture()->setAliasTexParameters();
	title_press->getTexture()->setAliasTexParameters();
	replayButton->setScale(2.0f);
	titleButton->setScale(2.0f);

	//それぞれのボタンからメニューを作成
	auto menu = Menu::create(replayButton, titleButton, NULL);
	//ボタンを縦に並べる
	menu->alignItemsVerticallyWithPadding(15);
	menu->setPosition(Vec2(320, 240));

	this->addChild(menu);
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

	auto scoreLabel = Label::createWithSystemFont(StringUtils::toString(_score), "arial", 16);
	scoreLabel->setPosition(Vec2(600, 440));
	this->setScoreLabel(scoreLabel);
	this->addChild(_scoreLabel);

	auto scoreHeader = Label::createWithSystemFont("Score", "arial", 16);
	scoreHeader->setPosition(Vec2(580, 460));
	this->addChild(scoreHeader);

	auto lifeLabel = Label::createWithSystemFont(StringUtils::toString(_life), "arial", 16);
	lifeLabel->setPosition(Vec2(20, 440));
	this->setLifeLabel(lifeLabel);
	this->addChild(_lifeLabel);

	auto lifeHeader = Label::createWithSystemFont("Life", "arial", 16);
	lifeHeader->setPosition(Vec2(40, 460));
	this->addChild(lifeHeader);

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

		//もし押されたキーがスペースキーだったら
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
			Bullet *bullet = _player->shoot();
			this->addChild(bullet);
			_bullets.pushBack(bullet);
		}


		//もし押されたキーが←だったら
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_A) {
			//X方向の速度を-1にする
			_velocity.x = -1;


		}
		//そうではなくもし、キーが→だったら
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_D) {
			//X方向の速度を1にする
			_velocity.x = 1;

		}
		//もし押されたキーが↑だったら
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW || keyCode == EventKeyboard::KeyCode::KEY_W) {

			//Y方向の速度を1にする
			_velocity.y = 1;
			
			//playAnimation(int index)の変数indexに1を代入
			//上方向へのアニメーションを再生
			_player->playAnimation(1);

		}
		//そうではなくもし押されたキーが↓だったら
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW || keyCode == EventKeyboard::KeyCode::KEY_S) {
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

	//MainSceneを毎フレーム更新する
	this->scheduleUpdate();



	//初期化処理
	return true;
}


