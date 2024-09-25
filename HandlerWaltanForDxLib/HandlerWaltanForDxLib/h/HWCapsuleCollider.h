#pragma once
#include "HWCollider.h"
#include "HandlerWaltan.h"
#include "CollisionWaltan.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		�J�v�Z���^�̃R���C�_�[�R���|�[�l���g�̒�`
*/


/**
 * @class	HWCapsuleCollider
 * @brief	�J�v�Z���^�̃R���C�_�[�R���|�[�l���g
 */
class HWCapsuleCollider : public HWCollider
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;
	friend class CollisionWaltan;

public:

	/*     �����o�ϐ�     */

	/**
	 * @brief		�R���C�_�[�̎n�_
	 * @History		24/09/16 �쐬(Suzuki N)
	 */
	VECTOR startPos;

	/**
	 * @brief		�R���C�_�[�̏I�_
	 * @History		24/09/16 �쐬(Suzuki N)
	 */
	VECTOR endPos;

	/**
	 * @brief		�R���C�_�[�̔��a
	 * @History		24/09/16 �쐬(Suzuki N)
	 */
	float radius;

	/**
	 * @brief		��]�s��
	 * @History		24/09/16 �쐬(Suzuki N)
	 */
	MATRIX mRotate;


	 /*     ���\�b�h     */

public:

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	HWCapsuleCollider();

	/**
	 * @brief		�f�X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	~HWCapsuleCollider();

#pragma region �I�[�o�[���C�h���\�b�h


	/**
	 * @brief		�����̂̃R���C�_�[��`�悷��
	 * @detail		�I�[�o���C�h���\�b�h
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	void DrawCollider() override;

	/**
	 * @brief		�����̂̃R���C�_�[���\������
	 * @detail		�I�[�o���C�h���\�b�h
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	void SetCollider() override;

	/**
	 * @brief		HWGameObject�ɃA�^�b�`���ꂽ�u�Ԃɓ���
	 * @detail		�I�[�o���C�h���\�b�h
	 * @author		Suzuki N
	 * @date		24/09/15
	 */
	void Awake()override;

	/**
	 * @brief		���t���[���Ă΂��
	 * @detail		�I�[�o�[���C�h���\�b�h
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	void Update() override;

#pragma endregion
};

