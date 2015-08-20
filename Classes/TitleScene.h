//もしdefineされていなければ
#ifndef __MyGame__TitleScene__
//コンパイル時に置き換える　インクルードガードというらしい。
//ifndefとendifの間に挟むとエラーが出なくなるおまじない。
#define __MyGame___TitleScene__

#include "cocos2d.h"

class TitleScene :public cocos2d::Layer
{
protected:
	TitleScene();
	virtual ~TitleScene();
	bool init() override;
public:
	static cocos2d::Scene* createScene();
	void gameStart();

	CREATE_FUNC(TitleScene);
};

#endif /*defined(__MyGame__TitleScene__*/