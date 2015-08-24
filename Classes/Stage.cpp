//Stage.hというヘッダーファイルを読む
#include "Stage.h"

//名前空間cocos2dを使うという宣言
USING_NS_CC;

//Stageクラスのコンストラクタ
//_tiledMap(nullptr)「Stageクラスのpirvate変数_tiledMapに無を代入する」の意
Stage::Stage()
	: _tiledMap(nullptr)
	, _pallaraxNode(nullptr)
{
}
//Stageクラスのデストラクタ
Stage::~Stage()
{
	CC_SAFE_RELEASE_NULL(_tiledMap);
	CC_SAFE_RELEASE_NULL(_pallaraxNode);

}
//bool型のStage::init()関数を宣言

Enemy* Stage::popZako()
{
	float zakoY = RandomHelper::random_real<float>(80, 400);
	//Enemyクラスのポインタ変数enemyを作る
	Enemy *zakoenemy = ZakoEnemy::create();
	//enemyをX540,Y240の位置にセットする
	zakoenemy->setPosition(Vec2(540, zakoY));
	//取得したenemyのテクスチャに対して設定を与えている
	zakoenemy->getTexture()->setAliasTexParameters();
	//enemyの表示サイズを2倍にする
	zakoenemy->setScale(2.0f);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop_se.wav");

	//戻り値にzakoenemyを返す
	return zakoenemy;
}
Enemy* Stage::popRare()
{
	float rareY = RandomHelper::random_real<float>(80, 400);
	//Enemyクラスのポインタ変数enemyを作る
	Enemy *rareenemy = RareEnemy::create();
	//enemyをX540,Y240の位置にセットする
	rareenemy->setPosition(Vec2(540, rareY));
	//取得したenemyのテクスチャに対して設定を与えている
	rareenemy->getTexture()->setAliasTexParameters();
	//enemyの表示サイズを2倍にする
	rareenemy->setScale(1.0f);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop_se.wav");

	//戻り値にrereenemyを返す
	return rareenemy;

}

bool Stage::init()
{
	//int型の変数x,yを宣言、初期化
	int x = 0;
	int y = 0;

	//もしLayerが初期化されていなかったら返り値にfalseを返す
	if (!Layer::init())
	{
		return false;
	}

	auto skySprite = Sprite::create("sky.png");
	skySprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	skySprite->setPosition(0, 0);

	auto setCloud = Node::create();
	auto setGround = Node::create();

	auto cloudSprite1 = Sprite::create("cloud.png");
	auto cloudSprite2 = Sprite::create("cloud.png");
	cloudSprite1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	cloudSprite2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	cloudSprite1->setPosition(0, 0);
	cloudSprite2->setPosition(640, 0);

	setCloud->addChild(cloudSprite1);
	setCloud->addChild(cloudSprite2);


	auto groundSprite1 = Sprite::create("ground.png");
	auto groundSprite2 = Sprite::create("ground.png");
	groundSprite1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	groundSprite2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	groundSprite1->setPosition(0, 0);
	groundSprite2->setPosition(640, 0);

	setGround->addChild(groundSprite1);
	setGround->addChild(groundSprite2);
	

	this->addChild(skySprite);
	this->addChild(setCloud);
	this->addChild(setGround);


	auto cloudMove = RepeatForever::create(Sequence::create(MoveTo::create(4, Vec2(-640, 0)), Place::create(Vec2::ZERO), NULL));
	setCloud->runAction(cloudMove);
	auto groundMove = RepeatForever::create(Sequence::create(MoveTo::create(2, Vec2(-640, 0)), Place::create(Vec2::ZERO), NULL));
	setGround->runAction(groundMove);
	//Stageクラスを毎フレーム更新する
	this->scheduleUpdate();

	//返り値にtrueを返す
	return true;

}
//毎フレーム更新する
void Stage::update(float dt)
{

}