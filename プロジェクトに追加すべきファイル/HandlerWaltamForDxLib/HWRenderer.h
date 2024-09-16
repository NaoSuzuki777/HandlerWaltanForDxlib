#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"


/**
* @author   Suzuki N
* @date     24/08/25
* @note		モデル描画コンポーネントの定義
*/


/**
 * @class	HWRenderer
 * @brief	モデル描画用のコンポーネント
 */
class HWRenderer : public HWComponent
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HWGameObject;

private:

	/*     メンバ変数     */

	/**
	 * @brief		モデルハンドル
	 * @History		24/08/25 作成(Suzuki N)
	 */
	int modelHandle;


public:

	/*     メソッド     */

	/**
	 * @brief		HWRendererのコンストラクタ
	 * @detail		引数でモデルファイルのパスか、モデルハンドルを指定可
	 * @author		Suzuki N
	 * @date		24/08/25
	 */
	HWRenderer() : modelHandle(-1) {}

	/**
	 * @brief		HWRendererのコンストラクタ
	 * @detail		モデルファイルのパスでも可
	 * @param[in]	int モデルハンドル
	 * @author		Suzuki N
	 * @date		24/08/25
	 */
	HWRenderer(int _modelHandle);

	/**
	 * @brief		HWRendererのコンストラクタ
	 * @detail		モデルファイルのパスでも可
	 * @param[in]	std::string 読み込むモデルのMV1ファイルのパス
	 * @author		Suzuki N
	 * @date		24/08/25
	 */
	HWRenderer(std::string _pass);

	/**
	 * @brief		モデルハンドルを取得する
	 * @return		int モデルハンドル
	 * @author		Suzuki N
	 * @date		24/08/25
	 */
	int GetModelHandle() { return modelHandle; }

	 /**
	  * @brief		モデルハンドルを変更する(モデルの外見を変更する時など)
	  * @param[in]	int 新たなモデルハンドル 
	  * @author		Suzuki N
	  * @date		24/08/25
	  */
	void SetModelHandle(int _modelHandle) { modelHandle = _modelHandle; }

protected:

#pragma region オーバーライドメソッド

	/**
	 * @brief		毎フレーム呼ばれる
	 * @detail		オーバーライド関数
	 * @author		Suzuki N
	 * @date		24/09/01
	 */
	void Update() override;

#pragma endregion
};

