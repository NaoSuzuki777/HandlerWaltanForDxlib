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
#include "DxLib.h"


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
 * @class		MapInfo
 * @brief		�L�[�}�b�v�̏��
 */
class MapInfo
{
	friend class InputSystem;

private:
	/*     �����o�ϐ�     */

	/**
	 * @brief		�L�[���
	 * @History		24/09/10 �쐬(Suzuki N)
	 */
	std::vector<KeyInfo> keyInfoVec;

	/**
	 * @brief		�o�^���ꂽ�R�[���o�b�N�֐�
	 * @History		24/09/10 �쐬(Suzuki N)
	 */
	std::vector<std::function<void(MapInfo&)>> callBacks;

	/**
	 * @brief		KeyMap�̃p�����[�^�[
	 * @History		24/09/10 �쐬(Suzuki N)
	 */
	InputState inputState;


private:
	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	MapInfo() : inputState(InputState::Waiting)
	{
	}

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	MapInfo(const int _keyCode) : inputState(InputState::Waiting)
	{
		AddKeyCode(_keyCode);
	}

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	MapInfo(const std::vector<int> _keyCodeVec) : inputState(InputState::Waiting)
	{
		AddKeyCode(_keyCodeVec);
	}

public:

	/**
	 * @brief		�L�[�}�b�v�̃X�e�[�^�X��Ԃ�
	 * return		InputStatus	�L�[�}�b�v�̃X�e�[�^�X
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	InputState GetInputState() { return inputState; }

	/**
	 * @brief		�L�[����Ԃ�
	 * return		std::vector<KeyInfo>	�o�^���ꂽ�L�[���
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	std::vector<KeyInfo> GetKeyInfoVec() { return keyInfoVec; }

private:

	/**
	 * @brief		�L�[����Ԃ�
	 * return		std::vector<KeyInfo>	�o�^���ꂽ�L�[���
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	std::vector<KeyInfo>& GetKeyInfoRef() { return keyInfoVec; }

	/**
	 * @brief		�L�[�}�b�v�̃X�e�[�^�X��ύX����
	 * param[in]	InputStatus	�L�[�}�b�v�̃X�e�[�^�X
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void SetInputState(InputState _state) { inputState = _state; }

	/**
	 * @brief		�o�^���ꂽ�R�[���o�b�N�֐������ׂČĂяo��
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void CallCallbacks()
	{
		for (auto it = callBacks.begin(); it != callBacks.end(); ++it)
			(*it)(*this);
	}

	/**
	 * @brief		�L�[�R�[�h��ǉ�����
	 * @detail		{} �ŕ����I���\
	 * @param[in]	int �ǉ�����L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void AddKeyCode(const int _keyCode)
	{
		//! �o�^����L�[���̏������錾
		KeyInfo keyInfo =
		{
			_keyCode,
			0,
			InputState::Waiting,
		};

		// �L�[����o�^
		keyInfoVec.push_back(keyInfo);
	}

	/**
	 * @brief		�L�[�R�[�h��ǉ�����
	 * @detail		{} �ŕ����I���\
	 * @param[in]	std::vector<int> �ǉ�����L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void AddKeyCode(const std::vector<int> _keyCodeVec)
	{
		for (auto it = _keyCodeVec.begin(); it != _keyCodeVec.end(); ++it)
		{
			//! �o�^����L�[���̏������錾
			KeyInfo keyInfo =
			{
				*it,
				0,
				InputState::Waiting,
			};

			// �L�[����o�^
			keyInfoVec.push_back(keyInfo);
		}
	}

	/**
	 * @brief		�R�[���o�b�N�֐���ǉ�����
	 * @param[in]	std::function<void(std::vector<KeyInfo>)> �ǉ�����R�[���o�b�N�֐�
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void AddCallBack(const std::function<void(MapInfo&)> _callBack)
	{
		callBacks.push_back(_callBack);
	}
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
	~PoolAllocator() {}

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


// �O���錾
class HandlerWaltan;

/**
 * @class		InputSystem
 * @brief		���͂̌��m�A���͎��ɃR�[���o�b�N�֐����ĂԃN���X
 */
class InputSystem
{
private:

	friend class HandlerWaltan;

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
	std::map<std::string, MapInfo*> keyMap;

	/**
	 * @brief		�������ꂽInputSystem�̃C���X�^���X
	 * @History		24/09/10 �쐬(Suzuki N)
	 */
	static std::vector<InputSystem*> inputSystemVec;


public:

	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	InputSystem() : active(true)
	{
		inputSystemVec.push_back(this);
	}

	/**
	 * @brief		Active��ύX����
	 * @param[in]	bool �ύX���bool�l
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void SetActive(bool _active) { active = _active; }

	/**
	 * @brief		�}�b�v�ɃL�[��o�^����
	 * @detail		{} �ŕ������͉\
	 * @param[in]	std::string	�o�^����L�[
	 * @param[in]	int			�L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyCode(const std::string _key, int _inputKey)
	{
		// �L�[�����ɑ��݂��Ă���ꍇ�͗v�f��ǉ�����
		auto it = keyMap.find(_key);
		// ���݂��Ă����ꍇ
		if (it != keyMap.end())
			it->second->AddKeyCode(_inputKey);
		// ���݂��Ă��Ȃ������ꍇ�́A�V���ɃC���X�^���X���쐬����
		else
			keyMap[_key] = new MapInfo(_inputKey);
	}

	/**
	 * @brief		�}�b�v�ɃL�[��o�^����
	 * @detail		{} �ŕ������͉\
	 * @param[in]	std::string		 �o�^����L�[
	 * @param[in]	std::vector<int> �L�[�R�[�h
	 * @author		Suzuki N
	 * @date		24/09/07
	 */
	void AddKeyCode(const std::string _key, std::vector<int> _inputKey)
	{
		// �L�[�����ɑ��݂��Ă���ꍇ�͗v�f��ǉ�����
		auto it = keyMap.find(_key);
		// ���݂��Ă����ꍇ
		if (it != keyMap.end())
			it->second->AddKeyCode(_inputKey);
		// ���݂��Ă��Ȃ������ꍇ�́A�V���ɃC���X�^���X���쐬����
		else
			keyMap[_key] = new MapInfo(_inputKey);
	}

