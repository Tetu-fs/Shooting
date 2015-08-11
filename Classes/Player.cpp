//Player.hを読む
#include "Player.h"

//名前空間cocos2dをしようするという宣言
USING_NS_CC;

//定数FRAME_COUNTを宣言、初期化
const int FRAME_COUNT = 2;

//Playerクラスのコンストラクタ
//二行目でヘッダーで宣言した変数indexCheckを初期化
Player::Player()
	:indexCheck(-1)
{

}

//void型のPlayer::update(float dt)関数を宣言
//毎フレーム更新したい物をつっこむ？
void Player::update(float dt)
{
	//Vec2型の_velocityという変数を整数値に直す？
	_velocity.normalize();
	//SPEEDという定数
	const int SPEED = 5;
	//自身の位置を、現在地＋ベクトル＊SPEEDの値にする
	this->setPosition(this->getPosition() + _velocity * SPEED);


	_Bvelocity.normalize();
	const int BSPEED = 15;
	this->setPosition(this->getPosition() + _Bvelocity * BSPEED);


}

//bool型のPlayer::init()関数を宣言
bool Player::init()
{
	_bullets = Vector<Sprite*>();
	int bulletCount = 0;
	//もしkawaz_shoothing.pngが見つからなかったら
	if (!Sprite::initWithFile("kawaz_shooting.png"))
	{
		//返り値にfalseを返す
		return false;
	}
	//cocos2d::EventListenerKeyboard型のポインタ変数keyboardListenerを宣言し、EventListenerKeyboard::createを代入
	auto keyboardListener = EventListenerKeyboard::create();
	//キーボードが押された時の処理を書く関数？
	//詳細よくわからない
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event *event) {
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
			this->playAnimation(1);

		}
		//そうではなくもし押されたキーが↓だったら
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			//Y方向の速度を-1にする
			_velocity.y = -1;
			//playAnimation(int index)の変数indexに2を代入
			//下方向へのアニメーションを再生
			this->playAnimation(2);
		}
		//もし押されたキーがスペースキーだったら
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
			//Shot()関数を走らせる
			Shot();
			//cocos2d::Spriteが格納できるポインタ配列（？）_bulletsに弾を生成
			_bullets.pushBack(Sprite::create());
			_Bvelocity.x = 1;
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
			this->playAnimation(0);
		}

	};

	//キーボードの処理を書いた後のおまじないみたいなもの。
	//(ぎぎさんのコメントより抜粋→)EventListenerってのにキーを押したときとか、話したときみたいな処理を紐付けておいて
	//最後にEventDispatcherっていうものに、今作ったEventListenerを登録して、「よしなにお願いします」って伝える処理
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// 上記の通りアニメーションを初期化
	this->playAnimation(0);
	
	//毎フレーム更新する
	this->scheduleUpdate();

	//返り値にtrueを返す
	return true;
}


// 0~2のアニメーションを再生するメソッド(0通常、1上、2下)
//void型のPlayer::playAnimation(int index)関数を作成
void Player::playAnimation(int index) {
	//もしも変数indexCheckと変数indexが等しかったら
	if (indexCheck == index) {
		//ここで関数の処理を終了する
		return;
	}

	// アニメーション用のタグを固定値で定義
	const int ACTION_TAG = 10000; // 好きな数

	// 既にアニメーションが動いていたら止める
	// アニメーションには全て10000のタグが付いてるはずなので、重複しないように止める
	this->stopActionByTag(ACTION_TAG);

	// cocos2d::Size型のframeSize変数で表示するかわずたんのスプライトのサイズを指定？
	//Size(frameSize.width, frameSize.height)にそれぞれ16.0を代入している。型はfloat
		auto frameSize = Size(16.0, 16.0);
		
		//？
		//スプライトのX座標0、Y座標0(左上)から、16x16を切り出す？
		//Rectはx,y,width,heightの4つをとれる。矩形という意味
		this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
		
		//SpriteFrame*というテンプレートでframesという配列を宣言
		Vector<SpriteFrame*> frames;

		//変数iを宣言、0で初期化しiがFRAME_COUNT未満である時、変数iに1を加算し{}内の処理を行いループ
		//iがFRAME_COUNT未満でなくなった時にループを抜ける
		for (int i = 0; i < FRAME_COUNT; ++i)
		{
			// indexの値によってy座標を変える
			//cocos2d::SpriteFrame型のポイント変数frameを宣言
			//画像kawaz_shooting.pngを読み、frameSize.widthにiをかけ2コマアニメーションのループ
			//indexに16(frameSize.heightの値)をかけ、アニメーションを切り替え
			//frameSize.widthとframeSize.heightで表示する画像の大きさを指定？
			auto frame = SpriteFrame::create("kawaz_shooting.png", Rect(frameSize.width * i, index * 16, frameSize.width, frameSize.height));

			//配列framesの終わりにframeの値を挿入する
			frames.pushBack(frame);
		}

		//cocos2d::Animation型のポインタ変数animationを宣言
		//配列framesを代入してるっぽいけどWithなんちゃらがよくわからない
		auto animation = Animation::createWithSpriteFrames(frames);

		//ポインタ変数animationの表示間隔を0.05秒にする
		animation->setDelayPerUnit(0.05);
		
		//cocos2d::RepeatForever型のポインタ変数animateを宣言　なんか闇っぽい
		//Animate::create(animation)でanimationで宣言された2コマアニメを生成してるとおもう
		//RepeatForeverは生成したアニメーションをを無限に繰り返す
		auto animate = RepeatForever::create(Animate::create(animation));

		//ポインタ変数animateにACTION_TAGというタグを設定
		animate->setTag(ACTION_TAG);
		
		//animateというアクションを走らせる
		this->runAction(animate);
		
		//indexCheckにindexの値を代入する
		indexCheck = index;
}

//void型のBullet::update(float dt)関数を宣言
//毎フレーム更新したい物をつっこむ？
void Bullet::update(float dt)
{


}
//bool型のBullet::init()関数を宣言
bool Bullet::init(){
	//もしbullet.pngみつからなかったら
	if (!Sprite::initWithFile("bullet.png"))
	{
		//返り値にfalseを返す
		return false;
	}
	//毎フレーム更新
	this->scheduleUpdate();
	//返り値にtrueを返す
	return true;
}

//void型のPlayer::Shot()関数を作成
void Player::Shot() {

	// cocos2d::Size型のBframeSize変数で表示する弾のスプライトのサイズを指定？
	//詳細は上部frameSizeにて
	auto BframeSize = Size(16.0, 16.0);

	//playAnimation(int index)とアニメーションの切り替えがない以外は同じ
	this->setTextureRect(Rect(0, 0, BframeSize.width, BframeSize.height));
	Vector<SpriteFrame*> Bframes;
	for (int j = 0; j < FRAME_COUNT; ++j)
	{
		auto Bframe = SpriteFrame::create("bullet.png", Rect(BframeSize.width * j, 0, BframeSize.width, BframeSize.height));
		Bframes.pushBack(Bframe);
	}

	auto Banimation = Animation::createWithSpriteFrames(Bframes);
	Banimation->setDelayPerUnit(0.05);
	auto Banimate = RepeatForever::create(Animate::create(Banimation));
	this->runAction(Banimate);

	//弾のX方向の速度を1にする


}