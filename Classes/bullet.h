// cocos2d.hを読む
#include "cocos2d.h"

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

	// cocos2d::Spriteが格納できるポインタ配列（？）、_bulletsを定義する
	cocos2d::Vector<cocos2d::Sprite*> _bullets;

	Sprite *bullet;

	//_Bvelocityは弾の速度を表す
	cocos2d::Vec2 _Bvelocity; // 弾の移動量

	//void型のshotという関数を作る
	void Shot();

	//auto Bullet = Bullet::create(); と同じ意味。bool init();が必要
	//上記はBullet型の*Bulletというポインタ変数にBullet::create()を代入している
	CREATE_FUNC(Bullet);
};