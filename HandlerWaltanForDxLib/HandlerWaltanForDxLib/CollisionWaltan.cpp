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
	//! �o�^����Ă���Collider�̐�����ȉ��Ȃ炻�̂܂܏I��
	if (ColVec.size() < 2)return;

	// �����蔻����`�F�b�N����
	for (auto it1 = ColVec.begin(); it1 != ColVec.end() - 1; ++it1)
	{
		// ���łɃ`�F�b�N�����g�ݍ��킹���Ȃ�
		for (auto it2 = it1 + 1; it2 != ColVec.end(); ++it2)
		{
			// trigger�Ɣ�trigger�̏ꍇ�͂��̑g�ݍ��킹�͖���
			if ((*it1)->isTrigger != (*it2)->isTrigger)
				continue;

			// �Փ˒��̃R���C�_�[�̃��X�g�ɓo�^����Ă��邩���ׂ�
			auto collisionIt = std::find((*it1)->CollidersInCollision.begin(),
				(*it1)->CollidersInCollision.end(), *it2);

			// it1 �̃R���C�_�[�^�C�v�ɂ���ď�����ς���
			switch ((*it1)->GetColliderType())
			{
				// �����̌^�R���C�_�[�̏ꍇ
			case ColliderType::Box:
				if (CollCheck_Box(dynamic_cast<HWBoxCollider*>(*it1), *it2))
				{
					// �Փ˂����m����
					// �R���C�_�[��trigger���ǂ����ŌĂԃ��\�b�h��ς���
					if ((*it1)->isTrigger)
					{
						if (collisionIt == (*it1)->CollidersInCollision.end())
						{

							// �Փˎ��̃R�[���o�b�N�֐��̌Ăяo��
							(*it1)->gameObject->CallAllOnTriggerEnters(*it2);
							(*it2)->gameObject->CallAllOnTriggerEnters(*it1);
						}
						else
						{
							// ���łɓo�^����Ă���ꍇ�͏Փ˒��̃R�[���o�b�N�֐����Ăяo��
							(*it1)->gameObject->CallAllOnTriggerStays(*it2);
							(*it2)->gameObject->CallAllOnTriggerStays(*it1);
						}
					}
					else
					{
						// ��trigger�̏ꍇ
						if (collisionIt == (*it1)->CollidersInCollision.end())
						{

							// �Փˎ��̃R�[���o�b�N�֐��̌Ăяo��
							(*it1)->gameObject->CallAllOnCollisionEnters(*it2);
							(*it2)->gameObject->CallAllOnCollisionEnters(*it1);
						}
						else
						{
							// ���łɓo�^����Ă���ꍇ�͏Փ˒��̃R�[���o�b�N�֐����Ăяo��
							(*it1)->gameObject->CallAllOnCollisionStays(*it2);
							(*it2)->gameObject->CallAllOnCollisionStays(*it1);
						}
					}
					// �Փ˒��̃R���C�_�[�̃��X�g�ɂȂ��ꍇ�͐V���ɓo�^
					if (collisionIt == (*it1)->CollidersInCollision.end())
					{
						(*it1)->CollidersInCollision.push_back(*it2);
						(*it2)->CollidersInCollision.push_back(*it1);
					}
				}
				else
				{
					// �Փ˂����m���Ȃ�����
					// �o�^���Ă���R���C�_�[�̏ꍇ(�O�t���[���܂ŏՓ˂��Ă���)
					if (collisionIt != (*it1)->CollidersInCollision.end())
					{
						// �R���C�_�[��trigger���ǂ����ŌĂԃ��\�b�h��ς���
						if ((*it1)->isTrigger)
						{
							// �ՓˏI�����̃R�[���o�b�N�֐��̌Ăяo��
							(*it1)->gameObject->CallAllOnTriggerExits(*it2);
							(*it2)->gameObject->CallAllOnTriggerExits(*it1);
						}
						else
						{
							// ��trigger�̏ꍇ
							// �ՓˏI�����̃R�[���o�b�N�֐��̌Ăяo��
							(*it1)->gameObject->CallAllOnCollisionExits(*it2);
							(*it2)->gameObject->CallAllOnCollisionExits(*it1);
						}
						// �o�^�����폜����
						(*it1)->CollidersInCollision.erase(collisionIt);
						auto collisionIt2 = std::find((*it2)->CollidersInCollision.begin(),
							(*it2)->CollidersInCollision.end(), *it1);
						if(collisionIt2 != (*it2)->CollidersInCollision.end())
							(*it2)->CollidersInCollision.erase(collisionIt2);
					}
				}
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

void CollisionWaltan::UnRegister(HWCollider* _collider)
{
	// �v�f���폜����
	auto it = std::find(ColVec.begin(), ColVec.end(), _collider);
	// ���������ꍇ�͍폜
	if (it != ColVec.end())
		ColVec.erase(it);
}

bool CollisionWaltan::CollCheck_Box(HWBoxCollider* boxCol1, HWCollider* _col2)
{
	// _col2�̃R���C�_�[�^�C�v�ɂ���ď�����ς���
	switch (_col2->GetColliderType())
	{
		// �����̌^�R���C�_�[�̏ꍇ
	case ColliderType::Box:
	{
		//! BoxCollider�ɃL���X�g
		HWBoxCollider* boxCol2 = dynamic_cast<HWBoxCollider*>(_col2);

		//-----------------------------------------------------------
		// �����蔻�������@*������
		//-----------------------------------------------------------

		OBB obb1;
		OBB obb2;

		obb1.center = boxCol1->worldPosition;
		// ��]�s��̍쐬�iX -> Y -> Z �̏��j
		MATRIX rotX1 = MGetRotX((float)Deg2Rad(boxCol1->transform->rotate.x));
		MATRIX rotY1 = MGetRotY((float)Deg2Rad(boxCol1->transform->rotate.y));
		MATRIX rotZ1 = MGetRotZ((float)Deg2Rad(boxCol1->transform->rotate.z));
		MATRIX mRotate1 = MMult(rotX1, MMult(rotY1, rotZ1));

		obb1.axis[0] = VGet(mRotate1.m[0][0], mRotate1.m[1][0], mRotate1.m[2][0]); // X��
		obb1.axis[1] = VGet(mRotate1.m[0][1], mRotate1.m[1][1], mRotate1.m[2][1]); // Y��
		obb1.axis[2] = VGet(mRotate1.m[0][2], mRotate1.m[1][2], mRotate1.m[2][2]); // Z��
		obb1.extent = VGet(boxCol1->size.x, boxCol1->size.y / 2, boxCol1->size.z);

		obb2.center = boxCol2->worldPosition;
		// ��]�s��̍쐬�iX -> Y -> Z �̏��j
		MATRIX rotX2 = MGetRotX((float)Deg2Rad(boxCol2->transform->rotate.x));
		MATRIX rotY2 = MGetRotY((float)Deg2Rad(boxCol2->transform->rotate.y));
		MATRIX rotZ2 = MGetRotZ((float)Deg2Rad(boxCol2->transform->rotate.z));
		MATRIX mRotate2 = MMult(rotX2, MMult(rotY2, rotZ2));
		obb2.axis[0] = VGet(mRotate2.m[0][0], mRotate2.m[1][0], mRotate2.m[2][0]); // X��
		obb2.axis[1] = VGet(mRotate2.m[0][1], mRotate2.m[1][1], mRotate2.m[2][1]); // Y��
		obb2.axis[2] = VGet(mRotate2.m[0][2], mRotate2.m[1][2], mRotate2.m[2][2]); // Z��
		obb2.extent = VGet(boxCol2->size.x, boxCol2->size.y / 2, boxCol2->size.z);

		if (!CheckOBBIntersection(obb1, obb2))
			return false;


		// �R���C�_�[���g���K�[�łȂ��Ȃ�A�R���C�_�[���m���߂荞�܂Ȃ��悤�ɂ���
		if (!boxCol1->isTrigger)
		{

		}

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

