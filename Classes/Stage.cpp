//Stage.hというヘッダーファイルを読む
#include "Stage.h"

//名前空間cocos2dを使うという宣言
USING_NS_CC;

//Stageクラスのコンストラクタ
//_tiledMap(nullptr)「Stageクラスのpirvate変数_tiledMapに無を代入する」の意
Stage::Stage()
	: _tiledMap(nullptr)
{
}
//Stageクラスのデストラクタ
Stage::~Stage()
{
	CC_SAFE_RELEASE_NULL(_tiledMap);

}
//bool型のStage::init()関数を宣言

Enemy* Stage::popZako()
{
	float zakoY = RandomHelper::random_real<float>(140, 400);
	//Enemyクラスのポインタ変数enemyを作る
	Enemy *zakoenemy = ZakoEnemy::create();
	//enemyをX540,Y240の位置にセットする
	zakoenemy->setPosition(Vec2(540, zakoY));
	//取得したenemyのテクスチャに対して設定を与えている
	zakoenemy->getTexture()->setAliasTexParameters();
	//enemyの表示サイズを2倍にする
	zakoenemy->setScale(2.0f);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/pop_se.wav");

	//戻り値にzakoenemyを返す
	return zakoenemy;
}
Enemy* Stage::popRare()
{
	float rareY = RandomHelper::random_real<float>(140, 400);
	//Enemyクラスのポインタ変数enemyを作る
	Enemy *rareenemy = RareEnemy::create();
	//enemyをX540,Y240の位置にセットする
	rareenemy->setPosition(Vec2(540, rareY));
	//取得したenemyのテクスチャに対して設定を与えている
	rareenemy->getTexture()->setAliasTexParameters();
	//enemyの表示サイズを2倍にする
	rareenemy->setScale(1.0f);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/pop_se.wav");

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
	

	auto skySprite = Sprite::create("graphic/sky.png");
	skySprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	skySprite->setPosition(0, 0);

	auto setCloud = Node::create();

	auto cloudSprite1 = Sprite::create("graphic/cloud.png");
	auto cloudSprite2 = Sprite::create("graphic/cloud.png");
	cloudSprite1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	cloudSprite2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	cloudSprite1->setPosition(0, 0);
	cloudSprite2->setPosition(640, 0);

	setCloud->addChild(cloudSprite1);
	setCloud->addChild(cloudSprite2);

	


	this->addChild(skySprite);
	this->addChild(setCloud);


	//どうすっぺ
	//

	auto cloudMove = RepeatForever::create(
		Sequence::create(
		MoveTo::create(5, Vec2(-640, 0)),
		Place::create(Vec2::ZERO),
		NULL));
	setCloud->runAction(cloudMove);



	//Stageクラスを毎フレーム更新する
	this->scheduleUpdate();

	//返り値にtrueを返す
	return true;

}


 float Stage::drawGround(float groundY)
 {

	//TMXTiledMapのポインタ変数mapにTMXTiledMap::create("test_map.tmx")を代入
	//test_map.tmxを読む
	auto ground = TMXTiledMap::create("ground.tmx");
	//TMXTiledMapのポインタ変数backgroundにmapのレイヤーbackgroundを代入
	// Tiledで設定したレイヤーの名前を渡す
	TMXLayer* yuka = ground->getLayer("yuka");
	//auto scrollGround = TMXTiledMap::create("test_map.tmx");
	//TMXTiledMapのポインタ変数yukaにmapのレイヤーyukaを代入
	TMXLayer* hana = ground->getLayer("hana");
	// Tiledで設定したレイヤーの名前を渡す
	//TMXTiledMapのポインタ変数mapにTMXTiledMap::create("test_map.tmx")を代入
	//test_map.tmxを読む
	auto ground2 = TMXTiledMap::create("ground.tmx");
	TMXLayer* yuka2 = ground2->getLayer("yuka");
	//auto scrollGround = TMXTiledMap::create("test_map.tmx");
	//TMXTiledMapのポインタ変数yukaにmapのレイヤーyukaを代入
	TMXLayer* hana2 = ground2->getLayer("hana");

	//Stageクラスのサイズを倍に指定
	ground->setScale(2.0f);
	//Stageクラスのサイズを倍に指定
	ground2->setScale(2.0f);
	//Stageクラスの子にmapを加える（これで画像を描画だっけ）
	//this->addChild(ground);
	//StageクラスのTiledMapにmapを指定　おまじないかな
	this->setTiledMap(ground);

	ground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	ground2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	ground->setPosition(0, groundY);
	ground2->setPosition(640, groundY);

	auto setGround = Node::create();

	setGround->addChild(ground);
	setGround->addChild(ground2);
	auto groundMove = RepeatForever::create(
		Sequence::create(
		MoveTo::create(3, Vec2(-640, 0)),
		Place::create(Vec2::ZERO),
		NULL));
	setGround->runAction(groundMove);

	//アカン
	//this->addChild(setGround);
	
	return groundY;
}

//毎フレーム更新する
void Stage::update(float dt)
{

}