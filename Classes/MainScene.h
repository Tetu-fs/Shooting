//����define����Ă��Ȃ����
#ifndef __MyGame__cocos_test__
//�R���p�C�����ɒu��������@�C���N���[�h�K�[�h�Ƃ����炵���B
//ifndef��endif�̊Ԃɋ��ނƃG���[���o�Ȃ��Ȃ邨�܂��Ȃ��B
#define __MyGame__cocos_test__

//�w�b�_�[�t�@�C������ǂݍ���
#include "cocos2d.h"
#include "Stage.h"
#include "Player.h"

//Layer�N���X��public�Ōp���N���XMainScene�̐錾�@
class MainScene :public cocos2d::Layer
{
	//MainScene�̒��ł̂�
protected:
	
	//MainScene�̃R���X�g���N�^�̐錾 �i���O������������킩��Â炢�C�����邪�����������̂炵��
	MainScene();
	
	//virtual�͉��z�֐��Ƃ������܂��Ȃ��@�f�X�R���X�g���N�^�̐錾
	virtual ~MainScene();
	
	//CREATE_FUNC���g�p����̂ɕK�v
	//bool�^��init�֐���錾�@override�͂��܂��Ȃ��B
	bool init() override;
	
	//�N���X�O����ł��Q�Ƃł���
public:
	
	// �N���X�֐��ł���cocos2d::Scene�^��*createScene�Ƃ����֐��̐錾
	static cocos2d::Scene* createScene();

	// void�^��update(float dt)�Ƃ����֐��̐錾�@override�͂��܂��Ȃ��B
	void update(float dt) override;
	//stage���ɂ���ƁAStage*�Ƃ����^������AMainScene�N���X��private�ϐ�_stage�����AgetStage/setStage������
	//getStage��_stage���擾���AsetStage��_stage��������������
	CC_SYNTHESIZE_RETAIN(Stage* , _stage, Stage);
	CC_SYNTHESIZE_RETAIN(Player*, _player, Player);
	CC_SYNTHESIZE_RETAIN(Bullet*, _bullet, Bullet);

	//auto mainScene = MainScene::create(); �Ɠ����Ӗ��Bbool init();���K�v
	//��L��MainScene�^��*mainScene�Ƃ����|�C���^�ϐ���MainScene::create()�������Ă���
	CREATE_FUNC(MainScene);


};
//ifndef���炱���܂ł��R���p�C������@�炵��
#endif /*defined(__MyGame__cocos_test__)*/