	/**
	 * @brief		�L�[�}�b�v�ɓo�^����Ă���L�[���Ď�����
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void AddCallBack(const std::string _key, std::function<void(MapInfo&)> _callBack)
	{
		// �L�[�����ɑ��݂��Ă���ꍇ�͗v�f��ǉ�����
		auto it = keyMap.find(_key);
		// ���݂��Ă����ꍇ
		if (it != keyMap.end())
			it->second->AddCallBack(_callBack);
		// ���݂��Ă��Ȃ������ꍇ�́A�V���ɃC���X�^���X���쐬����
		else
		{
			keyMap[_key] = new MapInfo();
			keyMap[_key]->AddCallBack(_callBack);
		}
	}

private:

	/**
	 * @brief		�L�[�}�b�v�ɓo�^����Ă���L�[���Ď�����
	 * @author		Suzuki N
	 * @date		24/09/08
	 */
	void KeyCheck()
	{
		// �o�^����Ă���L�[�̓��͏�Ԃ��Ď�
		for (auto it = keyMap.begin(); it != keyMap.end(); ++it)
		{
			//! ���̃L�[�}�b�v���œ��͂���������
			bool isInput = false;

			for (auto it2 = it->second->GetKeyInfoRef().begin(); it2 != it->second->GetKeyInfoRef().end(); ++it2)
			{
				//! �o�^���ꂽ�L�[�̏��
				KeyInfo& keyInfo = *it2;

				// �o�^���ꂽ�L�[�̓��͏�Ԃ��m�F
				if (CheckHitKey(keyInfo.keyCode))
				{
					// ���͂�������
					isInput = true;

					// �L�[�̓��͏�ԂŃp�����[�^�[��ς���
					switch (keyInfo.inputState)
					{
					case InputState::Waiting:
						keyInfo.inputState = InputState::Started;
						// ���s���Ԃ�ۊ�
						keyInfo.inputTyme = GetNowCount();
						break;

					case InputState::Started:
						// ���͒��Ƀp�����[�^�[��ύX
						keyInfo.inputState = InputState::Performed;
						break;

					case InputState::Performed:
						// ������Ԃ̌p���Ȃ��߁A�p�����[�^�[�̕ύX�͂Ȃ�
						break;

					case InputState::Canceled:
						keyInfo.inputState = InputState::Started;
						// ���s���Ԃ�ۊ�
						keyInfo.inputTyme = GetNowCount();
						break;
					}
				}
				// ���͂��Ȃ�����
				else
				{
					// �L�[�̓��͏�ԂŃp�����[�^�[��ς���
					switch (keyInfo.inputState)
					{
					case InputState::Waiting:
						// �ҋ@��Ԃ��p�����Ă��邽�߁A�ύX�Ȃ�
						break;

					case InputState::Started:
						// ���͏I���̃p�����[�^�[�ɕύX
						keyInfo.inputState = InputState::Canceled;
						break;

					case InputState::Performed:
						// ���͏I���̃p�����[�^�[�ɕύX
						keyInfo.inputState = InputState::Canceled;
						break;

					case InputState::Canceled:
						// ���͑ҋ@�̃p�����[�^�[�ɕύX
						keyInfo.inputState = InputState::Waiting;
						break;
					}
				}
			}

			// ���͂��������ꍇ
			if (isInput)
			{
				// �L�[�}�b�v��InputStatus��ύX����
				switch (it->second->GetInputState())
				{
				case InputState::Waiting:
					it->second->SetInputState(InputState::Started);
					break;
				case InputState::Started:
					it->second->SetInputState(InputState::Performed);
					break;
				case InputState::Performed:
					// ���͏�Ԃ��p���Ȃ��߁A�X�e�[�^�X�̕ύX�Ȃ�
					break;
				case InputState::Canceled:
					it->second->SetInputState(InputState::Started);
					break;
				}
				// �o�^���ꂽ�R�[���o�b�N�֐������ׂČĂяo��
				it->second->CallCallbacks();
			}
			// ���͂��Ȃ������ꍇ
			else
			{
				// �L�[�}�b�v��InputStatus��ύX����
				switch (it->second->GetInputState())
				{
				case InputState::Waiting:
					// ���͏�Ԃ��p���Ȃ��߁A�X�e�[�^�X�̕ύX�Ȃ�
					break;
				case InputState::Started:
					it->second->SetInputState(InputState::Canceled);
					// �o�^���ꂽ�R�[���o�b�N�֐������ׂČĂяo��
					it->second->CallCallbacks();
					break;
				case InputState::Performed:
					it->second->SetInputState(InputState::Canceled);
					// �o�^���ꂽ�R�[���o�b�N�֐������ׂČĂяo��
					it->second->CallCallbacks();
					break;
				case InputState::Canceled:
					it->second->SetInputState(InputState::Waiting);
					break;
				}
			}
		}
	}

	/**
	 * @brief		��F�Ă΂�郁�\�b�h
	 * @author		Suzuki N
	 * @date		24/09/10
	 */
	void Update()
	{
		KeyCheck();
	}
};