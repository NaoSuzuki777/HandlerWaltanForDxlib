#include "h/HWAnimator.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		HWAnimator�̎����t�@�C��
*/


#pragma region private���\�b�h


void HWAnimator::AnimPlay()
{
	// �Đ�����A�j���[�V���������ݒ�(-1)�������ꍇ�͂��̂܂܏I��
	if (playAnimId == -1) return;

	// �Đ����Ԃ�i�߂�
	playTime += animInfoVec[playAnimId]->playSpeed;
	// �Đ����Ԃ��g�[�^���^�C���𒴂����ꍇ
	if (playTime > animInfoVec[playAnimId]->totalTime)
	{
		// ���[�v�t���O�������Ă���ꍇ�AplayTime��������
		if (animInfoVec[playAnimId]->isLoop)
			playTime = 0.0f;
		// ���[�v�A�j���[�V��������Ȃ���΃f�t�H���g�ɐݒ肳��Ă���A�j���[�V�����������Đ�
		else
			AnimChange(defaultAnimId);
	}

	// �A�j���[�V�������Đ�����
	MV1AttachAnim(animInfoVec[playAnimId]->modelHandle, 0, animInfoVec[playAnimId]->animHandle);
}


#pragma endregion

#pragma region public���\�b�h


AnimInfo& HWAnimator::AnimLoad(const std::string& _filePath, const int _animId)
{
	//! �A�j���[�V���������܂Ƃ߂��N���X�̃C���X�^���X�𐶐�
	std::unique_ptr<AnimInfo> animInfo = std::make_unique<AnimInfo>();

	// �������������s��
	animInfo->filePath = _filePath;
	animInfo->animHandle = MV1LoadModel(_filePath.c_str());
	animInfo->modelHandle = gameObject->GetComponent<HWRenderer>()->GetModelHandle();
	animInfo->interruption = false;
	animInfo->isLoop = false;
	animInfo->playSpeed = 1.0f;
	animInfo->totalTime = MV1GetAttachAnimTotalTime(animInfo->animHandle, _animId);

	// ���L����vector�Ɉڂ�
	animInfoVec.push_back(std::move(animInfo));

	return *animInfoVec.back();
}

void HWAnimator::AnimChange(const int _animId)
{
	// �Đ��A�j���[�V����ID�������l�������ꍇ��
	// �p�����[�^���Q�Ƃ����Ɏw���̗����A�j���[�V�������Z�b�g
	if (playAnimId == -1)
	{
		// �e�p�����[�^���㏑��
		playAnimId = _animId;
		isStop = false;
	}
	// �����A�j���[�V�������Đ��͂��Ȃ�
	else if (playAnimId == _animId) return;

	// ���f�s�̃A�j���[�V�������A
	// �Đ����Ԃ��g�[�^�����Ԃ𒴉߂��Ă��Ȃ��ꍇ�͂��̂܂܏I��
	if (!animInfoVec[playAnimId]->interruption && 
		playTime <= animInfoVec[playAnimId]->totalTime) return;

	// �Đ��w�����ʂ���
	playAnimId = _animId;
}


#pragma endregion

#pragma region protected���\�b�h




#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h


void HWAnimator::Awake()
{
	// �����l�����Ă���
	playTime = 0.0f;
	playAnimId = -1;
	isStop = false;
}

void HWAnimator::Update()
{
	AnimPlay();
}


#pragma endregion



