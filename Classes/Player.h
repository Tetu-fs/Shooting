// cocos2d.hを読む
#include "cocos2d.h"

//Spriteを継承したPlayerクラスを作る
class Player : public cocos2d::Sprite
{
	//Playerの中でのみ
protected:
	
	//CREATE_FUNCを使用するのに必要
	//bool型のinit関数を宣言　overrideはおまじない。
	bool init() override;
	
	//整数を扱えるint型のindexCheckという変数を宣言
	int indexCheck;

	//クラス外でも参照できる
public:

	// void型のupdate(float dt)という関数の宣言　overrideはおまじない。
	void update(float dt)override;
	// void型のplayAnimation(int index)という関数の宣言　overrideはおまじない。
	//同時にint型のindexという変数も宣言されている
	void playAnimation(int index);

	//void型のshotという関数を作る
	void Shot();

	// cocos2d::Spriteが格納できるポインタ配列（？）、_bulletsを定義する
	cocos2d::Vector<cocos2d::Sprite*> _bullets;

	//cocos2d::Vec2という型で_velocityというメンバ変数を定義している
	//この変数はキャラクターの速度を表し、毎フレームこの速度を現在座標に加えることで移動している
	cocos2d::Vec2 _velocity; // 移動量
	//_Bvelocityは弾の速度を表す
	cocos2d::Vec2 _Bvelocity; // 弾の移動量


	//auto Player = Player::create(); と同じ意味。bool init();が必要
	//上記はPlayer型の*Playerというポインタ変数にPlayer::create()を代入している
	CREATE_FUNC(Player);
	//Playerクラスのコンストラクタの宣言
	Player();
};
//Spriteを継承したBulletクラスを作る
class Bullet : public cocos2d::Sprite
{
	//Bulletの中でのみ
protected:

	//CREATE_FUNCを使用するのに必要
	//bool型のinit関数を宣言　overrideはおまじない。
	bool init() override;

	//クラス外でも参照できる
public:
	// void型のupdate(float dt)という関数の宣言　overrideはおまじない。
	void update(float dt)override;


	//auto Bullet = Bullet::create(); と同じ意味。bool init();が必要
	//上記はBullet型の*Bulletというポインタ変数にBullet::create()を代入している
	CREATE_FUNC(Bullet);
};