//����define����Ă��Ȃ����
#ifndef __MyGame__stage__
//�R���p�C�����ɒu��������@�C���N���[�h�K�[�h�Ƃ����炵���B
//ifndef��endif�̊Ԃɋ��ނƃG���[���o�Ȃ��Ȃ邨�܂��Ȃ��B
#define __MyGame__stage__
//cocos2d.h�����
#include "cocos2d.h"
//cocos2d::Layer�N���X�̃p�u���b�N�Ōp���N���XStage�����
class Stage :public cocos2d::Layer
{
	//Stage�N���X���ł̂�
protected:
	//Stage�R���X�g���N�^�̐錾
	Stage();
	//Stage�f�X�g���N�^�̐錾�@virtual�͂��܂��Ȃ�
	virtual ~Stage();

	//bool�^��init()�֐��̐錾 override�͂��܂��Ȃ�
	//CREATE_FUNC()�ɕK�{
	bool init() override;

	//�N���X�O����ł��Q�Ɖ\
public:
	//void�^��update(float dt)�֐��̐錾�@override�͂��܂��Ȃ�
	void update(float dt) override;

	//Tile
	//TMXTiledMap�Ƃ����^������AStage�N���X��private�ϐ�_tiledMap�����AgetTledMap/setTledMap������
	//�����ł���ꂽTMXTiledMap�^�̕ϐ��̓|�C���^�ϐ��ɂȂ�
	//getTledMap��_tiledMap���擾���AsetTledMap��_tiledMap��������������
	CC_SYNTHESIZE_RETAIN(cocos2d::TMXTiledMap *, _tiledMap, TiledMap);

	//static Stage* create()�Ɠ����Ӗ��Bbool init();���K�v
	//Stage�N���X�C���X�^���X�ւ̃|�C���^��Ԃ�Stage�N���X�̃N���X���\�b�h�Acreate��錾���Ă���
	CREATE_FUNC(Stage);
};

#endif /*defined(__MyGame__stage__)*/