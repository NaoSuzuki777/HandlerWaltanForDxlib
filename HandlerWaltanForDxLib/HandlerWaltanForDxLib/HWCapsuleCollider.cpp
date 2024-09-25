#include "h/HWCapsuleCollider.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		HWCapsuleCollider�̎����t�@�C��
*/


#pragma region private���\�b�h


void HWCapsuleCollider::ClosestPointsOnLineSegments(const HWCapsuleCollider& other, VECTOR& outPoint1, VECTOR& outPoint2)
{
	VECTOR u = VSub(endPos, startPos); // this�J�v�Z���̐����x�N�g��
	VECTOR v = VSub(other.endPos, other.startPos); // other�J�v�Z���̐����x�N�g��
	VECTOR w = VSub(startPos, other.startPos);

	float a = VDot(u, u); // u�Eu
	float b = VDot(u, v); // u�Ev
	float c = VDot(v, v); // v�Ev
	float d = VDot(u, w); // u�Ew
	float e = VDot(v, w); // v�Ew
	float denom = a * c - b * b; // ����

	float s, t;

	// denom���[���ɋ߂��ꍇ�i���s�ɋ߂��ꍇ�j�̏���
	if (denom < 1e-6f) {
		s = 0.0f;
		t = (e > 0.0f ? 0.0f : (e < 0.0f ? 1.0f : 0.0f)); // ���̃J�v�Z����ōł��߂��[�_�����
	}
	else {
		s = (b * e - c * d) / denom;
		t = (a * e - b * d) / denom;

		// s���͈͊O�̏ꍇ�̏C��
		if (s < 0.0f) s = 0.0f;
		else if (s > 1.0f) s = 1.0f;

		// t���͈͊O�̏ꍇ�̏C��
		if (t < 0.0f) t = 0.0f;
		else if (t > 1.0f) t = 1.0f;
	}

	// �ŋߐړ_�����߂�
	outPoint1 = VAdd(startPos, VScale(u, s)); // this�J�v�Z����̍ŋߐړ_
	outPoint2 = VAdd(other.startPos, VScale(v, t)); // other�J�v�Z����̍ŋߐړ_
}

#pragma region �����o������

void HWCapsuleCollider::PushOut_Capsule_Box(HWCollider& other)
{
}

void HWCapsuleCollider::PushOut_Capsule_Capsule(HWCapsuleCollider& other)
{
	// 2�̃J�v�Z���Ԃ̍ŋߐړ_�����߂�
	VECTOR point1, point2;
	ClosestPointsOnLineSegments(other, point1, point2);
	VECTOR collisionVector = VSub(point2, point1);
	float distance = VSize(collisionVector);

	// ���K�����ꂽ�Փ˃x�N�g��
	VECTOR collisionNormal = VScale(collisionVector, 1.0f / distance);

	// �߂荞�ݗʂ��v�Z
	float penetrationDepth = (radius + other.radius) - distance;

	// �J�v�Z���̈ʒu���C���i�߂荞�݂������j
	VECTOR correction = VScale(collisionNormal, penetrationDepth * 0.5f);
	startPos = VSub(startPos, correction);
	endPos = VSub(endPos, correction);
	other.startPos = VAdd(other.startPos, correction);
	other.endPos = VAdd(other.endPos, correction);

	// �Փˌ�̑��x�𒲐��i�V���v���Ȕ��ˏ����j
	VECTOR relativeVelocity = VSub(other.transform->velocity, transform->velocity);
	float velocityAlongNormal = VDot(relativeVelocity, collisionNormal);

	if (velocityAlongNormal > 0) {
		return; // ���x���Փ˕����ɐi��ł��Ȃ��ꍇ�͉������Ȃ�
	}

	// �����W���i1.0���Ɗ��S�e���Փˁj
	float restitution = 0.8f;

	// �Փˌ�̑��x�̌v�Z
	float impulse = -(1.0f + restitution) * velocityAlongNormal;
	VECTOR impulseVector = VScale(collisionNormal, impulse);

	// �e�J�v�Z���̑��x���X�V
	transform->velocity = VAdd(transform->velocity, VScale(impulseVector, 0.5f));
	other.transform->velocity = VSub(other.transform->velocity, VScale(impulseVector, 0.5f));
}

void HWCapsuleCollider::PushOut_Capsule_Sphere(HWCollider& other)
{
}

#pragma endregion


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
	DrawCapsule3D(startPos, endPos, radius,
		6, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
}

void HWCapsuleCollider::SetCollider()
{
	startPos = VGet(0, 0, 0);
	endPos = VGet(0, height, 0);

	// ��]�s��̍쐬�iZ -> Y -> X �̏��j
	MATRIX rotX = MGetRotX((float)Deg2Rad(transform->rotate.x));
	MATRIX rotY = MGetRotY((float)Deg2Rad(transform->rotate.y));
	MATRIX rotZ = MGetRotZ((float)Deg2Rad(transform->rotate.z));
	mRotate = MMult(rotZ, MMult(rotY, rotX));

	//! ���s�ړ��p�̍s��(���_����̈ړ���)
	MATRIX trans = MGetTranslate(center);
	//! trans -> rotate �Ŋ|���邱�Ƃŉ�]��ɕ��s�ړ�����(���[�J���ȕ��s�ړ�)
	MATRIX mat = MMult(trans, mRotate);

	// ���[�J�����W�ł̉�]
	startPos = VTransform(startPos, mat);
	// ���[���h���W�ւ̕ϊ�
	startPos = VAdd(startPos, transform->position);
	// ���[�J�����W�ł̉�]
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
	radius = 50.f;

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

void HWCapsuleCollider::OnCollisionEnter(HWCollider& _collider)
{
	//! �R���C�_�[���J�v�Z���ɃL���X�g
	switch (_collider.GetColliderType())
	{
	case ColliderType::Box:
		PushOut_Capsule_Box(static_cast<HWBoxCollider&>(_collider));
		break;

	case ColliderType::Capsule:
		PushOut_Capsule_Capsule(static_cast<HWCapsuleCollider&>(_collider));
		break;

	case ColliderType::Sphere:
		PushOut_Capsule_Sphere(static_cast<HWSphereCollider&>(_collider));
		break;
	}
}


#pragma endregion