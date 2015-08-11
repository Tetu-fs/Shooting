//cocos_test.hっていうヘッダーファイルを読む
#include "MainScene.h"

//名前空間cocos2dを使うという宣言
USING_NS_CC;

//MainSceneクラスのコンストラクタ
//_stage(nullptr)を例にすると「MainSceneクラスのpirvate変数_stageに無を代入する」の意
MainScene::MainScene()
	:_stage(nullptr)
	,_player(nullptr)
	,_bullet(nullptr)
{


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

	//MainSceneを毎フレーム更新する
	this->scheduleUpdate();



	//初期化処理
	return true;
}


