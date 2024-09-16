#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"


/**
* @author   Suzuki N
* @date     24/07/18
* @note		あたり判定の情報を保持するコンポーネントの定義
*/


/**
 * @class	HWCollider
 * @brief	あたり判定の情報を保持するコライダーの基底コンポーネント
 */
class HWCollider : public HWComponent
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HWGameObject;

public:

	/*     メンバ変数     */

	/**
	 * @brief		コライダーを描画するか
	 * @History		24/09/15 作成(Suzuki N)
	 */
	bool isVisualization;

	/**
	 * @brief		コライダーがトリガーか
	 * @History		24/09/15 作成(Suzuki N)
	 */
	bool isTrigger;

	/**
	 * @brief		コライダーの中心(gameObjectのpositionとの相対距離)
	 * @History		24/09/15 作成(Suzuki N)
	 */
	VECTOR center;

	/**
	 * @brief		コライダーの中心(ワールドの原点との絶対距離)
	 * @History		24/09/15 作成(Suzuki N)
	 */
	VECTOR worldPosition;

	/*     メソッド     */

public:

	/**
	 * @brief		HWColliderのデストラクタ
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	virtual ~HWCollider() {}

protected:

	/**
	 * @brief		HWColliderのコンストラクタ
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	HWCollider();

	/**
	 * @brief		コライダーを描画する
	 * @detail		仮想関数
	 * @author		Suzuki N
	 * @date		24/09/16
	 */
	virtual void DrawCollider(){}

#pragma region オーバーライドメソッド

#pragma endregion
};
