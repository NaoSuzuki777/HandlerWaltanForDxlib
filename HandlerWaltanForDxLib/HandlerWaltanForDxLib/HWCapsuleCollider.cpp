#include "h/HWCapsuleCollider.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		HWCapsuleCollider�̎����t�@�C��
*/


#pragma region private���\�b�h




#pragma endregion

#pragma region public���\�b�h


HWCapsuleCollider::HWCapsuleCollider()
{
	colliderType = ColliderType::Capsule;	
}


#pragma endregion

#pragma region protected���\�b�h




#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h


HWCapsuleCollider::~HWCapsuleCollider()
{
	CollisionWaltan::Instance().UnRegister(dynamic_cast<HWCollider*>(this));
}

void HWCapsuleCollider::DrawCollider()
{
	DrawCapsule3D(startPos, endPos, radius, GetColor(0, 255, 0), GetColor(0, 255, 0), 12, FALSE);
}

void HWCapsuleCollider::SetCollider()
{
	// ��]�s��̍쐬�iZ -> Y -> X �̏��j
	MATRIX rotX = MGetRotX((float)Deg2Rad(transform->rotate.x));
	MATRIX rotY = MGetRotY((float)Deg2Rad(transform->rotate.y));
	MATRIX rotZ = MGetRotZ((float)Deg2Rad(transform->rotate.z));
	mRotate = MMult(rotZ, MMult(rotY, rotX));

	//! ���s�ړ��p�̍s��(���_����̈ړ���)
	MATRIX trans = MGetTranslate(center);
	//! trans -> rotate �Ŋ|���邱�Ƃŉ�]��ɕ��s�ړ�����(���[�J���ȕ��s�ړ�)
	MATRIX mat = MMult(trans, mRotate);

	// �e���_�ɉ�]�s���K�p���A���[���h���W�֕ϊ�
	// ���[�J�����W�ł̉�]
	// �n�_
	startPos = VTransform(startPos, mat);
	// ���[���h���W�ւ̕ϊ�
	startPos = VAdd(startPos, transform->position);
	// �I�_
	endPos = VTransform(endPos, mat);
	// ���[���h���W�ւ̕ϊ�
	endPos = VAdd(endPos, transform->position);


	// ��]�s��̍쐬�iZ -> Y -> X �̏��j
	rotX = MGetRotX((float)Deg2Rad(transform->rotate.x));
	rotY = MGetRotY((float)Deg2Rad(transform->rotate.y));
	rotZ = MGetRotZ((float)Deg2Rad(transform->rotate.z));
	MATRIX mRotate2 = MMult(rotX, MMult(rotY, rotZ));
	//! ���s�ړ��p�̍s��(���_����̈ړ���)
	trans = MGetTranslate(center);
	//! trans -> rotate �Ŋ|���邱�Ƃŉ�]��ɕ��s�ړ�����(���[�J���ȕ��s�ړ�)
	mat = MMult(trans, mRotate);
	// �R���C�_�[�̒��S���W���X�V
	worldPosition = VTransform(VGet(0, 0, 0), mat);
	worldPosition = VAdd(worldPosition, transform->position);
}


void HWCapsuleCollider::Awake()
{
	center = VGet(0, 0, 0);
	startPos = VGet(0, 50, 0);
	endPos = VGet(0, -50, 0);

	// �R���C�_�[�̌`���\������
	SetCollider();

	// CollisionWaltan�ɓo�^
	CollisionWaltan::Instance().ColVec.push_back(dynamic_cast<HWCollider*>(this));
}

void HWCapsuleCollider::Update()
{
	// �R���C�_�[�̌`���\������
	SetCollider();

	// �f�o�b�O���[�h�A�������̓R���C�_�[�̉����t���O�������Ă���Ȃ�A�R���C�_�[��`�悷��
	if (isVisualization || HandlerWaltan::debugMode)
		DrawCollider();
}


#pragma endregion