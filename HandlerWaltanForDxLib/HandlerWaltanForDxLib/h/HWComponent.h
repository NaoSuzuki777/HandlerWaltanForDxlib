#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include "DxLib.h"
#include "Utilities.h"


/**
* @author   Suzuki N
* @date     24/07/16
* @note     ���ׂẴR���|�[�l���g�̊��N���X�̒�`�t�@�C��
*/


//HWComponent�N���X�������o�ϐ���HWGameObject�N���X���������邽�߂ɑO���錾
class HWGameObject;


class HWComponent
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HWGameObject;
	friend class CollisionWaltan;

public:
	/*     �����o�ϐ�     */

	/**
	 * @brief		���̃R���|�[�l���g���A�^�b�`����Ă���HWGameObject
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	HWGameObject* gameObject;

	/**
	 * @brief		�����A�^�b�`�\�ȃR���|�[�l���g��
	 * @History		24/08/03 �쐬(Suzuki N)
	 */
	bool isMultiplePossession;

	/**
	 * @brief		�R���|�[�l���g�̃A�N�e�B�u
	 * @History		24/08/03 �쐬(Suzuki N)
	 */
	bool active;


private:

	/**
	 * @brief		�Փ˔������������ɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/07/19 �쐬(Suzuki N)
	 */
	std::function<void()> OnCollisionEnterCallBack;

	/**
	 * @brief		�Փ˔��������Ă���ԂɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/07/19 �쐬(Suzuki N)
	 */
	std::function<void()> OnCollisionStayCallBack;
	
	/**
	 * @brief		�Փ˔��肪�����ꂽ���ɌĂ΂��R�[���o�b�N�֐�
	 * @History		24/07/19 �쐬(Suzuki N)
	 */
	std::function<void()> OnCollisionExitCallBack;


public:


	/*     ���\�b�h     */


	/**
	 * @brief		�A�^�b�`����Ă���HWGameObject�ɃC���X�^���X��������
	 * @param[in]	HWGameObject* _gameObject  �������HWGameObject
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void SetGameObject(HWGameObject* _gameObject)
	{
		gameObject = _gameObject;
	}

	/**
	 * @brief		�A�^�b�`����Ă���HWGameObject��Ԃ�
	 * @return		�R���|�[�l���g���A�^�b�`����Ă���HWGameObject
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	HWGameObject* GetGameObject()
	{
		return gameObject;
	}

protected:

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	HWComponent() : isMultiplePossession(false), active(true)
	{
		//�e�R�[���o�b�N�֐��ɃI�[�o�[���C�h���ꂽ���\�b�h��������
		OnCollisionEnterCallBack = std::bind(&HWComponent::OnCollisionEnter, this);
		OnCollisionStayCallBack = std::bind(&HWComponent::OnCollisionStay, this);
		OnCollisionExitCallBack = std::bind(&HWComponent::OnCollisionExit, this);
	}

#pragma region ���z�֐��Q

	/**
	 * @brief		HWGameObject�ɃA�^�b�`���ꂽ�u�Ԃɓ���
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	virtual void Start() {}


	/**
	 * @brief		���t���[���Ă΂�郁�\�b�h
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	virtual void Update() {}


	/**
	 * @brief		�R���C�_�[�Փˎ��ɓ������\�b�h
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnCollisionEnter() {}


	/**
	 * @brief		�R���C�_�[�Փ˒��ɓ������\�b�h
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnCollisionStay() {}


	/**
	 * @brief		�R���C�_�[�Փ˂��������ɓ������\�b�h
	 * @detail		���z�֐�
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	virtual void OnCollisionExit() {}

#pragma endregion

public:

#pragma region �o�^���ꂽ�R�[���o�b�N�֐����Ăԃ��\�b�h�Q

	/**
	 * @brief		�o�^���ꂽ�Փˎ��ɓ������\�b�h�𓭂�����
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnCollisionEnterHandler()
	{
		if (OnCollisionEnterCallBack)
			OnCollisionEnterCallBack();
	}

	/**
	 * @brief		�o�^���ꂽ�Փˎ��ɓ������\�b�h�𓭂�����
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnCollisionStayHandler()
	{
		if (OnCollisionStayCallBack)
			OnCollisionStayCallBack();
	}

	/**
	 * @brief		�o�^���ꂽ�Փˎ��ɓ������\�b�h�𓭂�����
	 * @author		Suzuki N
	 * @date		24/07/19
	 */
	void OnCollisionExsitHandler()
	{
		if (OnCollisionExitCallBack)
			OnCollisionExitCallBack();
	}

#pragma endregion
};

