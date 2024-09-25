#pragma once
#include "HWComponent.h"
#include "HWGameObject.h"
#include "HWRenderer.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		アニメーション制御コンポーネントの定義
*/


/**
 * @class	AnimInfo
 * @brief	アニメーション情報
 */
class AnimInfo
{
public:

	/*     メンバ変数     */

	/**
	 * @brief		アニメーションをアタッチするモデル
	 * @History		24/09/24 作成(Suzuki N)
	 */
	int modelHandle;

	/**
	 * @brief		アニメーションのハンドル
	 * @History		24/09/24 作成(Suzuki N)
	 */
	int animHandle;

	/**
	 * @brief		アニメーションファイル
	 * @History		24/09/24 作成(Suzuki N)
	 */
	std::string filePath;

	/**
	 * @brief		ループするか
	 * @History		24/09/24 作成(Suzuki N)
	 */
	bool isLoop;

	/**
	 * @brief		中断可能か
	 * @History		24/09/24 作成(Suzuki N)
	 */
	bool interruption;

	/**
	 * @brief		再生速度
	 * @History		24/09/24 作成(Suzuki N)
	 */
	float playSpeed;

	/**
	 * @brief		総再生時間
	 * @History		24/09/24 作成(Suzuki N)
	 */
	float totalTime;


public:
	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	AnimInfo(){}
};


/**
 * @class	HWAnimator
 * @brief	アニメーション制御管理用のコンポーネント
 */
class HWAnimator : public HWComponent
{
	// 特定のクラス以外からのアクセスを防ぐためのフレンド宣言
	friend class HWGameObject;

public:

	/*     メンバ変数     */

	/**
	 * @brief		各アニメーション情報
	 * @History		24/09/24 作成(Suzuki N)
	 */
	std::vector<std::unique_ptr<AnimInfo>> animInfoVec;

	/**
	 * @brief		アニメーション1の現在の再生時間
	 * @History		24/09/24 作成(Suzuki N)
	 */
	float playTime1;

	/**
	 * @brief		アニメーション2の現在の再生時間
	 * @History		24/09/25 作成(Suzuki N)
	 */
	float playTime2;

	/**
	 * @brief		再生中のアニメーション1インデックス
	 * @History		24/09/24 作成(Suzuki N)
	 */
	int playAnimId1;

	/**
	 * @brief		再生中のアニメーション2インデックス
	 * @History		24/09/25 作成(Suzuki N)
	 */
	int playAnimId2;

	/**
	 * @brief		playAnimId1 と playAnimId2 のブレンド率
	 * @History		24/09/25 作成(Suzuki N)
	 */
	float animBlendRate;

	/**
	 * @brief		再生を停止
	 * @History		24/09/24 作成(Suzuki N)
	 */
	bool isStop;

private:

	/**
	 * @brief		アニメーションの再生が終了したときに再生するIdleのID
	 * @History		24/09/24 作成(Suzuki N)
	 */
	int defaultAnimId = 0;


public:
	/*     メソッド     */

	/**
	 * @brief		コンストラクタ
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	HWAnimator(){}

	/**
	 * @brief		デストラクタ
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	~HWAnimator();

	/**
	 * @brief		アニメーションをロードする ※ロードするアニメーションはアニメーションが一つしかついていないこと
	 * @param[in]	const std::string& アニメーションファイルのパス
	 * @param[in]	const int		   読み込むアニメーションID
	 * @return		AnimInfo& アニメーション情報(戻り値からパラメータを操作する)
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	AnimInfo& AnimLoad(const std::string& _filePath, const int _animId = 0);

	/**
	 * @brief		再生するアニメーションを指定
	 * @param[in]	const int 再生するアニメーションID
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	void AnimChange(const int _animId);

#pragma region Setter関数

	/**
	 * @brief		アニメーションの再生が終了した時に自動再生されるdefaultアニメーション(Idolアニメーションなど)
	 * @param[in]	const int デフォルトのアニメーションID
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	void SetDefaultAnimId(const int _defaultAnimId) { defaultAnimId = _defaultAnimId; }

#pragma endregion


private:

	/**
	 * @brief		アニメーションを再生する
	 * @author		Suzuki N
	 * @date		24/09/24
	 */
	void AnimPlay();



protected:

#pragma region オーバーライドメソッド

	/**
	 * @brief		HWGameObjectにアタッチされた瞬間に働く
	 * @detail		オーバライドメソッド
	 * @author		Suzuki N
	 * @date		24/09/25
	 */
	void Awake()override;

	/**
	 * @brief		毎フレーム呼ばれる
	 * @detail		オーバーライド関数
	 * @author		Suzuki N
	 * @date		24/09/25
	 */
	void Update() override;

#pragma endregion
};

