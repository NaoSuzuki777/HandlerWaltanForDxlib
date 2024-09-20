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

		//if (!HitCheck_OBB_OBB())
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

bool CollisionWaltan::HitCheck_OBB_OBB(OBB _obb1, OBB _obb2)
{
	return false;
}

#pragma endregion

