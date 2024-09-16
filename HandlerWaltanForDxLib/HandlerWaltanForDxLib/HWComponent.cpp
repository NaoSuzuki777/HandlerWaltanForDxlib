#include "h/HWComponent.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		HWComponent�̎����t�@�C��
*/


#pragma region private���\�b�h




#pragma endregion

#pragma region public���\�b�h


void HWComponent::OnCollisionEnterHandler()
{
	if (OnCollisionEnterCallBack)
		OnCollisionEnterCallBack();
}

void HWComponent::OnCollisionStayHandler()
{
	if (OnCollisionStayCallBack)
		OnCollisionStayCallBack();
}

void HWComponent::OnCollisionExsitHandler()
{
	if (OnCollisionExitCallBack)
		OnCollisionExitCallBack();
}


#pragma endregion

#pragma region protected���\�b�h


HWComponent::HWComponent() : isMultiplePossession(true), active(true)
{
	//�e�R�[���o�b�N�֐��ɃI�[�o�[���C�h���ꂽ���\�b�h��������
	OnCollisionEnterCallBack = std::bind(&HWComponent::OnCollisionEnter, this);
	OnCollisionStayCallBack = std::bind(&HWComponent::OnCollisionStay, this);
	OnCollisionExitCallBack = std::bind(&HWComponent::OnCollisionExit, this);
}


#pragma endregion

