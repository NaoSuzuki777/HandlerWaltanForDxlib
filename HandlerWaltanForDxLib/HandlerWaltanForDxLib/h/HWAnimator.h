#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"
#include "HWRenderer.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		�A�j���[�V��������R���|�[�l���g�̒�`
*/


/**
 * @class	AnimInfo
 * @brief	�A�j���[�V�������
 */
class AnimInfo
{
public:

	/*     �����o�ϐ�     */

	/**
	 * @brief		�A�j���[�V�������A�^�b�`���郂�f��
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	int modelHandle;

	/**
	 * @brief		�A�j���[�V�����̃n���h��
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	int animHandle;

	/**
	 * @brief		�A�^�b�`����A�j���[�V�������f���̃C���f�b�N�X
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	int animIndex;

	/**
	 * @brief		���ԖڂɃA�^�b�`���ꂽ��
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	int playIndex;

	/**
	 * @brief		�A�j���[�V�����t�@�C��
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	std::string filePath;

	/**
	 * @brief		���[�v���邩
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	bool isLoop;

	/**
	 * @brief		���f�\��
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	bool interruption;

	/**
	 * @brief		�Đ����x
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	float playSpeed;

	/**
	 * @brief		���Đ�����
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	float totalTime;


public:
	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	AnimInfo(){}
};


/**
 * @class	HWAnimator
 * @brief	�A�j���[�V��������Ǘ��p�̃R���|�[�l���g
 */
class HWAnimator : public HWComponent
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;

public:

	/*     �����o�ϐ�     */

	/**
	 * @brief		�e�A�j���[�V�������
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	std::vector<std::unique_ptr<AnimInfo>> animInfoVec;

	/**
	 * @brief		�A�j���[�V����1�̌��݂̍Đ�����
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	float playTime1;

	/**
	 * @brief		�A�j���[�V����2�̌��݂̍Đ�����
	 * @History		24/09/25 �쐬(Suzuki N)
	 */
	float playTime2;

	/**
	 * @brief		�Đ����̃A�j���[�V����1�C���f�b�N�X
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	int playAnimId1;

	/**
	 * @brief		�Đ����̃A�j���[�V����2�C���f�b�N�X
	 * @History		24/09/25 �쐬(Suzuki N)
	 */
	int playAnimId2;

	/**
	 * @brief		playAnimId1 �� playAnimId2 �̃u�����h��
	 * @History		24/09/25 �쐬(Suzuki N)
	 */
	float animBlendRate;

	/**
	 * @brief		�Đ����~
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	bool isStop;

private:

	/**
	 * @brief		�A�j���[�V�����̍Đ����I�������Ƃ��ɍĐ�����Idle��ID
	 * @History		24/09/24 �쐬(Suzuki N)
	 */
	int defaultAnimId = 0;


public:
	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	HWAnimator(){}

	/**
	 * @brief		�f�X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	~HWAnimator();

	/**
	 * @brief		�A�j���[�V���������[�h���� �����[�h����A�j���[�V�����̓A�j���[�V��������������Ă��Ȃ�����
	 * @param[in]	const std::string& �A�j���[�V�����t�@�C���̃p�X
	 * @param[in]	const int		   �ǂݍ��ރA�j���[�V����ID
	 * @return		AnimInfo& �A�j���[�V�������(�߂�l����p�����[�^�𑀍삷��)
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	AnimInfo& AnimLoad(const std::string& _filePath, const int _animId = 0);

	/**
	 * @brief		�Đ�����A�j���[�V�������w��
	 * @param[in]	const int �Đ�����A�j���[�V����ID
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	void AnimChange(const int _animId);

#pragma region Setter�֐�

	/**
	 * @brief		�A�j���[�V�����̍Đ����I���������Ɏ����Đ������default�A�j���[�V����(Idol�A�j���[�V�����Ȃ�)
	 * @param[in]	const int �f�t�H���g�̃A�j���[�V����ID
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	void SetDefaultAnimId(const int _defaultAnimId) { defaultAnimId = _defaultAnimId; }

#pragma endregion


private:

	/**
	 * @brief		�A�j���[�V�������Đ�����
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	void AnimPlay();



protected:

#pragma region �I�[�o�[���C�h���\�b�h

	/**
	 * @brief		HWGameObject�ɃA�^�b�`���ꂽ�u�Ԃɓ���
	 * @detail		�I�[�o���C�h���\�b�h
	 * @author		Suzuki N
	 * @date		24/09/25
	 */
	void Awake()override;

	/**
	 * @brief		���t���[���Ă΂��
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		Suzuki N
	 * @date		24/09/25
	 */
	void Update() override;

#pragma endregion
};

