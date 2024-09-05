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
public:

	/*     �����o�ϐ�     */

	/**
	 * @brief		���[���h���W
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	VECTOR position;

	/**
	 * @brief		��]
	 * @History		24/06/17 �쐬(Suzuki N)
	 */

	VECTOR rotate;

	/**
	 * @brief		�g�k
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	VECTOR scale;


public:

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
	VECTOR GetPosition() { return position; }

	/**
	 * @brief		��]��Ԃ�
	 * @return		��]
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	VECTOR GetRotate() { return rotate; }

	/**
	 * @brief		�g�k�x��Ԃ�
	 * @return		�g�k
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	VECTOR GetScale() { return scale; }

#pragma endregion

#pragma region Setter���\�b�h�Q

	/**
	 * @brief		���[���h���W��ύX
	 * @param[in]	�ύX��̍��W
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void SetPosition(VECTOR _pos) { position = _pos; }

	/**
	 * @brief		��]��ύX
	 * @param[in]	�ύX��̉�]
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void SetRotate(VECTOR _rot) { rotate = _rot; }

	/**
	 * @brief		�g�k��ύX
	 * @param[in]	�ύX��̊g�k
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void SetScale(VECTOR _scale) { scale = _scale; }

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
