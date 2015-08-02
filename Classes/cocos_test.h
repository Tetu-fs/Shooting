#ifndef __MyGame__cocos_test__
#define __MyGame__cocos_test__

#include "cocos2d.h"
#include "stage.h"
#include "kawaztan.h"
class MainScene :public cocos2d::Layer
{
protected:
	MainScene();
	virtual ~MainScene();
	bool init() override;

public:
	static cocos2d::Scene* createScene();
	void update(float dt) override;
	//stage
	CC_SYNTHESIZE_RETAIN(Stage* , _stage, Stage);
	CC_SYNTHESIZE_RETAIN(Player*, _kawaztan, Player);
	CC_SYNTHESIZE_RETAIN(Bullet*, _bullet, Bullet);

	CREATE_FUNC(MainScene);



};

#endif /*defined(__MyGame__cocos_test__)*/