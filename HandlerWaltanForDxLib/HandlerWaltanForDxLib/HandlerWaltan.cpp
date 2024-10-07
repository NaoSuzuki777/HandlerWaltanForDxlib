#include "h/HandlerWaltan.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		HandlerWaltan�̎����t�@�C��
*/


// �ÓI�����o�ϐ��̏����� ------------------------------------------------------------------------------------------------

bool HandlerWaltan::debugMode = false;
std::vector<InputSystem*> InputSystem::inputSystemVec;
float Time::deltaTime = 1.0f;
std::chrono::high_resolution_clock::time_point Time::lastFrameTime = std::chrono::high_resolution_clock::now();
int Time::N = NULL;
int Time::startTime = NULL;
int Time::count = NULL;
float Time::fps = NULL;
int Time::FPS = 120;

//------------------------------------------------------------------------------------------------------------------------


#pragma region publuc���\�b�h


void HandlerWaltan::Update()
{
    Time::Update();

    // �C���X�^���X�����ꂽ�S�Ă�HWGameObject��Update���\�b�h���Ăяo��
    for (auto obj : HWGameObject::GetGameObjects())
        obj->CallAllUpdates();

    // �����蔻����m�F
    CollisionWaltan::Instance().Update();

    // �C���X�^���X�����ꂽInputSystem��Update���\�b�h���Ă�
    for (auto it = InputSystem::inputSystemVec.begin(); it != InputSystem::inputSystemVec.end(); ++it)
    {
        if ((*it)->active)
            (*it)->Update();
    }

    // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
    UpdateEffekseer3D();

    // Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
    DrawEffekseer3D();

    // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
    Effekseer_Sync3DSetting();

    //if (debugMode)
    //    GameTime::Draw();
    //GameTime::Wait();
}


#pragma endregion

#pragma region private���\�b�h


HandlerWaltan::HandlerWaltan()
{
    // �eWaltan�I�u�W�F�N�g�ɃC���X�^���X��^����
}


HandlerWaltan::~HandlerWaltan()
{

}


#pragma endregion

#pragma region static���\�b�h


HandlerWaltan& HandlerWaltan::Instance()
{
    // �V���O���g���C���X�^���X�𐶐�
    static HandlerWaltan instance;
    return instance;
}

int HandlerWaltan::Init(int _particle)
{
    // DX���C�u������Effekseer�̏�����

    // DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
    // Effekseer���g�p����ɂ͕K���ݒ肷��B
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    if (DxLib_Init() == -1)		// �c�w���C�u��������������
        // �G���[�R�[�h��Ԃ�
        return -1;

    // Effekseer������������B
    // �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
    if (Effekseer_Init(8000) == -1)
    {
        DxLib_End();
        return -1;
    }

    // �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
    // Effekseer���g�p����ꍇ�͕K���ݒ肷��B
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
    // �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
    // �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // Z�o�b�t�@��L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetUseZBuffer3D(TRUE);

    // Z�o�b�t�@�ւ̏������݂�L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetWriteZBuffer3D(TRUE);

    return 0;
}

void HandlerWaltan::End()
{
    // Effekseer���I������B
    Effkseer_End();

    DxLib_End();				// �c�w���C�u�����g�p�̏I������
}

#pragma endregion



