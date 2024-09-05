#include "h/HWRenderer.h"


/**
* @author   Suzuki N
* @date     24/08/25
* @note		HWRenderer�̎����t�@�C��
*/


#pragma region �R���X�g���N�^


HWRenderer::HWRenderer(int _modelHandle) : modelHandle(_modelHandle)
{
}


#pragma endregion

#pragma region private���\�b�h




#pragma endregion

#pragma region public���\�b�h





#pragma endregion


#pragma region �I�[�o�[���C�h���\�b�h


void HWRenderer::Update()
{
	auto transform = gameObject->GetComponent<HWTransform>();
	MV1SetPosition(modelHandle, transform->GetPosition());
}


#pragma endregion
