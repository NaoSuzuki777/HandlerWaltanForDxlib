#include<iostream>
#include"MyComponent.h"
#pragma once


/**
* @author   Suzuki N
* @date     24/07/18
* @note		あたり判定の情報を保持するコンポーネントの定義
*/


/**
 * @enum		eColliderType
 * @brief		コライダータイプ
 */
enum class eColliderType
{
	//!通常の四角形型のあたり判定(0)
	BoxCollider,
};


/**
 * @class		myTransform
 * @brief		オブジェクトの座標や回転などを保持するコンポーネント
 */
class MyCollider : public MyComponent
{
private:


public:
	/*     メンバ変数     */

	/**
	 * @brief		コライダータイプ
	 * @History		24/07/18 作成(Suzuki N)
	 */
	eColliderType colliderType;
	


	/*     メソッド     */


	/**
	 * @brief		MyColliderのコンストラクタ
	 * @ditail		イニシャライズ用
	 * @author		Suzuki N
	 * @date		24/07/18
	 */
	MyCollider() : colliderType(eColliderType::BoxCollider)
	{
	}


	/**
	 * @brief		毎フレーム呼ばれる
	 * @ditail		オーバーライド関数
	 * @author		Suzuki N
	 * @date		24/06/17
	 */
	void Update() override
	{
	}
};
