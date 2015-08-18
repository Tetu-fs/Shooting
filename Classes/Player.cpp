//Player.hを読む
#include "Player.h"
#include "SimpleAudioEngine.h"

//名前空間cocos2dをしようするという宣言
USING_NS_CC;

//定数FRAME_COUNTを宣言、初期化
const int FRAME_COUNT = 2;

//Playerクラスのコンストラクタ
//二行目でヘッダーで宣言した変数indexCheckを初期化
Player::Player()
	: indexCheck(-1)

{

}
Player::~Player()
{
}

//void型のPlayer::update(float dt)関数を宣言
//毎フレーム更新したい物をつっこむ？
void Player::update(float dt)
{
}

//bool型のPlayer::init()関数を宣言
bool Player::init()
{
	int bulletCount = 0;
	//もしkawaz_shoothing.pngが見つからなかったら
	if (!Sprite::initWithFile("kawaz_shooting.png"))
	{
		//返り値にfalseを返す
		return false;
	}

	//返り値にtrueを返す
	return true;
}

Bullet * Player::shoot()
{
	//Bulletクラスのポインタ変数bulletを生成
	Bullet *bullet = Bullet::create();
	//bulletの位置をPlayerの現在地に設定
	bullet->setPosition(this->getPosition());
	//bulletに取得したテクスチャを与える
	bullet->getTexture()->setAliasTexParameters();
	//効果音をならす
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("shot_se.wav");
	//戻り値にbulletを返す
	return bullet;
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


