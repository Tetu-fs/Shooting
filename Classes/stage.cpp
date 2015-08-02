#include "Stage.h"

USING_NS_CC;


Stage::Stage()
	: _tiledMap(nullptr)
{
}

Stage::~Stage()
{
	CC_SAFE_RELEASE_NULL(_tiledMap);
}

bool Stage::init()
{
	int x = 0;
	int y = 0;

	if (!Layer::init())
	{
		return false;
	}

	auto map = TMXTiledMap::create("test_map.tmx");
	TMXLayer* background = map->getLayer("background"); // Tiledで設定したレイヤーの名前を渡す
	TMXLayer* yuka = map->getLayer("yuka"); // Tiledで設定したレイヤーの名前を渡す
	background->getTileAt(Vec2(x, y));
	background->getTileGIDAt(Vec2(x, y));
	yuka->getTileAt(Vec2(x, y));
	yuka->getTileGIDAt(Vec2(x, y));
	this->setPosition(320, 240);
	this->setScale(2.0f);
	this->addChild(map);
	this->setTiledMap(map);

	this->scheduleUpdate();

	return true;

}

void Stage::update(float dt)
{

}