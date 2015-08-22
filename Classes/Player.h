// cocos2d.hを読む
#include "cocos2d.h"
#include "bullet.h"

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

	//Playerクラスのコンストラクタの宣言
	Player();
	//virtualは仮想関数というおまじない　デストラクタの宣言
	virtual ~Player();


	//クラス外でも参照できる
public:
	

	// void型のupdate(float dt)という関数の宣言　overrideはおまじない。
	void update(float dt)override;

	//Bullet型Playerクラスのshootメソッドを宣言
	Bullet* Player::shoot();


	// void型のplayAnimation(int index)という関数の宣言　overrideはおまじない。
	//同時にint型のindexという変数も宣言されている
	void playAnimation(int index);

	//auto Player = Player::create(); と同じ意味。bool init();が必要
	//上記はPlayer型の*Playerというポインタ変数にPlayer::create()を代入している
	CREATE_FUNC(Player);

};
