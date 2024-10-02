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
			// �A�^�b�`����Ă���GameObject�������ꍇ�͖���
			if ((*it1)->gameObject == (*it2)->gameObject) continue;	
			// trigger�Ɣ�trigger�̏ꍇ�͂��̑g�ݍ��킹�͖���
			if ((*it1)->isTrigger != (*it2)->isTrigger) continue;

			// �Փ˒��̃R���C�_�[�̃��X�g�ɓo�^����Ă��邩���ׂ�
			auto collisionIt = std::find((*it1)->CollidersInCollision.begin(),
				(*it1)->CollidersInCollision.end(), *it2);

			// it1 �̃R���C�_�[�^�C�v�ɂ���ď�����ς���
			switch ((*it1)->GetColliderType())
			{
				// �����̌^�R���C�_�[�̏ꍇ
			case ColliderType::Box:
				if (CollCheck_Box(dynamic_cast<HWBoxCollider*>(*it1), *it2))
					// Hit���̃R�[���o�b�N�֐����Ăяo��
					ColliderHitCallBacks(collisionIt, *it1, *it2, (*it1)->isTrigger);
				else
					// ���ڐG���̏���
					ColliderAvoidCallBacks(collisionIt, *it1, *it2, (*it1)->isTrigger);
				break;

				// �J�v�Z���^�R���C�_�[�̏ꍇ
			case ColliderType::Capsule:
				if (!(*it1)->isTrigger && ((*it2)->gameObject->name == "Map" ||
					(*it2)->gameObject->name == "map" || (*it2)->gameObject->name == "Stage" ||
					(*it2)->gameObject->name == "stage"))
					// �R���C�_�[��trigger�ł͂Ȃ��ꍇ�A�ǂƂ̂����蔻������
					CollCheck_Capsule_Model(dynamic_cast<HWCapsuleCollider*>(*it1),
						(*it2)->gameObject->GetComponent<HWRenderer>()->GetModelHandle());

				if (CollCheck_Capsule(dynamic_cast<HWCapsuleCollider*>(*it1), *it2))
					// Hit���̃R�[���o�b�N�֐����Ăяo��
					ColliderHitCallBacks(collisionIt, *it1, *it2, (*it1)->isTrigger);
				else
					// ���ڐG���̏���
					ColliderAvoidCallBacks(collisionIt, *it1, *it2, (*it1)->isTrigger);
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
	// �{�b�N�X to �{�b�N�X �̏ꍇ
	case ColliderType::Box:
		return CollCheck_Box_Box(boxCol1, static_cast<HWBoxCollider*>(_col2));

	// �{�b�N�X to �J�v�Z�� �̏ꍇ
	case ColliderType::Capsule:
		return CollCheck_Box_Capsule(boxCol1, static_cast<HWCapsuleCollider*>(_col2));

	// �{�b�N�X to �X�t�B�A �̏ꍇ
	case ColliderType::Sphere:
		return CollCheck_Box_Sphere(boxCol1, static_cast<HWSphereCollider*>(_col2));
	}

	return false;
}

bool CollisionWaltan::CollCheck_Capsule(HWCapsuleCollider* _col1, HWCollider* _col2)
{
	// _col2�̃R���C�_�[�^�C�v�ɂ���ď�����ς���
	switch (_col2->GetColliderType())
	{
		// �J�v�Z�� to �{�b�N�X �̏ꍇ
	case ColliderType::Box:
		return CollCheck_Capsule_Box(_col1, static_cast<HWBoxCollider*>(_col2));

		// �J�v�Z�� to �J�v�Z�� �̏ꍇ
	case ColliderType::Capsule:
		return CollCheck_Capsule_Capsule(_col1, static_cast<HWCapsuleCollider*>(_col2));

		// �J�v�Z�� to �X�t�B�A �̏ꍇ
	case ColliderType::Sphere:
		return CollCheck_Capsule_Sphere(_col1, static_cast<HWSphereCollider*>(_col2));
	}

	return false;
}

