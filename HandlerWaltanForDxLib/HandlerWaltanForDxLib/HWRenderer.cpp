#include "h/HWRenderer.h"


/**
* @author   Suzuki N
* @date     24/08/25
* @note		HWRenderer�̎����t�@�C��
*/


#pragma region �R���X�g���N�^


HWRenderer::HWRenderer(const int _modelHandle) : modelHandle(_modelHandle)
{
}

HWRenderer::HWRenderer(const std::string& _pass)
{
	modelHandle = MV1LoadModel(_pass.c_str());
}


#pragma endregion

#pragma region private���\�b�h




#pragma endregion

#pragma region public���\�b�h





#pragma endregion


#pragma region �I�[�o�[���C�h���\�b�h


void HWRenderer::Update()
{
	if (modelHandle == -1)
	{
		return;
	}

	// HWTransform�̃O���[�o���ϊ��s����Q�Ƃ��ă��f���ɓK�p
	MV1SetMatrix(modelHandle, transform->globalMat);
	// ���f����`��
	MV1DrawModel(modelHandle);
}


#pragma endregion
