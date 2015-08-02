#include "cocos2d.h"
#include <list>


class Player : public cocos2d::Sprite
{
protected:
	bool init() override;
	int test;
public:
	void update(float dt)override;
	void playAnimation(int index);

	void Shot();
	std::list<int> _bullets;

	cocos2d::Vec2 _velocity; // ˆÚ“®—Ê
	cocos2d::Vec2 _Bvelocity; // ’e‚ÌˆÚ“®—Ê
	CREATE_FUNC(Player);
	Player();
};

class Bullet : public cocos2d::Sprite
{
protected:
	bool init() override;
public:
	void update(float dt)override;

	CREATE_FUNC(Bullet);
};