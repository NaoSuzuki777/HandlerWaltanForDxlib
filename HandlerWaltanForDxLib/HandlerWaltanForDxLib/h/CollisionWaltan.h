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
        VECTOR c;      
        //! OBB�̊e��(���K�����ꂽ)
        VECTOR u[3];     
        //! �e�������̃n�[�t�T�C�Y
        VECTOR e;
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

    void ColliderHitCallBacks(HWCollider* _col1, HWCollider* _col2, bool _isTrigger);

    /**
      * @brief       OBB���m�̓����蔻��
      * @author      Suzuki N
      * @date        24/09/24
      */
    int TestOBBOBB(OBB* a, OBB* b)
    {
        const float EPSILON = 1.175494e-37;

        float R[3][3], AbsR[3][3];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                R[i][j] = VDot(a->u[i], b->u[j]);
                AbsR[i][j] = fabsf(R[i][j]) + EPSILON;
            }
        }

        VECTOR t = VSub(b->c, a->c);
        t = VGet(VDot(t, a->u[0]), VDot(t, a->u[1]), VDot(t, a->u[2]));

        //��L=A0, L=A1, L=A2����
        float ra, rb;

            ra = a->e.x;
            rb = b->e.x * AbsR[0][0] + b->e.y * AbsR[0][1] + b->e.z * AbsR[0][2];
            if (fabsf(t.x) > ra + rb)return 0;

            ra = a->e.y;
            rb = b->e.x * AbsR[1][0] + b->e.y * AbsR[1][1] + b->e.z * AbsR[1][2];
            if (fabsf(t.y) > ra + rb)return 0;
            
            ra = a->e.z;
            rb = b->e.x * AbsR[2][0] + b->e.y * AbsR[2][1] + b->e.z * AbsR[2][2];
            if (fabsf(t.z) > ra + rb)return 0;

        //��L=B0, L=B1, L=B2����
            ra = a->e.x * AbsR[0][0] + a->e.y * AbsR[1][0] + a->e.z * AbsR[2][0];
            rb = b->e.x;
            if (fabsf(t.x * R[0][0] + t.y * R[1][0] + t.z * R[2][0]) > ra + rb)return 0;

            ra = a->e.x * AbsR[0][1] + a->e.y * AbsR[1][1] + a->e.z * AbsR[2][1];
            rb = b->e.y;
            if (fabsf(t.x * R[0][1] + t.y * R[1][1] + t.z * R[2][1]) > ra + rb)return 0;
            
            ra = a->e.x * AbsR[0][2] + a->e.y * AbsR[1][2] + a->e.z * AbsR[2][2];
            rb = b->e.y;
            if (fabsf(t.x * R[0][2] + t.y * R[1][2] + t.z * R[2][2]) > ra + rb)return 0;
        



        //��L=A0 X B0����
        ra = a->e.y * AbsR[2][0] + a->e.z * AbsR[1][0];
        rb = b->e.y * AbsR[0][2] + b->e.z * AbsR[0][1];
        if (fabsf(t.z * R[1][0] - t.y * R[2][0]) > ra + rb)return 0;

        //��L=A0 X B1����
        ra = a->e.y * AbsR[2][1] + a->e.z * AbsR[1][1];
        rb = b->e.x * AbsR[0][2] + b->e.z * AbsR[0][0];
        if (fabsf(t.z * R[1][1] - t.y * R[2][1]) > ra + rb)return 0;

        //��L=A0 X B2����
        ra = a->e.y * AbsR[2][2] + a->e.z * AbsR[1][2];
        rb = b->e.x * AbsR[0][1] + b->e.y * AbsR[0][0];
        if (fabsf(t.z * R[1][2] - t.y * R[2][2]) > ra + rb)return 0;

        //��L=A1 X B0����
        ra = a->e.x * AbsR[2][0] + a->e.z * AbsR[0][0];
        rb = b->e.y * AbsR[1][2] + b->e.z * AbsR[1][1];
        if (fabsf(t.x * R[2][0] - t.z * R[0][0]) > ra + rb)return 0;

        //��L=A1 X B1����
        ra = a->e.z * AbsR[2][1] + a->e.z * AbsR[0][1];
        rb = b->e.z * AbsR[1][2] + b->e.z * AbsR[1][0];
        if (fabsf(t.x * R[2][1] - t.z * R[0][1]) > ra + rb)return 0;

        //��L=A1 X B2����
        ra = a->e.x * AbsR[2][2] + a->e.z * AbsR[0][2];
        rb = b->e.x * AbsR[1][1] + b->e.y * AbsR[1][0];
        if (fabsf(t.x * R[2][2] - t.z * R[0][2]) > ra + rb)return 0;

        //��L=A2 X B0����
        ra = a->e.x * AbsR[1][0] + a->e.y * AbsR[0][0];
        rb = b->e.y * AbsR[2][2] + b->e.z * AbsR[2][1];
        if (fabsf(t.y * R[0][0] - t.x * R[1][0]) > ra + rb)return 0;

        //��L=A2 X B1����
        ra = a->e.x * AbsR[1][1] + a->e.y * AbsR[0][1];
        rb = b->e.x * AbsR[2][2] + b->e.z * AbsR[2][0];
        if (fabsf(t.y * R[0][1] - t.y * R[1][1]) > ra + rb)return 0;

        //��L=A2 X B2����
        ra = a->e.x * AbsR[1][2] + a->e.y * AbsR[0][2];
        rb = b->e.x * AbsR[2][1] + b->e.y * AbsR[2][0];
        if (fabsf(t.y * R[0][2] - t.x * R[1][2]) > ra + rb)return 0;

        return 1;
    }
};

