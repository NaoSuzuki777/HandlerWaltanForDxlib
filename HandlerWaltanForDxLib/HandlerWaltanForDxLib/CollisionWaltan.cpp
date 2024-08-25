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
    for (auto& obj : HWGameObject::GetGameObjects())
    {
        obj->CallAllOnCollisionEnters();
        obj->CallAllOnCollisionStays();
        obj->CallAllOnCollisionExits();
    }
}


#pragma endregion

#pragma region static���\�b�h


CollisionWaltan& CollisionWaltan::Instance()
{
    // �V���O���g���C���X�^���X�𐶐�
    static CollisionWaltan instance;
    return instance;
}

int CollisionWaltan::Init()
{

    return 0;
}


#pragma endregion

