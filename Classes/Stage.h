//もしdefineされていなければ
#ifndef __MyGame__stage__
//コンパイル時に置き換える　インクルードガードというらしい。
//ifndefとendifの間に挟むとエラーが出なくなるおまじない。
#define __MyGame__stage__
//cocos2d.hをよむ
#include "cocos2d.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"

//cocos2d::Layerクラスのパブリックで継承クラスStageを作る
class Stage :public cocos2d::Layer
{
	//Stageクラス内でのみ
protected:

	//bool型のinit()関数の宣言 overrideはおまじない
	//CREATE_FUNC()に必須
	bool init() override;



	//クラス外からでも参照可能
public:

	//Eenmy型StageクラスのpopZakoメソッドを宣言
	Enemy* popZako();
	//Eenmy型StageクラスのpopRareメソッドを宣言
	Enemy* popRare();

	//static Stage* create()と同じ意味。bool init();が必要
	//Stageクラスインスタンスへのポインタを返すStageクラスのクラスメソッド、createを宣言している
	CREATE_FUNC(Stage);
};
class Cloud :public Stage
{
	//Stageクラス内でのみ
protected:

	//bool型のinit()関数の宣言 overrideはおまじない
	//CREATE_FUNC()に必須
	bool init() override;



	//クラス外からでも参照可能
public:
	//static Stage* create()と同じ意味。bool init();が必要
	//Stageクラスインスタンスへのポインタを返すStageクラスのクラスメソッド、createを宣言している
	CREATE_FUNC(Cloud);
};

class Ground :public Stage
{
	//Stageクラス内でのみ
protected:
	//Stageコンストラクタの宣言
	Ground();
	//Stageデストラクタの宣言　virtualはおまじない
	virtual ~Ground();

	//bool型のinit()関数の宣言 overrideはおまじない
	//CREATE_FUNC()に必須
	bool init() override;



	//クラス外からでも参照可能
public:

	//Tile
	//TMXTiledMapという型をつくり、Stageクラスのprivate変数_tiledMapを作り、getTledMap/setTledMapをつくる
	//ここでつくられたTMXTiledMap型の変数はポインタ変数になる
	//getTledMapは_tiledMapを取得し、setTledMapは_tiledMapを書き換えられる
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXTiledMap *, _tiledMap, TiledMap);
	//static Stage* create()と同じ意味。bool init();が必要
	//Stageクラスインスタンスへのポインタを返すStageクラスのクラスメソッド、createを宣言している
	CREATE_FUNC(Ground);
};


#endif /*defined(__MyGame__stage__)*/
