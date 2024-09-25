#pragma once
#include "Utilities.h"
#include "HandlerWaltan.h"
#include "HWBoxCollider.h"
#include "HWSphereCollider.h"
#include "HWCapsuleCollider.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		ColliderWaltanの定義ファイル
*/


/**
 * @class	ColliderWaltan
 * @brief   毎Fコライダーコンポーネントのあたり判定を監視し、条件に応じたハンドラーを呼び出す
 */
class CollisionWaltan
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HandlerWaltan;
    friend class HWBoxCollider;
    friend class HWSphereCollider;
    friend class HWCapsuleCollider;

    // コリジョンチェックに使う構造体

    /**
    * @struct	OBB
    * @brief	立方体の当たり判定
    */
    struct OBB {
        //! OBBの中心座標
        VECTOR c;      
        //! OBBの各軸(正規化された)
        VECTOR u[3];     
        //! 各軸方向のハーフサイズ
        VECTOR e;
    };

private:

    /*     メンバ変数     */

    /**
     * @brief		インスタンス化されているコライダー
     * @History		24/09/17 作成(Suzuki N)
     */
    std::vector<HWCollider*> ColVec;


private:

    /*     メソッド     */

    /**
     * @brief       インスタンスを取得する静的メソッド
     * @detail      初めの一回だけインスタンスを生成する
     * @return      CollisionWaltan& シングルトンインスタンス
     * @author      Suzuki N
     * @date        24/07/19
     */
    static CollisionWaltan& Instance()
    {
        // シングルトンインスタンスを生成
        static CollisionWaltan instance;
        return instance;
    }

    //インスタンスのコピー禁止
    //デフォルトのコピーコンストラクタを削除
    CollisionWaltan(const CollisionWaltan&) = delete;
    //デフォルトのコピー代入演算子も削除
    CollisionWaltan& operator=(const CollisionWaltan&) = delete;

    /**
     * @brief       コンストラクタ
     * @author      Suzuki N
     * @date        24/07/19
     */
    CollisionWaltan();

    /**
     * @brief       デストラクタ
     * @author      Suzuki N
     * @date        24/07/19
     */
    ~CollisionWaltan();

    /**
      * @brief       各コンポーネントのUpdateメソッドを全て呼び出す
      * @author      Suzuki N
      * @date        24/08/22
      */
    void Update();

    /**
     * @brief       登録されているコライダー情報を削除する
     * @param[in]   HWCollider* 削除するコライダー情報
     * @author      Suzuki N
     * @date        24/09/17
     */
    void UnRegister(HWCollider* _collider);

    /**
      * @brief       要素1 がBoxColliderの場合のコリジョンチェック
      * @param[in]   HWBoxCollider* あたり判定の重なりを見る立方体型Collider情報1
      * @param[in]   HWCollider*    あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Box(HWBoxCollider* _boxCol1, HWCollider* _col2);

    /**
      * @brief       要素1 がCapsuleColliderの場合のコリジョンチェック
      * @param[in]   HWCapsuleCollider*  あたり判定の重なりを見るカプセル型Collider情報1
      * @param[in]   HWCollider*         あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Capsule(HWCapsuleCollider* _col1, HWCollider* _col2);

    /**
      * @brief       要素1 がSphereColliderの場合のコリジョンチェック
      * @param[in]   HWSphereCollider*   あたり判定の重なりを見る球体型Collider情報1
      * @param[in]   HWCollider*         あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Sphere(HWSphereCollider* _col1, HWCollider* _col2);


#pragma region BOXタイプの衝突判定

    /**
      * @brief       ボックスとボックスのあたり判定
      * @param[in]   HWBoxCollider*      あたり判定の重なりを見るCollider情報1
      * @param[in]   HWBoxCollider*      あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Box_Box(HWBoxCollider* _boxCol, HWBoxCollider* _boxCol2);

    /**
      * @brief       ボックスとカプセルのあたり判定
      * @param[in]   HWBoxCollider*      あたり判定の重なりを見るCollider情報1
      * @param[in]   HWCapsuleCollider*  あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Box_Capsule(HWBoxCollider* _boxCol, HWCapsuleCollider* _capsuleCol);

    /**
      * @brief       ボックスとスフィアのあたり判定
      * @param[in]   HWBoxCollider*      あたり判定の重なりを見るCollider情報1
      * @param[in]   HWSphereCollider*   あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Box_Sphere(HWBoxCollider* _boxCol, HWSphereCollider* _sphereCol);

#pragma endregion

#pragma region CAPSULEタイプの衝突判定

    /**
      * @brief       カプセルとボックスのあたり判定
      * @param[in]   HWCapsuleCollider*  あたり判定の重なりを見るCollider情報1
      * @param[in]   HWBoxCollider*      あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Capsule_Box(HWCapsuleCollider* _capsuleCol, HWBoxCollider* _boxCol);

    /**
      * @brief       カプセルとカプセルのあたり判定
      * @param[in]   HWCapsuleCollider*  あたり判定の重なりを見るCollider情報1
      * @param[in]   HWCapsuleCollider*  あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Capsule_Capsule(HWCapsuleCollider* _capsuleCol, HWCapsuleCollider* _capsuleCol2);

    /**
      * @brief       カプセルとスフィアのあたり判定
      * @param[in]   HWCapsuleCollider*  あたり判定の重なりを見るCollider情報1
      * @param[in]   HWSphereCollider*   あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Capsule_Sphere(HWCapsuleCollider* _capsuleCol, HWSphereCollider* _sphereCol);

#pragma endregion

#pragma region SPHEREタイプの衝突判定

    /**
      * @brief       スフィアとボックスのあたり判定
      * @param[in]   HWSphereCollider*   あたり判定の重なりを見るCollider情報1
      * @param[in]   HWBoxCollider*      あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Sphere_Box(HWSphereCollider* _sphereCol, HWBoxCollider* _boxCol);

    /**
      * @brief       スフィアとカプセルのあたり判定
      * @param[in]   HWSphereCollider*   あたり判定の重なりを見るCollider情報1
      * @param[in]   HWCapsuleCollider*  あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Sphere_Capsule(HWSphereCollider* _sphereCol, HWCapsuleCollider* _capsuleCol);

    /**
      * @brief       スフィアとスフィアのあたり判定
      * @param[in]   HWSphereCollider*   あたり判定の重なりを見るCollider情報1
      * @param[in]   HWSphereCollider*   あたり判定の重なりを見るCollider情報2
      * @author      Suzuki N
      * @date        24/09/17
      */
    bool CollCheck_Sphere_Sphere(HWSphereCollider* _sphereCol, HWSphereCollider* _sphereCol2);

#pragma endregion


    /**
      * @brief       コリジョンHit時のコールバック関数を呼び出す
      * @author      Suzuki N
      * @date        24/09/17
      */
    void ColliderHitCallBacks(std::vector<HWCollider*>::iterator colIt, HWCollider* _col1, HWCollider* _col2, bool _isTrigger);

    /**
      * @brief       コリジョン接触がない場合の処理
      * @author      Suzuki N
      * @date        24/09/17
      */
    void ColliderAvoidCallBacks(std::vector<HWCollider*>::iterator colIt, HWCollider* _col1, HWCollider* _col2, bool _isTrigger);

    /**
      * @brief       OBB同士の当たり判定
      * @author      Suzuki N
      * @date        24/09/24
      */
    int TestOBBOBB(OBB* a, OBB* b);

};

