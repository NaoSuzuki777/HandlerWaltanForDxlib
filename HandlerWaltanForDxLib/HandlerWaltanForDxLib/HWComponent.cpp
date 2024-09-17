#include "h/HWComponent.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		HWComponent�̎����t�@�C��
*/


#pragma region private���\�b�h




#pragma endregion

#pragma region public���\�b�h


void HWComponent::OnCollisionEnterHandler(HWCollider* _collider)
{
	if (OnCollisionEnterCallBack)
		OnCollisionEnterCallBack(_collider);
}

void HWComponent::OnCollisionStayHandler(HWCollider* _collider)
{
	if (OnCollisionStayCallBack)
		OnCollisionStayCallBack(_collider);
}

void HWComponent::OnCollisionExsitHandler(HWCollider* _collider)
{
	if (OnCollisionExitCallBack)
		OnCollisionExitCallBack(_collider);
}


#pragma endregion

#pragma region protected���\�b�h


HWComponent::HWComponent() : isMultiplePossession(true), active(true)
{
	//�e�R�[���o�b�N�֐��ɃI�[�o�[���C�h���ꂽ���\�b�h��������
	OnCollisionEnterCallBack = std::bind(&HWComponent::OnCollisionEnter, this, std::placeholders::_1);
	OnCollisionStayCallBack = std::bind(&HWComponent::OnCollisionStay, this, std::placeholders::_1);
	OnCollisionExitCallBack = std::bind(&HWComponent::OnCollisionExit, this, std::placeholders::_1);
}


#pragma endregion

