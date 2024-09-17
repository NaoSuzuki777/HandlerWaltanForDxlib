#pragma once
#include <stdarg.h>
#include <algorithm>
#include "HWComponent.h"
#include "HWTransform.h"


/**
* @author   Suzuki N
* @date     24/07/16
* @note		�R���|�[�l���g���Ǘ�����A���ׂẴI�u�W�F�N�g�����N���X�̒�`
*/


/**
 * @class	HWGameObject
 * @brief	�I�u�W�F�N�g�Ɋւ�������܂Ƃ߂��N���X
 */
class HWGameObject
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HandlerWaltan;
	friend class CollisionWaltan;

private:

	/*     �����o�ϐ�     */

	/**
	 * @brief   �C���X�^���X�����ꂽ�I�u�W�F�N�g�S�Ă�ۊǂ��Ă����R���e�i
	 * @History 24/07/19 �쐬(Suzuki N)
	 */
	static std::vector<HWGameObject*> gameObjects;

	/**
	 * @brief		�A�^�b�`����Ă���S�ẴR���|�[�l���g
	 * @History		24/06/17 �쐬(Suzuki N)
	 */
	std::vector<std::unique_ptr<HWComponent>> hwComponents;

public:

	/**
	 * @brief		�I�u�W�F�N�g�̖��O
	 * @History		24/07/29 �쐬(Suzuki N)
	 */
	std::string name;

	/**
	 * @brief		�n���h���[��Update���\�b�h�̗D�揇��(�~��)
	 * @History		24/07/21 �쐬(Suzuki N)
	 */
	int priority;


private:

	/*     ���\�b�h     */

	/**
	 * @brief       �v���C�I���e�B���Q�Ƃ��ă\�[�g����
	 * @author      Suzuki N
	 * @date        24/07/19
	 */
	void BubbleSort();

	/**
	 * @brief       �S�ẴR���|�[�l���g��Update���\�b�h���Ăт���
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllUpdates();

	/**
	 * @brief       �S�ẴR���|�[�l���g��OnCollisionEnterCallBack���\�b�h���Ăт���
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionEnters(HWCollider* _collider);

	/**
	 * @brief       �S�ẴR���|�[�l���g��OnCollisionStayCallBack���\�b�h���Ăт���
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionStays(HWCollider* _collider);

	/**
	 * @brief       �S�ẴR���|�[�l���g��OnCollisionExitCallBack���\�b�h���Ăт���
	 * @author      Suzuki N
	 * @date        24/08/22
	 */
	void CallAllOnCollisionExits(HWCollider* _collider);


public:

#pragma region �R���X�g���N�^

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject();

	/**
	 * @brief		�R���X�g���N�^(���O�̏������錾)
	 * @param[in]	std::string �I�u�W�F�N�g��
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(std::string _name);

	/**
	 * @brief		�R���X�g���N�^(�v���C�I���e�B�̏������錾)
	 * @param[in]	int �v���C�I���e�B
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(int _priority);

	/**
	 * @brief		�R���X�g���N�^(���O�ƃv���C�I���e�B�̏������錾)
	 * @param[in]	std::string �I�u�W�F�N�g��
	 * @param[in]	int	�v���C�I���e�B
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	HWGameObject(std::string _name, int _priority);

#pragma endregion


	/**
	 * @brief		�f�X�g���N�^
	 * @author		Suzuki N
	 * @date		24/07/21
	 */
	~HWGameObject();


#pragma region Getter���\�b�h�Q

	static std::vector<HWGameObject*> GetGameObjects(){ return gameObjects; }

#pragma endregion

	/**
	 * @brief		�R���|�[�l���g��ǉ�����
	 * @param[in]	std::unique_ptr<HWComponent> �A�^�b�`����R���|�[�l���g
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	template<class T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		//�e���v���[�g��Type��Component�̔h���N���X�����ׁA������ꍇ�̓R���p�C�����ɃG���[��f��
		static_assert(std::is_base_of<HWComponent, T>::value, "Error : Attempted to attach a non-component");


		std::unique_ptr<HWComponent> component = std::make_unique<T>(std::forward<Args>(args)...);

		// �R���|�[�l���g����A�^�b�`����Ă���GameObject��Transform���m�F�ł���悤�ɂ���
		component->gameObject = this;
		component->transform = (GetComponent<HWTransform>());
		hwComponents.push_back(std::move(component));

		T* ret = dynamic_cast<T*>(hwComponents[hwComponents.size() - 1].get());
		// �R���|�[�l���g���A�^�b�`���ꂽ�u�Ԃɑ��郁�\�b�h���Ăяo��
		ret->Awake();

		return ret;
	}

	/**
	 * @brief		�w��̃R���|�[�l���g��Ԃ�
	 * @return		�A�^�b�`����Ă����ꍇ�̓C���X�^���X��Ԃ��A����ȊO�Ȃ�nullPtr��Ԃ�
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	template<class T >
	T* GetComponent()
	{
		//�e���v���[�g��Type��Component�̔h���N���X�����ׁA������ꍇ�̓R���p�C�����ɃG���[��f��
		static_assert(std::is_base_of<HWComponent, T>::value, "Error : Trying to get something other than Component");

		//java��C#�ł����Ƃ����foreach�\��
		for (auto& component : hwComponents)
		{
			if (auto* targetComponent = dynamic_cast<T*>(component.get()))
				return targetComponent;
		}

		return nullptr;
	}
};