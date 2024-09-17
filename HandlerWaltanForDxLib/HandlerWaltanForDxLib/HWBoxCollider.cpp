#include "h/HWBoxCollider.h"


/**
* @author   Suzuki N
* @date     24/09/15
* @note		HWBoxCollider�̎����t�@�C��
*/


#pragma region private���\�b�h




#pragma endregion

#pragma region public���\�b�h


HWBoxCollider::HWBoxCollider()
{
	colliderType = ColliderType::Box;
	size = VGet(50.f, 50.f, 50.f);
}

HWBoxCollider::HWBoxCollider(VECTOR _size) : size(_size)
{
	colliderType = ColliderType::Box;
}

HWBoxCollider::HWBoxCollider(float _sizeX, float _sizeY, float _sizeZ) : size(VGet(_sizeX, _sizeY, _sizeZ))
{
	colliderType = ColliderType::Box;
}


#pragma endregion

#pragma region protected���\�b�h




#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h


HWBoxCollider::~HWBoxCollider()
{
	CollisionWaltan::Instance().UnRegister(dynamic_cast<HWCollider*>(this));
}

void HWBoxCollider::DrawCollider()
{
	//! ���_���W
	// [0][] = ���, [1][] = ���
	// [][0] = ����, [][1] = �E��, [][2] = ����, [][3] = �E��
	VECTOR vertex[2][4];

	vertex[0][0] = VAdd(worldPosition, VGet(-size.x / 2, size.y / 2, -size.z / 2));
	vertex[0][1] = VAdd(worldPosition, VGet(size.x / 2, size.y / 2, -size.z / 2));
	vertex[0][2] = VAdd(worldPosition, VGet(-size.x / 2, size.y / 2, size.z / 2));
	vertex[0][3] = VAdd(worldPosition, VGet(size.x / 2, size.y / 2, size.z / 2));
	vertex[1][0] = VAdd(worldPosition, VGet(-size.x / 2, -size.y / 2, -size.z / 2));
	vertex[1][1] = VAdd(worldPosition, VGet(size.x / 2, -size.y / 2, -size.z / 2));
	vertex[1][2] = VAdd(worldPosition, VGet(-size.x / 2, -size.y / 2, size.z / 2));
	vertex[1][3] = VAdd(worldPosition, VGet(size.x / 2, -size.y / 2, size.z / 2));


	DrawLine3D(vertex[0][0], vertex[0][1], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][0], vertex[0][2], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][1], vertex[0][3], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][2], vertex[0][3], GetColor(0, 255, 0));
	
	DrawLine3D(vertex[0][0], vertex[1][0], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][1], vertex[1][1], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][2], vertex[1][2], GetColor(0, 255, 0));
	DrawLine3D(vertex[0][3], vertex[1][3], GetColor(0, 255, 0));

	DrawLine3D(vertex[1][0], vertex[1][1], GetColor(0, 255, 0));
	DrawLine3D(vertex[1][0], vertex[1][2], GetColor(0, 255, 0));
	DrawLine3D(vertex[1][1], vertex[1][3], GetColor(0, 255, 0));
	DrawLine3D(vertex[1][2], vertex[1][3], GetColor(0, 255, 0));
}

void HWBoxCollider::Awake()
{
	center = VGet(0, 0, 0);
	worldPosition = VAdd(transform->position, center);
	// CollisionWaltan�ɓo�^
	CollisionWaltan::Instance().ColVec.push_back(dynamic_cast<HWCollider*>(this));
}

void HWBoxCollider::Update()
{
	// ��]�s��̍쐬
	MATRIX rotX = MGetRotX(transform->rotate.x);
	MATRIX rotY = MGetRotY(transform->rotate.y);
	MATRIX rotZ = MGetRotZ(transform->rotate.z);

	MATRIX rot = MMult(rotZ, MMult(rotY, rotX));



	worldPosition = VAdd(transform->position, center);

	// �f�o�b�O���[�h�A�������̓R���C�_�[�̉����t���O�������Ă���Ȃ�A�R���C�_�[��`�悷��
	if (isVisualization || HandlerWaltan::debugMode)
		DrawCollider();
}


#pragma endregion

