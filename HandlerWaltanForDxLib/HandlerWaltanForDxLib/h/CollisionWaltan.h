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

    // �R���W�����`�F�b�N�Ɏg���\����

    /**
    * @struct	OBB
    * @brief	�����̂̓����蔻��
    */
    struct OBB {
        //! OBB�̒��S���W
        VECTOR center;      
        //! �e���x�N�g���i���K���ς݁j
        VECTOR axis[3];     
        //! �e�������̃n�[�t�T�C�Y
        float halfSize[3];  
    };

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
      * @brief       �������ɑ΂��� OBB �̃v���W�F�N�V�����T�C�Y���v�Z���邽�߂̃w���p�[�֐�
      * @author      Suzuki N
      * @date        24/09/17
      */
    float ProjectOntoAxis(const OBB& obb, const VECTOR& axis)
    {
        // OBB �̊e���̃X�P�[���ƁA�w�肵���������Ƃ̃h�b�g�ς��g�p���ē��e�̑傫�������߂�
        return obb.halfSize[0] * fabs(VDot(obb.axis[0], axis)) +
            obb.halfSize[1] * fabs(VDot(obb.axis[1], axis)) +
            obb.halfSize[2] * fabs(VDot(obb.axis[2], axis));
    }

    bool CheckOverlapOnAxis(const OBB& obb1, const OBB& obb2, const VECTOR& axis) {
        // �����[���x�N�g���Ȃ疳������
        if (VSize(axis) < 1e-6) return true;

        // ������ OBB �����̎��ɓ��e
        float projection1 = ProjectOntoAxis(obb1, axis);
        float projection2 = ProjectOntoAxis(obb2, axis);

        // 2��OBB�̒��S�Ԃ̃x�N�g�������̎��ɓ��e
        float distance = fabs(VDot(VSub(obb2.center, obb1.center), axis));

        // �����������̓��e�̍��v���傫���ꍇ�́A��������Ă���
        return distance <= (projection1 + projection2);
    }

    bool OBBvsOBB(const OBB& obb1, const OBB& obb2) {
        VECTOR axis;

        // obb1 �̎�
        for (int i = 0; i < 3; ++i) {
            if (!CheckOverlapOnAxis(obb1, obb2, obb1.axis[i])) return false;
        }

        // obb2 �̎�
        for (int i = 0; i < 3; ++i) {
            if (!CheckOverlapOnAxis(obb1, obb2, obb2.axis[i])) return false;
        }

        // �� OBB �̎��Ԃ̊O�ςŒ�`����鎲
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                axis = VCross(obb1.axis[i], obb2.axis[j]);
                if (!CheckOverlapOnAxis(obb1, obb2, axis)) return false;
            }
        }

        // �S�Ă̎��ŕ�����������Ȃ���΁A�Փ˂��Ă���
        return true;
    }
};

