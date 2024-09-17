#include "h/CollisionWaltan.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		ColliderWaltan�̎����t�@�C��
*/


#pragma region publuc���\�b�h



#pragma endregion

#pragma region private���\�b�h


CollisionWaltan::CollisionWaltan()
{

}


CollisionWaltan::~CollisionWaltan()
{

}

void CollisionWaltan::Update()
{
	// �����蔻����`�F�b�N����
	// �`�F�b�N�̏d�����Ȃ������߁A�Ō�̗v�f����-1�����v�f�܂łɂ���
	for (auto it1 = ColVec.begin(); it1 != ColVec.end() - 1; ++it1)
	{
		// ���łɃ`�F�b�N�����g�ݍ��킹���Ȃ�
		for (auto it2 = it1 + 1; it2 != ColVec.end(); ++it2)
		{
			// it1 �̃R���C�_�[�^�C�v�ɂ���ď�����ς���
			switch ((*it1)->GetColliderType())
			{
				// �����̌^�R���C�_�[�̏ꍇ
			case ColliderType::Box:
				if (CollCheck_Box(dynamic_cast<HWBoxCollider*>(*it1), *it2))
					(*it1)->gameObject->CallAllOnCollisionEnters(*it2);
					(*it2)->gameObject->CallAllOnCollisionEnters(*it1);
				break;
				// �J�v�Z���^�R���C�_�[�̏ꍇ
			case ColliderType::Capsule:
				CollCheck_Capsule(dynamic_cast<HWCapsuleCollider*>(*it1), *it2);
				break;
				// ���̌^�R���C�_�[�̏ꍇ
			case ColliderType::Sphere:
				CollCheck_Sphere(dynamic_cast<HWSphereCollider*>(*it1), *it2);
				break;
			}
		}
	}
}

bool CollisionWaltan::CollCheck_Box(HWBoxCollider* _col1, HWCollider* _col2)
{
	// _col2�̃R���C�_�[�^�C�v�ɂ���ď�����ς���
	switch (_col2->GetColliderType())
	{
		// �����̌^�R���C�_�[�̏ꍇ
	case ColliderType::Box:
	{
		HWBoxCollider* boxCol = dynamic_cast<HWBoxCollider*>(_col2);

		if (fabs(_col1->worldPosition.x - boxCol->worldPosition.x) > (_col1->size.x / 2 + boxCol->size.x / 2)) return false;
		if (fabs(_col1->worldPosition.y - boxCol->worldPosition.y) > (_col1->size.y / 2 + boxCol->size.y / 2)) return false;
		if (fabs(_col1->worldPosition.z - boxCol->worldPosition.z) > (_col1->size.z / 2 + boxCol->size.z / 2)) return false;

		return true;
		break;
	}
	// �J�v�Z���^�R���C�_�[�̏ꍇ
	case ColliderType::Capsule:
	{
		HWCapsuleCollider* capsuleCol = dynamic_cast<HWCapsuleCollider*>(_col2);
		break;
	}
	// ���̌^�R���C�_�[�̏ꍇ
	case ColliderType::Sphere:
	{
		HWSphereCollider* sphereCol = dynamic_cast<HWSphereCollider*>(_col2);
		break;
	}
	}

	return false;
}

bool CollisionWaltan::CollCheck_Sphere(HWSphereCollider* _col1, HWCollider* _col2)
{
	// _col2�̃R���C�_�[�^�C�v�ɂ���ď�����ς���
	switch (_col2->GetColliderType())
	{
		// �����̌^�R���C�_�[�̏ꍇ
	case ColliderType::Box:
		break;
		// �J�v�Z���^�R���C�_�[�̏ꍇ
	case ColliderType::Capsule:
		break;
		// ���̌^�R���C�_�[�̏ꍇ
	case ColliderType::Sphere:
		break;
	}

	return false;
}

bool CollisionWaltan::CollCheck_Capsule(HWCapsuleCollider* _col1, HWCollider* _col2)
{
	// _col2�̃R���C�_�[�^�C�v�ɂ���ď�����ς���
	switch (_col2->GetColliderType())
	{
		// �����̌^�R���C�_�[�̏ꍇ
	case ColliderType::Box:
		break;
		// �J�v�Z���^�R���C�_�[�̏ꍇ
	case ColliderType::Capsule:
		break;
		// ���̌^�R���C�_�[�̏ꍇ
	case ColliderType::Sphere:
		break;
	}

	return false;
}

#pragma endregion

