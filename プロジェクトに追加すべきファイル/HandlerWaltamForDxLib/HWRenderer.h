#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"


/**
* @author   Suzuki N
* @date     24/08/25
* @note		���f���`��R���|�[�l���g�̒�`
*/


/**
 * @class		HWRenderer
 * @brief		���f���`��p�̃R���|�[�l���g
 */
class HWRenderer : public HWComponent
{
private:

	/*     �����o�ϐ�     */

	/**
	 * @brief		���f���n���h��
	 * @History		24/08/25 �쐬(Suzuki N)
	 */
	int modelHandle;


public:

	/*     ���\�b�h     */

	/**
	 * @brief		HWRenderer�̃R���X�g���N�^
	 * @param[in]	int ���f���n���h��
	 * @author		Suzuki N
	 * @date		24/08/25
	 */
	HWRenderer(int _modelHandle);

#pragma region �I�[�o�[���C�h���\�b�h

	/**
	 * @brief		���t���[���Ă΂��
	 * @detail		�I�[�o�[���C�h�֐�
	 * @author		Suzuki N
	 * @date		24/09/01
	 */
	void Update() override;

#pragma endregion
};

