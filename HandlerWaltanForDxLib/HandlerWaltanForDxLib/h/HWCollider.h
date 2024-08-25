#pragma once
#include "HWComponent.h"


/**
* @author   Suzuki N
* @date     24/07/18
* @note		�����蔻��̏���ێ�����R���|�[�l���g�̒�`
*/


/**
 * @enum		eColliderType
 * @brief		�R���C�_�[�^�C�v
 */
enum class HWColliderType
{
	//! �l�p�`�^�̂����蔻��(0)
	BoxCollider,
	//! ���`�^�̂����蔻��(1)
	SphereCollider,
	//! �J�v�Z���^�̂����蔻��(2)
	CapsuleCollider,
};


/**
 * @class		HWCollider
 * @brief		�����蔻��̏���ێ�����R���|�[�l���g
 */
class HWCollider : public HWComponent
{
private:


public:
	/*     �����o�ϐ�     */

	/**
	 * @brief		�R���C�_�[�^�C�v
	 * @History		24/07/18 �쐬(Suzuki N)
	 */
	HWColliderType colliderType;



	/*     ���\�b�h     */


	/**
	 * @brief		HWCollider�̃R���X�g���N�^
	 * @detail		�C�j�V�����C�Y�p
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	HWCollider() : colliderType(HWColliderType::BoxCollider)
	{
	}


#pragma region �I�[�o�[���C�h���\�b�h

	/**
	 * @brief		�Փ˂����m�����Ƃ��Ɉ�x�Ă΂�郁�\�b�h
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void OnCollisionEnter() override;

#pragma endregion
};
