#include "h/HandlerWaltan.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		HandlerWaltan�̎����t�@�C��
*/


// �ÓI�����o�ϐ��̏����� ------------------------------------------------------------------------------------------------

bool HandlerWaltan::debugMode = false;
std::vector<InputSystem*> InputSystem::inputSystemVec;
float GameTime::deltaTime = 1.0f;
std::chrono::high_resolution_clock::time_point GameTime::lastFrameTime = std::chrono::high_resolution_clock::now();
int GameTime::N = 0;
int GameTime::startTime = 0;
int GameTime::count = 0;
float GameTime::fps = 0;
int GameTime::FPS = 120;

//------------------------------------------------------------------------------------------------------------------------


#pragma region publuc���\�b�h


void HandlerWaltan::Update()
{
    GameTime::Update();

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

    if (debugMode)
        GameTime::Draw();
    GameTime::Wait();
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

int HandlerWaltan::Init()
{
    // DX���C�u�����̏�����

    if (DxLib_Init() == -1)		// �c�w���C�u��������������
    {
        // �G���[�R�[�h��Ԃ�
        return -1;
    }

    return 0;
}

void HandlerWaltan::End()
{
    DxLib_End();				// �c�w���C�u�����g�p�̏I������
}

#pragma endregion



