#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <chrono>
#include <thread>
#include <future>
#include <cstdio>
#include <cstdint>
#include "Syslog.h"


/**
* @author   Suzuki N
* @date     24/07/20
* @note		�ėp�I�ȃN���X�̒�`���܂Ƃ߂��w�b�_�[�t�@�C��
*/


/**
* @enum		InputState
* @brief	InputSystem�̓��̓p�����[�^
*/
enum class InputState
{
	//! ���͑҂�(0)
	Waiting,
	//! ���͂����u��(1)
	Started,
	//! ���͒�(2)
	Performed,
	//! ���͏I��(3)
	Canceled,
};

/**
* @struct	KeyInfo
* @brief	�L�[���
*/
struct KeyInfo
{
	//! �L�[�R�[�h
	int keyCode;
	//! ���͎���
	unsigned int inputTyme;
	//! �{�^�����͂̃p�����[�^
	InputState inputState;
};


/**
 * @class		PoolAllocator
 * @brief		�������Ǘ������������邽�߂̃������A���P�[�^�[
 */
template<class T, size_t MAXSIZE>
class PoolAllocator
{
public:

	/*     �����o�ϐ�     */

	union Block
	{
		char pool[sizeof(T)];
		Block* nextBlock;
	};

	/**
	 * @brief		�������v�[��
	 * @History		24/09/01 �쐬(Suzuki N)
	 */
	Block block[MAXSIZE];

	/**
	 * @brief		�󂫃������u���b�N�̐퓬
	 * @History		24/09/01 �쐬(Suzuki N)
	 */
	Block* freeBlockHead;


public:

	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/01
	 */
	PoolAllocator()
	{
		// �������u���b�N���m��A������
		for (size_t i = 0; i < MAXSIZE - 1; ++i)
			block[i]->nextBlock = &block[i + 1];
		// ������ nullptr
		block[MAXSIZE - 1].nextBlock = nullptr;

		// �󂫃������̐擪�̏����l�� block �̐擪
		freeBlockHead = block;
	}

	/**
	 * @brief		�f�X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/01
	 */
	~PoolAllocator(){}

	/**
	 * @brief		���������m�ۂ���
	 * @return		�m�ۂ���������
	 * @author		Suzuki N
	 * @date		24/09/01
	 */
	T* Alloc()
	{
		// �󂫃������u���b�N���Ȃ��ꍇ�Anullptr ��Ԃ�
		if (freeBlockHead == nullptr)
			return nullptr;

		//! �m�ۂ���������
		T* ret = reinterpret_cast<T*>(freeBlockHead);
		// �󂫃������u���b�N���X�V
		freeBlockHead = freeBlockHead->nextBlock;

		// ���I�ɃR���X�g���N�^���Ă�
		return new(ret) T();
	}

	/**
	 * @brief		���������������
	 * @param[in]	T* Alloc�Ŋm�ۂ���������
	 * @author		Suzuki N
	 * @date		24/09/01
	 */
	void Free(T* _addr)
	{
		if (_addr == nullptr)
			return;

		// �����I�Ƀf�X�g���N�^���Ă�
		_addr->~T();

		//! �������A�h���X
		Block* freeBlock = reinterpret_cast<Block*>(_addr);

		// ��������u���b�N�̌���freeBlockHead���Ȃ���
		freeBlockHead->nextBlock = freeBlock;
		// �󂫃������u���b�N���X�V
		freeBlockHead = freeBlock;	
	}
};


/**
 * @class		InputSystem
 * @brief		���͂̌��m�A���͎��ɃR�[���o�b�N�֐����ĂԃN���X
 */
class InputSystem
{
private:

	/*     �����o�ϐ�     */

	/**
	 * @brief		�A�N�e�B�u
	 * @History		24/09/07 �쐬(Suzuki N)
	 */
	bool active;

	/**
	 * @brief		�L�[�}�b�v
	 * @History		24/09/07 �쐬(Suzuki N)
	 */
	std::map<std::string, std::vector<std::atomic<KeyInfo>>> keyMap;

	/**
	 * @brief		�L�[�`�F�b�N��ʃX���b�h�ŉ�
	 * @History		24/09/07 �쐬(Suzuki N)
	 */
	std::thread keyCheck;


public:

	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	InputSystem() : active(true)
	{
	}

	/**
	 * @brief		�X�e�[�W�ɃL�[��o�^����
	 * @detail		{} �ŕ������͉\
	 * @param[in]	std::string	�o�^����L�[	
	 * @param[in]	int			�L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyMap(std::string _key, int _inputKey)
	{
		//! �o�^����L�[���̏������錾
		KeyInfo keyInfo =
		{
			_inputKey,
			0,
			InputState::Waiting,
		};

		// �L�[�����ɑ��݂��Ă���ꍇ�͗v�f��ǉ�����

	}

	/**
	 * @brief		�X�e�[�W�ɃL�[��o�^����
	 * @detail		{} �ŕ������͉\
	 * @param[in]	std::string		 �o�^����L�[
	 * @param[in]	std::vector<int> �L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyMap(std::string _key, std::vector<int> _inputKey)
	{
		for (int i = 0; i < _inputKey.size(); ++i)
		{
			//! �o�^����L�[���̏������錾
			KeyInfo keyInfo =
			{
				_inputKey[i],
				0,
				InputState::Waiting,
			};

			// �L�[�����ɑ��݂��Ă���ꍇ�͗v�f��ǉ�����
//			auto it = keyMap.find(_key);
//			if (it != keyMap.end())
//				it->second.push_back(keyInfo);
//			else
//				keyMap[_key].push_back(keyInfo);
		}
	}

	/**
	 * @brief		�L�[�}�b�v�ɓo�^����Ă���L�[���Ď�����
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void KeyCheckAsync()
	{
	}
};
