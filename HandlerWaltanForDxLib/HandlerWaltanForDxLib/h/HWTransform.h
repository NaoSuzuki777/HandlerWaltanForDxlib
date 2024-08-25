#pragma once
#include "HWComponent.h"


/**
* @author   Suzuki N
* @date     24/07/16
* @note		���W�n�̏���ێ�����R���|�[�l���g�̒�`
*/


/**
 * @class		HWTransform
 * @brief		�I�u�W�F�N�g�̍��W���]�Ȃǂ�ێ�����R���|�[�l���g
 */
class HWTransform : public HWComponent
{
private:


public:
	/*     �����o�ϐ�     */

	/**
	 * @brief		���[���h���W
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	VECTOR Position;


	/*     ���\�b�h     */

#pragma region �R���X�g���N�^

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	HWTransform();

#pragma endregion


#pragma region Getter���\�b�h�Q

	/**
	 * @brief		���[���h���W��Ԃ�
	 * @return		���[���h���W
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	VECTOR GetPosition() { return Position; }

#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h

	/**
	 * @brief		���t���[���Ă΂��
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void Update() override;

#pragma endregion
};
