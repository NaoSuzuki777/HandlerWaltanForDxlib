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
        //! OBB�̊e��(���K�����ꂽ)
        VECTOR axis[3];     
        //! �e�������̃n�[�t�T�C�Y
        VECTOR extent;
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
      * @brief       OBB���m�̂����蔻��
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CheckOBBIntersection(const OBB& _obb1, const OBB& _obb2)
    {
        // �eOBB�̎�
        const VECTOR& a0 = _obb1.axis[0];
        const VECTOR& a1 = _obb1.axis[1];
        const VECTOR& a2 = _obb1.axis[2];

        const VECTOR& b0 = _obb2.axis[0];
        const VECTOR& b1 = _obb2.axis[1];
        const VECTOR& b2 = _obb2.axis[2];

        //! obb1 �� obb2 �Ԃ̋����x�N�g��
        VECTOR dir = VSub(_obb2.center, _obb1.center);

        // �e���œ��e���ĕ��������`�F�b�N���邽�߂̃T�|�[�g�ϐ�
        float c[3][3];
        float AbsC[3][3];
        float rA, rB;

        // �e���ɑ΂��铊�e���v�Z
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                c[i][j] = VDot(_obb1.axis[i], _obb2.axis[j]);
                AbsC[i][j] = fabs(c[i][j]) + FLT_EPSILON;  // ���������_�G���[�΍�
            }

        // obb1 �̎�����ɂ��ĕ��������e�X�g
        rA = _obb1.extent.x;
        rB = _obb2.extent.x * AbsC[0][1] + _obb2.extent.y * 
            AbsC[0][1] + _obb2.extent.z * AbsC[0][2];
        // obb1 �� obb2 �Ԃ̋����� rA + rB (�Q��OBB�̔����̓��e����)
        // �����傫�������炱�̎��ł͐ڐG���Ă��Ȃ�
        if (fabs(VDot(a0, dir)) > rA + rB)
            return false;

        rA = _obb1.extent.y;
        rB = _obb2.extent.x * AbsC[1][0] + _obb2.extent.y * 
            AbsC[1][1] + _obb2.extent.z * AbsC[1][2];
        // obb1 �� obb2 �Ԃ̋����� rA + rB (�Q��OBB�̔����̓��e����)
        // �����傫�������炱�̎��ł͐ڐG���Ă��Ȃ�
        if (fabs(VDot(a1, dir)) > rA + rB)
            return false;

        rA = _obb1.extent.z;
        rB = _obb2.extent.x * AbsC[2][0] + _obb2.extent.y * 
            AbsC[2][1] + _obb2.extent.z * AbsC[2][2];
        // obb1 �� obb2 �Ԃ̋����� rA + rB (�Q��OBB�̔����̓��e����)
        // �����傫�������炱�̎��ł͐ڐG���Ă��Ȃ�
        if (fabs(VDot(a2, dir)) > rA + rB)
            return false;

        // obb2 �̎�����ɂ��ĕ��������e�X�g
        rB = _obb1.extent.x * AbsC[0][1] + _obb1.extent.y * 
            AbsC[0][1] + _obb1.extent.z * AbsC[0][2];
        rA = _obb2.extent.x;
        // obb1 �� obb2 �Ԃ̋����� rA + rB (�Q��OBB�̔����̓��e����)
        // �����傫�������炱�̎��ł͐ڐG���Ă��Ȃ�
        if (fabs(VDot(a0, dir)) > rA + rB)
            return false;

        rB = _obb1.extent.x * AbsC[1][0] + _obb1.extent.y * 
            AbsC[1][1] + _obb1.extent.z * AbsC[1][2];
        rA = _obb2.extent.y;
        // obb1 �� obb2 �Ԃ̋����� rA + rB (�Q��OBB�̔����̓��e����)
        // �����傫�������炱�̎��ł͐ڐG���Ă��Ȃ�
        if (fabs(VDot(a1, dir)) > rA + rB)
            return false;

        rB = _obb1.extent.x * AbsC[2][0] + _obb1.extent.y * 
            AbsC[2][1] + _obb1.extent.z * AbsC[2][2];
        rA = _obb2.extent.z;
        // obb1 �� obb2 �Ԃ̋����� rA + rB (�Q��OBB�̔����̓��e����)
        // �����傫�������炱�̎��ł͐ڐG���Ă��Ȃ�
        if (fabs(VDot(a2, dir)) > rA + rB)
            return false;

        // �ǂ̎����猩�Ă��ڐG���Ă���
        return true;
    }
};

