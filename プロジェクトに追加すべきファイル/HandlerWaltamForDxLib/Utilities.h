#pragma once
#include <iostream>
#include <fstream>
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
 * @class	ReadOnly
 * @brief	�ǂݎ���p�ɂ��郉�b�p�[�N���X	
 */
template<class T>
class ReadOnly
{
private:

	/*     �����o�ϐ�     */

	/**
	 * @brief		�l��ۊǂ���I�u�W�F�N�g
	 * @History		24/09/14 �쐬(Suzuki N)
	 */
	T obj;


public:

	/*     ���\�b�h     */

	/**
	 * @brief		�R���X�g���N�^
	 * @param[in]	T �����l
	 * @author		Suzuki N
	 * @date		24/09/14
	 */
	ReadOnly(T _obj) : obj(_obj) {}

	/**
	 * @brief		�֐��Ăяo��operator�̒�`
	 * @param[in]	T �����l
	 * @author		Suzuki N
	 * @date		24/09/14
	 */
	operator T() const { return obj; }

	// �l�̕ύX���֎~���邽�߁A���operator�͍폜
	ReadOnly& operator=(const T&) = delete;
};


/**
 * @class	PoolAllocator
 * @brief	�������Ǘ������������邽�߂̃������A���P�[�^�[
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


/**
 * @class	CsvLoader
 * @brief	csv�t�@�C�����J���}��؂�œǂݍ���
 * @detail	�ÓI�N���X
 */
class CsvLoader final
{
private:

	/*     �����o�ϐ�     */


public:

	/*     ���\�b�h     */

	// �ÓI�N���X�̂��߁A�R���X�g���N�^�ƃf�X�g���N�^���폜
	CsvLoader() = delete;
	~CsvLoader() = delete;


	/**
	 * @brief		csv�t�@�C����ǂݍ��݁A�s��؂�A�J���}��؂�ŕ������Ԃ�
	 * @param[in]	std::string	�ǂݍ���csv�t�@�C���̃p�X
	 * @return		std::vector<std::vector<std::string>> �ǂݍ��񂾕������Ԃ�(1���� = �s, 2���� = �J���}��؂�)
	 * @author		Suzuki N
	 * @date		24/09/14
	 */
	static std::vector<std::vector<std::string>> Load(const std::string _filePath)
	{
		//! �߂�l
		std::vector<std::vector<std::string>> ret;

		// �t�@�C����ǂݍ���
		std::ifstream file(_filePath);
		// �t�@�C���ǂݍ��݂Ɏ��s�����ꍇ�A���̂܂܏I��
		if (!file)
			return ret;

		//! �s��؂�œǂݍ��񂾕�����
		std::string line;

		// 1�s���ǂݍ���
		while (std::getline(file, line))
		{
			//! �J���}��؂�œǂݍ��񂾕�����
			std::vector<std::string> comma;
			//! �m�F�ς݂̕������index
			size_t confirmed = 0;
			//! �J���}��������index
			size_t commaPos = 0;
			
			// �J���}��؂�œǂݍ���
			do
			{
				// �O��J���}��������index����J���}��������
				commaPos = line.find_first_of(',', confirmed);
				// �J���}��������Ȃ������ꍇ�͂��̂܂܏I��
				if (commaPos == std::string::npos)
				{
					// �O��̃R���}�̈ʒu����R�s�[
					comma.push_back(line.substr(confirmed));
					break;
				}

				// �O��̃R���}�̈ʒu���玟�̃R���}�̈ʒu�܂ł̕�������R�s�[
				comma.push_back(line.substr(confirmed, commaPos - confirmed));

				// �m�F�ς݂̕�������X�V
				confirmed = commaPos + 1;
			} while (commaPos != std::string::npos);

			// �J���}���Ȃ��Ȃ����猋�ʂ�ǉ�
			ret.push_back(comma);
		}

		return ret;
	}
};


//--------------------------------------------------------
// �֐�
//--------------------------------------------------------

/**
 * @brief		�x���@ -> �ʓx�@ �ɕϊ�
 * @param[in]	double �p�x
 * @return		double �ϊ��������W�A���l
 * @author		Suzuki N
 * @date		24/09/23
 */
inline double Deg2Rad(const double _angle)
{
	return _angle * DX_PI / 180.f;
}

/**
 * @brief		�ʓx�@ -> �x���@ �ɕϊ�
 * @param[in]	double ���W�A���l
 * @return		double �ϊ������p�x
 * @author		Suzuki N
 * @date		24/09/23
 */
inline double Rad2Deg(const double _radian)
{
	return _radian * 180 / DX_PI;
}