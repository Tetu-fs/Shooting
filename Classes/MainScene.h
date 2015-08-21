//����define����Ă��Ȃ����
#ifndef __MyGame__MainScene__
//�R���p�C�����ɒu��������@�C���N���[�h�K�[�h�Ƃ����炵���B
//ifndef��endif�̊Ԃɋ��ނƃG���[���o�Ȃ��Ȃ邨�܂��Ȃ��B
#define __MyGame___MainScene__

//�w�b�_�[�t�@�C������ǂݍ���
#include "cocos2d.h"
#include "Stage.h"
#include "Player.h"
#include "SimpleAudioEngine.h"


//Layer�N���X��public�Ōp���N���XMainScene�̐錾�@
class MainScene :public cocos2d::Layer
{
	//MainScene�̒��ł̂�
protected:

	//MainScene�̃R���X�g���N�^�̐錾 �i���O������������킩��Â炢�C�����邪�����������̂炵��
	MainScene();
	
	//virtual�͉��z�֐��Ƃ������܂��Ȃ��@�f�X�g���N�^�̐錾
	virtual ~MainScene();
	
	//CREATE_FUNC���g�p����̂ɕK�v
	//bool�^��init�֐���錾�@override�͂��܂��Ȃ��B
	bool init() override;

	enum class GameState
	{
		PLAYING,

		RESULT
	};

	//�G�N���̃^�C�}�[�Ƃ��̒l�̕ϐ�
	int popTimer;
	int popGuide;
	//�G��|�������̕ϐ�
	int enemyBusted;
	
	//���A�G�o���̗����p
	int enemy_pop;

	//�N���X�O����ł��Q�Ƃł���
public:
	
	// Bullet���i�[�ł���|�C���^�z��i�H�j�A_bullets���`����
	cocos2d::Vector<Bullet *> _bullets;

	// �����\��̒e���X�g�����
	cocos2d::Vector<Bullet *> deletedBullets;

	// Enemy���i�[�ł���|�C���^�z��i�H�j�A_enemys���`����
	cocos2d::Vector<Enemy *> _zako;


	// Enemy���i�[�ł���|�C���^�z��i�H�j�A_enemys���`����
	cocos2d::Vector<Enemy *> _rare;


	// �����\��̓G���X�g�����
	cocos2d::Vector<Enemy *> deletedEnemys;

	// �N���X�֐��ł���cocos2d::Scene�^��*createScene�Ƃ����֐��̐錾
	static cocos2d::Scene* createScene();

	//cocos2d::Vec2�Ƃ����^��_velocity�Ƃ��������o�ϐ����`���Ă���
	//���̕ϐ��̓L�����N�^�[�̑��x��\���A���t���[�����̑��x�����ݍ��W�ɉ����邱�Ƃňړ����Ă���
	cocos2d::Vec2 _velocity; // �ړ���

	// void�^��update(float dt)�Ƃ����֐��̐錾�@override�͂��܂��Ȃ��B
	void update(float dt) override;
	//�@void�^�̒������O�̊֐��̐錾
	void onEnterTransitionDidFinish() override;

	//���U���g�̏���
	void onResult();

	//stage���ɂ���ƁAStage*�Ƃ����^������AMainScene�N���X��private�ϐ�_stage�����AgetStage/setStage������
	//getStage��_stage���擾���AsetStage��_stage��������������
	CC_SYNTHESIZE_RETAIN(Stage* , _stage, Stage);
	CC_SYNTHESIZE_RETAIN(Player*, _player, Player);

	CC_SYNTHESIZE(long, _score, Score);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _scoreLabel, ScoreLabel);
	
	CC_SYNTHESIZE(int, _life, Life);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _lifeLabel, LifeLabel);

	CC_SYNTHESIZE(GameState, _state, State);


	//auto mainScene = MainScene::create(); �Ɠ����Ӗ��Bbool init();���K�v
	//��L��MainScene�^��*mainScene�Ƃ����|�C���^�ϐ���MainScene::create()�������Ă���
	CREATE_FUNC(MainScene);


};
//ifndef���炱���܂ł��R���p�C������@�炵��
#endif /*defined(__MyGame___MainScene__)*/