bool CollisionWaltan::CollCheck_Sphere(HWSphereCollider* _col1, HWCollider* _col2)
{
	// _col2�̃R���C�_�[�^�C�v�ɂ���ď�����ς���
	switch (_col2->GetColliderType())
	{
		// �X�t�B�A to �{�b�N�X �̏ꍇ
	case ColliderType::Box:
		return CollCheck_Sphere_Box(_col1, static_cast<HWBoxCollider*>(_col2));

		// �X�t�B�A to �J�v�Z�� �̏ꍇ
	case ColliderType::Capsule:
		return CollCheck_Sphere_Capsule(_col1, static_cast<HWCapsuleCollider*>(_col2));

		// �X�t�B�A to �X�t�B�A �̏ꍇ
	case ColliderType::Sphere:
		return CollCheck_Sphere_Sphere(_col1, static_cast<HWSphereCollider*>(_col2));
	}

	return false;
}


#pragma region BOX�^�C�v�̏Փ˔���


bool CollisionWaltan::CollCheck_BOX_Model(HWBoxCollider* _boxCol, const int _modelHandle)
{
	return false;
}

bool CollisionWaltan::CollCheck_Box_Box(HWBoxCollider* _boxCol, HWBoxCollider* _boxCol2)
{
	OBB obb1;
	OBB obb2;

	obb1.c = _boxCol->worldPosition;
	// ��]�s��̍쐬�iX -> Y -> Z �̏��j
	MATRIX rotX1 = MGetRotX((float)Deg2Rad(_boxCol->transform->rotate.x));
	MATRIX rotY1 = MGetRotY((float)Deg2Rad(_boxCol->transform->rotate.y));
	MATRIX rotZ1 = MGetRotZ((float)Deg2Rad(_boxCol->transform->rotate.z));
	MATRIX mRotate1 = MMult(rotZ1, MMult(rotY1, rotX1));

	obb1.u[0] = VGet(mRotate1.m[0][0], mRotate1.m[1][0], mRotate1.m[2][0]); // X��
	obb1.u[1] = VGet(mRotate1.m[0][1], mRotate1.m[1][1], mRotate1.m[2][1]); // Y��
	obb1.u[2] = VGet(mRotate1.m[0][2], mRotate1.m[1][2], mRotate1.m[2][2]); // Z��
	obb1.e = VGet(_boxCol->size.x / 2, _boxCol->size.y / 2, _boxCol->size.z / 2);

	obb2.c = _boxCol2->worldPosition;
	// ��]�s��̍쐬�iX -> Y -> Z �̏��j
	MATRIX rotX2 = MGetRotX((float)Deg2Rad(_boxCol2->transform->rotate.x));
	MATRIX rotY2 = MGetRotY((float)Deg2Rad(_boxCol2->transform->rotate.y));
	MATRIX rotZ2 = MGetRotZ((float)Deg2Rad(_boxCol2->transform->rotate.z));
	MATRIX mRotate2 = MMult(rotZ2, MMult(rotY2, rotX2));
	obb2.u[0] = VGet(mRotate2.m[0][0], mRotate2.m[1][0], mRotate2.m[2][0]); // X��
	obb2.u[1] = VGet(mRotate2.m[0][1], mRotate2.m[1][1], mRotate2.m[2][1]); // Y��
	obb2.u[2] = VGet(mRotate2.m[0][2], mRotate2.m[1][2], mRotate2.m[2][2]); // Z��
	obb2.e = VGet(_boxCol2->size.x / 2, _boxCol2->size.y / 2, _boxCol2->size.z / 2);

	if (!TestOBBOBB(&obb1, &obb2))
		return false;


	// �R���C�_�[���g���K�[�łȂ��Ȃ�A�R���C�_�[���m���߂荞�܂Ȃ��悤�ɂ���
	if (!_boxCol->isTrigger)
	{
	}

	return true;
}

bool CollisionWaltan::CollCheck_Box_Capsule(HWBoxCollider* _boxCol, HWCapsuleCollider* _capsuleCol)
{
	return false;
}

bool CollisionWaltan::CollCheck_Box_Sphere(HWBoxCollider* _boxCol, HWSphereCollider* _sphereCol)
{
	return false;
}


#pragma endregion

#pragma region CAPSULE�^�C�v�̏Փ˔���


