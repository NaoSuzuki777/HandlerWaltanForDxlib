#include"h/HWTransform.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		MyTransform�̎����t�@�C��
*/


#pragma region private���\�b�h


#pragma endregion

#pragma region public���\�b�h


HWTransform::HWTransform()
{
	position = { 0.0f, 0.0f, 0.0f };
	rotate = { 0.0f, 0.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };
	localPosition = { 0.0f, 0.0f, 0.0f };
	localRotate = { 0.0f, 0.0f, 0.0f };
	localScale = { 1.0f, 1.0f, 1.0f };
}


#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h


void HWTransform::Update()
{
}


#pragma endregion