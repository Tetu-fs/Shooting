#ifndef __MyGame__stage__
#define __MyGame__stage__

#include "cocos2d.h"

class Stage :public cocos2d::Layer
{
protected:
	Stage();
	virtual ~Stage();
	bool init() override;

public:
	void update(float dt) override;
	//Tile
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXTiledMap *, _tiledMap, TiledMap);
	CREATE_FUNC(Stage);
};

#endif /*defined(__MyGame__stage__)*/