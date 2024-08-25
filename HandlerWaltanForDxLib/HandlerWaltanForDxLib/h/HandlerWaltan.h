#pragma once
#include "HWTransform.h"
#include "HWCollider.h"
#include "HWGameObject.h"
#include "CollisionWaltan.h"


/**
* @author   Suzuki N
* @date     24/07/18
* @note		�����A�n���h���[�͂��ׂ�HandlerWaltan�ŌĂяo��
*/


/**
 * @class		HandlerWaltan
 * @brief       ���ׂẴn���h���[���Ǘ��A���s����N���X
 */
class HandlerWaltan
{

private:

    /*     �����o�ϐ�     */

public:

    /**
     * @brief		�f�o�b�O���[�h�Ŏ��s���邩
     * @History		24/08/23 �쐬(Suzuki N)
     */
    static bool debugMode;


    /*     ���\�b�h     */

private:

    /**
     * @brief       �R���X�g���N�^
     * @author      Suzuki N
     * @date        24/07/19
     */
    HandlerWaltan();

    /**
     * @brief       �f�X�g���N�^
     * @author      Suzuki N
     * @date        24/07/19
     */
    ~HandlerWaltan();


public:

    /**
      * @brief       �S�Ă�Update���\�b�h��S�ČĂяo��
      * @author      Suzuki N
      * @date        24/08/22
      */
    void Update();

    /**
     * @brief       �C���X�^���X���擾����ÓI���\�b�h
     * @detail      ���߂̈�񂾂��C���X�^���X�𐶐�����
     * @author      Suzuki N
     * @date        24/07/19
     */
    static HandlerWaltan& Instance();


    //�C���X�^���X�̃R�s�[�֎~
    //�f�t�H���g�̃R�s�[�R���X�g���N�^���폜
    HandlerWaltan(const HandlerWaltan&) = delete;
    //�f�t�H���g�̃R�s�[������Z�q���폜
    HandlerWaltan& operator=(const HandlerWaltan&) = delete;


    /**
     * @brief       �C�j�V�����C�Y�p�̃��\�b�h
     * @detail      �C���X�^���X�𐶐������Ƃ��ɌĂ�
     * @return      int �����������̐���
     * @author      Suzuki N
     * @date        24/07/29
     */
    static int Init();

    /**
     * @brief       �I�����p�̃��\�b�h
     * @author      Suzuki N
     * @date        24/07/29
     */
    static void End();
};
