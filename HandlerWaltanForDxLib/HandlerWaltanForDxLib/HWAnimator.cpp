#include "h/HWAnimator.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		HWAnimator�̎����t�@�C��
*/


#pragma region private���\�b�h


void HWAnimator::AnimPlay()
{
	// �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
	if (animBlendRate < 1.0f)
	{
		animBlendRate += PLAYER_ANIM_BLEND_SPEED * GameTime::DeltaTime();
		if (animBlendRate > 1.0f)
		{
			animBlendRate = 1.0f;
		}
	}

	// �Đ����Ă���A�j���[�V�����P�̏���
	if (playAnimId1 != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		float animTotalTime = animInfoVec[playAnimId1]->totalTime;

		// �Đ����Ԃ�i�߂�
		playTime1 += animInfoVec[playAnimId1]->playSpeed * GameTime::DeltaTime();

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (playTime1 >= animTotalTime)
		{
			playTime1 = fmodf(playTime1, animTotalTime);
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(animInfoVec[playAnimId1]->modelHandle, playAnimId1, playTime1);

		// �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(animInfoVec[playAnimId1]->modelHandle, playAnimId1, animBlendRate);
	}

	// �Đ����Ă���A�j���[�V�����Q�̏���
	if (playAnimId1 != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		float animTotalTime = MV1GetAttachAnimTotalTime(animInfoVec[playAnimId2]->modelHandle, playAnimId2);

		// �Đ����Ԃ�i�߂�
		playTime2 += animInfoVec[playAnimId2]->playSpeed * GameTime::DeltaTime();

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (playTime2 > animTotalTime)
		{
			playTime2 = fmodf(playTime2, animTotalTime);
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(animInfoVec[playAnimId2] ->modelHandle, playAnimId2, playTime2);

		// �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(animInfoVec[playAnimId2]->modelHandle , playAnimId2, 1.0f - animBlendRate);
	}
}


#pragma endregion

#pragma region public���\�b�h


HWAnimator::~HWAnimator()
{
	for (auto it = animInfoVec.begin(); it != animInfoVec.end(); ++it)
		MV1DeleteModel((*it)->animHandle);
}

AnimInfo& HWAnimator::AnimLoad(const std::string& _filePath, const int _animId)
{
	//! �A�j���[�V���������܂Ƃ߂��N���X�̃C���X�^���X�𐶐�
	std::unique_ptr<AnimInfo> animInfo = std::make_unique<AnimInfo>();

	// �������������s��
	animInfo->filePath = _filePath;
	animInfo->animHandle = MV1LoadModel(_filePath.c_str());
	animInfo->modelHandle = gameObject->GetComponent<HWRenderer>()->GetModelHandle();
	animInfo->interruption = true;
	animInfo->isLoop = false;
	animInfo->playSpeed = 1.0f;
	animInfo->totalTime = MV1GetAttachAnimTotalTime(animInfo->animHandle, _animId);

	// ���L����vector�Ɉڂ�
	animInfoVec.push_back(std::move(animInfo));

	return *animInfoVec.back();
}

void HWAnimator::AnimChange(const int _animId)
{
	// �w���̗����A�j���[�V�����ԍ����o�^����Ă���A�j���[�V�����̑����𒴉߂��Ă���ꍇ
	if (_animId >= animInfoVec.size())
		return;

	// �Đ��A�j���[�V����ID�������l�������ꍇ��
	// �p�����[�^���Q�Ƃ����Ɏw���̗����A�j���[�V�������Z�b�g
	if (playAnimId1 == -1)
	{
		// �e�p�����[�^���㏑��
		isStop = false;
		playAnimId1 = _animId;
	}

	// �����A�j���[�V�������Đ��͂��Ȃ�
	else if (playAnimId1 == _animId) return;

	// ���f�s�̃A�j���[�V�������A
	// �Đ����Ԃ��g�[�^�����Ԃ𒴉߂��Ă��Ȃ��ꍇ�͂��̂܂܏I��
	if (!animInfoVec[playAnimId1]->interruption && 
		playTime1 <= animInfoVec[playAnimId1]->totalTime) return;

	// �Đ��w�����ʂ���

	// �Đ����̃A�j���[�V����2�����łɑ��݂���ꍇ�̓f�^�b�`����
	if (playAnimId2 != -1)
	{
		MV1DetachAnim(animInfoVec[playAnimId1]->modelHandle, playAnimId2);
		playAnimId2 = -1;
	}
	// �A�j���[�V����1�̏���2�Ɉړ�����
	playAnimId2 = playAnimId1;
	playTime2 = playTime1;

	// �V�����A�j���[�V�������A�^�b�`
	playAnimId1 = MV1AttachAnim(animInfoVec[_animId]->modelHandle, 0, animInfoVec[_animId]->animHandle);
	playTime1 = 0.0f;

	// �u�����h���͍Đ����̃��[�V�����Q���L���ł͂Ȃ��ꍇ�͂P�D�O��( �Đ����̃��[�V�����P���P�O�O���̏�� )�ɂ���
	animBlendRate = playAnimId2 == -1 ? 1.0f : 0.0f;
}


#pragma endregion

#pragma region protected���\�b�h




#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h


void HWAnimator::Awake()
{
	// �����l�����Ă���
	playTime1 = 0.0f;
	playAnimId1 = -1;
	isStop = false;
}

void HWAnimator::Update()
{
	AnimPlay();
}


#pragma endregion



