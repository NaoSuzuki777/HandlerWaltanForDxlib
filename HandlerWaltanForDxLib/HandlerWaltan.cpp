#include "h/HandlerWaltan.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		HandlerWaltanの実装ファイル
*/


// 静的メンバ変数の初期化
bool HandlerWaltan::debugMode = false;


#pragma region publucメソッド


void HandlerWaltan::Update()
{
    // インスタンス化された全てのHWGameObjectのUpdateメソッドを呼び出す
    for (auto obj : HWGameObject::GetGameObjects())
        obj->CallAllUpdates();

    // CollisionWaltanのUpdateメソッド(あたり判定)
    CollisionWaltan::Instance().Update();
}


#pragma endregion

#pragma region privateメソッド


HandlerWaltan::HandlerWaltan()
{
    // 各Waltanオブジェクトにインスタンスを与える
}


HandlerWaltan::~HandlerWaltan()
{

}


#pragma endregion

#pragma region staticメソッド


HandlerWaltan& HandlerWaltan::Instance()
{
    // シングルトンインスタンスを生成
    static HandlerWaltan instance;
    return instance;
}

int HandlerWaltan::Init()
{
    // DXライブラリの初期化

    if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
    {
        // エラーコードを返す
        return -1;
    }

    return 0;
}

void HandlerWaltan::End()
{
    DxLib_End();				// ＤＸライブラリ使用の終了処理
}

#pragma endregion



