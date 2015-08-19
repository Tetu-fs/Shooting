// cocos2d.hを読む
#include "cocos2d.h"

//Spriteを継承したBulletクラスを作る
class Enemy : public cocos2d::Sprite
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

	//auto Enemy = Enemy::create(); と同じ意味。bool init();が必要
	//上記はEnemy型の*Enemyというポインタ変数にEnemy::create()を代入している
	CREATE_FUNC(Enemy);
};