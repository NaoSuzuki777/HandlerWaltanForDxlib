#include "h/HandlerWaltan.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		HandlerWaltanの実装ファイル
*/


// 静的メンバ変数の初期化 ------------------------------------------------------------------------------------------------

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


#pragma region publucメソッド


void HandlerWaltan::Update()
{
    Time::Update();

    // インスタンス化された全てのHWGameObjectのUpdateメソッドを呼び出す
    for (auto obj : HWGameObject::GetGameObjects())
        obj->CallAllUpdates();

    // あたり判定を確認
    CollisionWaltan::Instance().Update();

    // インスタンス化されたInputSystemのUpdateメソッドを呼ぶ
    for (auto it = InputSystem::inputSystemVec.begin(); it != InputSystem::inputSystemVec.end(); ++it)
    {
        if ((*it)->active)
            (*it)->Update();
    }

    // Effekseerにより再生中のエフェクトを更新する。
    UpdateEffekseer3D();

    // Effekseerにより再生中のエフェクトを描画する。
    DrawEffekseer3D();

    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();

    //if (debugMode)
    //    GameTime::Draw();
    //GameTime::Wait();
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

int HandlerWaltan::Init(int _particle)
{
    // DXライブラリとEffekseerの初期化

    // DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
    // Effekseerを使用するには必ず設定する。
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
        // エラーコードを返す
        return -1;

    // Effekseerを初期化する。
    // 引数には画面に表示する最大パーティクル数を設定する。
    if (Effekseer_Init(8000) == -1)
    {
        DxLib_End();
        return -1;
    }

    // フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
    // Effekseerを使用する場合は必ず設定する。
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DXライブラリのデバイスロストした時のコールバックを設定する。
    // ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
    // ただし、DirectX11を使用する場合は実行する必要はない。
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // Zバッファを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetUseZBuffer3D(TRUE);

    // Zバッファへの書き込みを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetWriteZBuffer3D(TRUE);

    return 0;
}

void HandlerWaltan::End()
{
    // Effekseerを終了する。
    Effkseer_End();

    DxLib_End();				// ＤＸライブラリ使用の終了処理
}

#pragma endregion



