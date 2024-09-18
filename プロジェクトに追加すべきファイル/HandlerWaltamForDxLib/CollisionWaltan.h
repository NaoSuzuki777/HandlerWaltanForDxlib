#pragma once
#include "Utilities.h"
#include "HandlerWaltan.h"
#include "HWBoxCollider.h"
#include "HWSphereCollider.h"
#include "HWCapsuleCollider.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		ColliderWaltan�̒�`�t�@�C��
*/


/**
 * @class	ColliderWaltan
 * @brief   ��F�R���C�_�[�R���|�[�l���g�̂����蔻����Ď����A�����ɉ������n���h���[���Ăяo��
 */
class CollisionWaltan
{
	// ����̃N���X�ȊO����̃A�N�Z�X��h�����߂̃t�����h�錾
	friend class HandlerWaltan;
    friend class HWBoxCollider;
    friend class HWSphereCollider;
    friend class HWCapsuleCollider;


private:

    /*     �����o�ϐ�     */

    /**
     * @brief		�C���X�^���X������Ă���R���C�_�[
     * @History		24/09/17 �쐬(Suzuki N)
     */
    std::vector<HWCollider*> ColVec;


private:

    /*     ���\�b�h     */

    /**
     * @brief       �C���X�^���X���擾����ÓI���\�b�h
     * @detail      ���߂̈�񂾂��C���X�^���X�𐶐�����
     * @return      CollisionWaltan& �V���O���g���C���X�^���X
     * @author      Suzuki N
     * @date        24/07/19
     */
    static CollisionWaltan& Instance()
    {
        // �V���O���g���C���X�^���X�𐶐�
        static CollisionWaltan instance;
        return instance;
    }

    //�C���X�^���X�̃R�s�[�֎~
    //�f�t�H���g�̃R�s�[�R���X�g���N�^���폜
    CollisionWaltan(const CollisionWaltan&) = delete;
    //�f�t�H���g�̃R�s�[������Z�q���폜
    CollisionWaltan& operator=(const CollisionWaltan&) = delete;

    /**
     * @brief       �R���X�g���N�^
     * @author      Suzuki N
     * @date        24/07/19
     */
    CollisionWaltan();

    /**
     * @brief       �f�X�g���N�^
     * @author      Suzuki N
     * @date        24/07/19
     */
    ~CollisionWaltan();

    /**
      * @brief       �e�R���|�[�l���g��Update���\�b�h��S�ČĂяo��
      * @author      Suzuki N
      * @date        24/08/22
      */
    void Update();

    /**
     * @brief       �o�^����Ă���R���C�_�[�����폜����
     * @param[in]   HWCollider* �폜����R���C�_�[���
     * @author      Suzuki N
     * @date        24/09/17
     */
    void UnRegister(HWCollider* _collider);

    /**
      * @brief       �v�f1 ��BoxCollider�̏ꍇ�̃R���W�����`�F�b�N
      * @param[in]   HWBoxCollider* �����蔻��̏d�Ȃ�����闧���̌^Collider���1
      * @param[in]   HWCollider*    �����蔻��̏d�Ȃ������Collider���2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Box(HWBoxCollider* _boxCol1, HWCollider* _col2);

    /**
      * @brief       �v�f1 ��SphereCollider�̏ꍇ�̃R���W�����`�F�b�N
      * @param[in]   HWSphereCollider*   �����蔻��̏d�Ȃ�����鋅�̌^Collider���1
      * @param[in]   HWCollider*         �����蔻��̏d�Ȃ������Collider���2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Sphere(HWSphereCollider* _col1, HWCollider* _col2);

    /**
      * @brief       �v�f1 ��CapsuleCollider�̏ꍇ�̃R���W�����`�F�b�N
      * @param[in]   HWCapsuleCollider*  �����蔻��̏d�Ȃ������J�v�Z���^Collider���1
      * @param[in]   HWCollider*         �����蔻��̏d�Ȃ������Collider���2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Capsule(HWCapsuleCollider* _col1, HWCollider* _col2);

    /**
      * @brief       Box�R���C�_�[���߂荞�܂Ȃ��悤�ɂ��鏈��
      * @author      Suzuki N
      * @date        24/09/17
      */

};