bool CollisionWaltan::CollCheck_Capsule_Model(HWCapsuleCollider* _capsuleCol, const int _modelHandle)
{
	MV1_COLL_RESULT_POLY* Poly;			// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^( �g��Ȃ��Ă��ς܂����܂����v���O�����������Ȃ�̂ŁE�E�E )

	// �ړ��O�̍��W��ۑ�
	const VECTOR OldPos = _capsuleCol->transform->position;
	// �ړ���
	VECTOR velocity = _capsuleCol->transform->velocity;
	// �ړ���̍��W���Z�o
	VECTOR NewPos = VAdd(OldPos, velocity);

	std::vector<MV1_COLL_RESULT_POLY*> Walls;	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	std::vector<MV1_COLL_RESULT_POLY*> Floors;	// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��

	int MaxHitCol = 0;
	int HitTryNum = 0;

	bool isWallHit;

	// �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
	// ( ���o����͈͈͂ړ��������l������ )
	MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Sphere(_modelHandle, -1, OldPos, _capsuleCol->radius);

	// x����y�������� 0.01f �ȏ�ړ������ꍇ�́u�ړ������v����
	const bool IsMove = fabs(velocity.x) > 0.01f || fabs(velocity.z) > 0.01f;

	// ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f����
	Walls.clear();
	Floors.clear();

	// ���o���ꂽ�|���S���̐������J��Ԃ�
	for (int i = 0; i < HitDim.HitNum; i++)
	{
		// �w�y���ʂɐ������ǂ����̓|���S���̖@���̂x�������O�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
		if (IsNearlyZero(HitDim.Dim[i].Normal.y))
		{
			// �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�v���C���[�̂x���W�{�P�D�O����荂���|���S���̂ݓ����蔻����s��
			if (HitDim.Dim[i].Position[0].y > OldPos.y + 1.0f ||
				HitDim.Dim[i].Position[1].y > OldPos.y + 1.0f ||
				HitDim.Dim[i].Position[2].y > OldPos.y + 1.0f)
			{
				// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
				if (Walls.size() < MaxHitCol)
				{
					// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
					Walls.push_back(&HitDim.Dim[i]);
				}
			}
		}
		else
		{
			// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
			if (Floors.size() < MaxHitCol)
			{
				// �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�z��ɕۑ�����
				Floors.push_back(&HitDim.Dim[i]);
			}
		}
	}

	// �ǃ|���S���Ƃ̓����蔻�菈��
	if (Walls.size() != 0)
	{
		// �ړ��������ǂ����ŏ����𕪊�
		if (IsMove)
		{
			// �ǃ|���S���̐������J��Ԃ�
			for (int i = 0; i < Walls.size(); i++)
			{
				// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				Poly = Walls[i];

				// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
				if (HitCheck_Capsule_Triangle(NewPos, VAdd(NewPos, VGet(0.0f, _capsuleCol->height, 0.0f)), _capsuleCol->radius,
					Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) { continue; }

				// �����ɂ�����|���S���ƃv���C���[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
				isWallHit = true;

				// �ǂɓ���������ǂɎՂ��Ȃ��ړ������������ړ�����
				{
					VECTOR SlideVec;	// �v���C���[���X���C�h������x�N�g��

					// �i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o
					SlideVec = VCross(velocity, Poly->Normal);

					// �Z�o�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o�A���ꂪ
					// ���̈ړ���������Ǖ����̈ړ������𔲂����x�N�g��
					SlideVec = VCross(Poly->Normal, SlideVec);

					// ������ړ��O�̍��W�ɑ��������̂�V���ȍ��W�Ƃ���
					NewPos = VAdd(OldPos, SlideVec);
				}

				// �V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
				bool isCollisionNewPos = false;
				for (int j = 0; j < Walls.size(); j++)
				{
					// j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					Poly = Walls[j];

					// �������Ă����烋�[�v���甲����
					if (HitCheck_Capsule_Triangle(NewPos, VAdd(NewPos, VGet(0.0f, _capsuleCol->height, 0.0f)), _capsuleCol->radius,
						Poly->Position[0], Poly->Position[1], Poly->Position[2]))
					{
						isCollisionNewPos = true;
						break;
					}
				}

				// �ǂ̃|���S���Ƃ�������Ȃ������̂�
				// �ǂɓ��������t���O��|������Ń��[�v���甲����
				if (!isCollisionNewPos)
				{
					isWallHit = false;
					break;
				}
			}
		}
		else
		{
			// �ړ����Ă��Ȃ��ꍇ�̏���

			// �ǃ|���S���̐������J��Ԃ�
			for (int i = 0; i < Walls.size(); i++)
			{
				// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				Poly = Walls[i];

				// �|���S���ɓ������Ă����瓖�������t���O�𗧂Ă���Ń��[�v���甲����
				if (HitCheck_Capsule_Triangle(NewPos, VAdd(NewPos, VGet(0.0f, _capsuleCol->height, 0.0f)), _capsuleCol->radius,
					Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
				{
					isWallHit = true;
					break;
				}
			}
		}

		// �ǂɓ������Ă�����ǂ��牟���o���������s��
		if (isWallHit)
		{
			// �ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
			for (int k = 0; k < HitTryNum; k++)
			{
				bool IsNeedHitTry = true;
				// �ǃ|���S���̐������J��Ԃ�
				for (int i = 0; i < Walls.size(); i++)
				{
					// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					Poly = Walls[i];

					// �v���C���[�Ɠ������Ă��邩�𔻒�
					if (HitCheck_Capsule_Triangle(NewPos, VAdd(NewPos, VGet(0.0f, _capsuleCol->height, 0.0f)), _capsuleCol->radius,
						Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) { continue; }

					// �������Ă�����K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
					NewPos = VAdd(NewPos, VScale(Poly->Normal, HIT_SLIDE_LENGTH));

					// �ړ�������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
					bool isCollisionNewPos = false;
					for (int j = 0; j < Walls.size(); j++)
					{
						// �������Ă����烋�[�v�𔲂���
						Poly = Walls[j];
						if (HitCheck_Capsule_Triangle(NewPos, VAdd(NewPos, VGet(0.0f, _capsuleCol->height, 0.0f)), _capsuleCol->radius,
							Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
						{
							isCollisionNewPos = true;
							break;
						}
					}

					// �S�Ẵ|���S���Ɠ������Ă��Ȃ������炱���Ń��[�v�I��
					if (!isCollisionNewPos)
					{
						// �S���̃|���S���ŉ����o�������݂�O�ɑS�Ă̕ǃ|���S���ƐڐG���Ȃ��Ȃ����Ƃ������ƂȂ̂ŉ����o���`�F�b�N�͂������Ȃ��Ă���.
						IsNeedHitTry = false;
						break;
					}
				}

				if (!IsNeedHitTry)
				{
					break;
				}
			}
		}
	}

	return isWallHit;
}

bool CollisionWaltan::CollCheck_Capsule_Box(HWCapsuleCollider* _capsuleCol, HWBoxCollider* _boxCol)
{
	return false;
}

bool CollisionWaltan::CollCheck_Capsule_Capsule(HWCapsuleCollider* _capsuleCol, HWCapsuleCollider* _capsuleCol2)
{
	VECTOR sPos1 = VAdd(_capsuleCol->startPos, _capsuleCol->transform->velocity);
	VECTOR ePos1 = VAdd(_capsuleCol->endPos, _capsuleCol->transform->velocity);
	VECTOR sPos2 = VAdd(_capsuleCol2->startPos, _capsuleCol2->transform->velocity);
	VECTOR ePos2 = VAdd(_capsuleCol2->endPos, _capsuleCol2->transform->velocity);

	if (!HitCheck_Capsule_Capsule(sPos1, ePos1, _capsuleCol->radius,
		sPos2, ePos2, _capsuleCol2->radius))
		return false;

	// �R���C�_�[���g���K�[�łȂ��Ȃ�A�R���C�_�[���m���߂荞�܂Ȃ��悤�ɂ���
	if (!_capsuleCol->isTrigger)
	{
		// �ړ��x�N�g���𖳌�������
		_capsuleCol->transform->velocity = VGet(0, 0, 0);
		_capsuleCol2->transform->velocity = VGet(0, 0, 0);
	}

	return true;
}

bool CollisionWaltan::CollCheck_Capsule_Sphere(HWCapsuleCollider* _capsuleCol, HWSphereCollider* _sphereCol)
{
	return false;
}


#pragma endregion

#pragma region SPHERE�^�C�v�̏Փ˔���


bool CollisionWaltan::CollCheck_Sphere_Model(HWSphereCollider* _sphereCol, const int _modelHandle)
{
	return false;
}

bool CollisionWaltan::CollCheck_Sphere_Box(HWSphereCollider* _sphereCol, HWBoxCollider* _boxCol)
{
	return false;
}

bool CollisionWaltan::CollCheck_Sphere_Capsule(HWSphereCollider* _sphereCol, HWCapsuleCollider* _capsuleCol)
{
	return false;
}

bool CollisionWaltan::CollCheck_Sphere_Sphere(HWSphereCollider* _sphereCol, HWSphereCollider* _sphereCol2)
{
	return false;
}


#pragma endregion


void CollisionWaltan::ColliderHitCallBacks(std::vector<HWCollider*>::iterator colIt, HWCollider* _col1, HWCollider* _col2, bool _isTrigger)
{
	// �Փ˂����m����
	// �R���C�_�[��trigger���ǂ����ŌĂԃ��\�b�h��ς���
	if (_col1->isTrigger)
	{
		if (colIt == _col1->CollidersInCollision.end())
		{

			// �Փˎ��̃R�[���o�b�N�֐��̌Ăяo��
			_col1->gameObject->CallAllOnTriggerEnters(*_col2);
			_col2->gameObject->CallAllOnTriggerEnters(*_col1);
		}
		else
		{
			// ���łɓo�^����Ă���ꍇ�͏Փ˒��̃R�[���o�b�N�֐����Ăяo��
			_col1->gameObject->CallAllOnTriggerStays(*_col2);
			_col1->gameObject->CallAllOnTriggerStays(*_col1);
		}
	}
	else
	{
		// ��trigger�̏ꍇ
		if (colIt == _col1->CollidersInCollision.end())
		{

			// �Փˎ��̃R�[���o�b�N�֐��̌Ăяo��
			_col1->gameObject->CallAllOnCollisionEnters(*_col2);
			_col2->gameObject->CallAllOnCollisionEnters(*_col1);
		}
		else
		{
			// ���łɓo�^����Ă���ꍇ�͏Փ˒��̃R�[���o�b�N�֐����Ăяo��
			_col1->gameObject->CallAllOnCollisionStays(*_col2);
			_col2->gameObject->CallAllOnCollisionStays(*_col1);
		}
	}
	// �Փ˒��̃R���C�_�[�̃��X�g�ɂȂ��ꍇ�͐V���ɓo�^
	if (colIt == _col1->CollidersInCollision.end())
	{
		_col1->CollidersInCollision.push_back(_col2);
		_col2->CollidersInCollision.push_back(_col1);
	}
}

void CollisionWaltan::ColliderAvoidCallBacks(std::vector<HWCollider*>::iterator colIt, HWCollider* _col1, HWCollider* _col2, bool _isTrigger)
{
	// �Փ˂����m���Ȃ�����
	// �o�^���Ă���R���C�_�[�̏ꍇ(�O�t���[���܂ŏՓ˂��Ă���)
	if (colIt != _col1->CollidersInCollision.end())
	{
		// �R���C�_�[��trigger���ǂ����ŌĂԃ��\�b�h��ς���
		if (_col1->isTrigger)
		{
			// �ՓˏI�����̃R�[���o�b�N�֐��̌Ăяo��
			_col1->gameObject->CallAllOnTriggerExits(*_col2);
			_col2->gameObject->CallAllOnTriggerExits(*_col1);
		}
		else
		{
			// ��trigger�̏ꍇ
			// �ՓˏI�����̃R�[���o�b�N�֐��̌Ăяo��
			_col1->gameObject->CallAllOnCollisionExits(*_col2);
			_col2->gameObject->CallAllOnCollisionExits(*_col1);
		}
		// �o�^�����폜����
		_col1->CollidersInCollision.erase(colIt);
		auto collisionIt2 = std::find(_col2->CollidersInCollision.begin(),
			_col2->CollidersInCollision.end(), _col1);
		if (collisionIt2 != _col2->CollidersInCollision.end())
			_col2->CollidersInCollision.erase(collisionIt2);
	}
}

int CollisionWaltan::TestOBBOBB(OBB* a, OBB* b)
{
	const float EPSILON = 1.175494e-37f;

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

#pragma endregion

