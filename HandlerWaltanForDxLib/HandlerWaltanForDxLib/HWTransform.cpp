#include"h/HWTransform.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		MyTransform�̎����t�@�C��
*/


#pragma region private���\�b�h


void HWTransform::SetMatrix()
{
	MATRIX pos, rot, scl;

	// ���s�ړ�
	pos = MGetTranslate(position);
	// ��]
	MATRIX rotX = MGetRotX(rotate.x);
	MATRIX rotY = MGetRotY(rotate.y);
	MATRIX rotZ = MGetRotZ(rotate.z);
	// �O���[�o����]
	rot = MMult(rotZ, MMult(rotY, rotX));
	// ���[�J����]
	//rot = MMult(rotX, MMult(rotY, rotZ));

	// �g�k
	scl = MGetScale(scale);

	// �Ō�ɍs����������킹��
	globalMat = MMult(scl, MMult(rot, pos));
}


#pragma endregion

#pragma region public���\�b�h


HWTransform::HWTransform() : position({ 0.0f, 0.0f, 0.0f }), rotate({ 0.0f, 0.0f, 0.0f }), 
scale({ 1.0f, 1.0f, 1.0f }), localPosition({ 0.0f, 0.0f, 0.0f }), localRotate({ 0.0f, 0.0f, 0.0f }),
localScale({ 1.0f, 1.0f, 1.0f })
{
	globalMat = MGetIdent();
}


#pragma endregion

#pragma region �I�[�o�[���C�h���\�b�h


void HWTransform::Update()
{
	SetMatrix();
}


#pragma endregion