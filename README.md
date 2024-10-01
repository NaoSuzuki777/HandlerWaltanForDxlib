<div id="top"></div>

## 使用技術一覧

<!-- シールド一覧 -->

</p>

## 目次

1. [プロジェクトについて](#プロジェクトについて)
2. [環境](#環境)
3. [導入方法](#導入方法)
4. [使い方](#使い方)

<br>

<b> APIリファレンス </b>

1. [HWGameObject](#hwgameobject)
2. [HWComponent](#hwcomponent)
3. [HWTransform](#hwtransform)
4. [HWCapsuleCollider](#hwcapsulecollider)
5. [HWAnimator](#hwanimator)
6. [InputSystem](#inputsystem)



<!-- READMEの作成方法のテンプレート -->
<br />
<div align="right">
    <a href="https://qiita.com/shun198/items/c983c713452c041ef787"><strong>READMEのテンプレート »</strong></a>
</div>
</><br />
<!-- プロジェクト名を記載 -->


## プロジェクトについて

来年に製作する予定の自作エンジンに向けて、unityと同じ感覚で使えるコンポーネント思考の
ライブラリを製作する。

<!-- プロジェクトの概要を記載 -->

  <p align="left">
    <br />
    <!-- プロジェクト詳細にBacklogのWikiのリンク -->
    <a href="Backlogのwikiリンク"><strong>プロジェクト詳細 »</strong></a>
    <br />
    <br />

<p align="right">(<a href="#top">トップへ</a>)</p>

## 環境

<!-- 言語、フレームワーク、ミドルウェア、インフラの一覧とバージョンを記載 -->

| 言語・フレームワーク  | バージョン |
| --------------------- | ---------- |
| C++                   | 14         |
| DXライブラリ           | 3.24d      |


現状、開発環境はVisualStudio2022を想定しています。

<p align="right">(<a href="#top">トップへ</a>)</p>


## 導入方法

<!-- 導入方法 -->

<b> <Visual Studio Community 2022 の場合> </b>

プロジェクトの作成 と プロジェクトへ新規プログラムファイルを作成・追加 までは <a href="https://dxlib.xsrv.jp/use/dxuse_vscom2022.html"><strong>こちら</strong></a> を参照してください。

<br>

<b> 1.ＤＸライブラリ と 当ライブラリ を使用するためのプロジェクトの設定を行う </b>

<body>

 	①　Visual Studio Community 2022 のメニューの
	　　『プロジェクト(P)』→『(プロジェクト名) のプロパティ(E)...』を選んで、プロジェクトのプロパティダイアログを開きます。
   
	②　次にダイアログの左上にある『構成(C):』と書かれている項目を『アクティブ(Debug)』から『すべての構成』に、
	　　『構成(C):』の右側にある『プラットフォーム(P):』と書かれている項目を『アクティブ(x64)』から
	　　『すべてのプラットフォーム』変更します。

	③　次にダイアログの左側のリストから『構成プロパティ』→『詳細』を選びます。

	④　次にダイアログ右側に表示されている『文字セット』の項目を
	　　『マルチ バイト文字セットを使用する』に変更したあと、ダイアログ右下にある『適用(A)』ボタンを押します。

	⑤　次に左側のリストから『構成プロパティ』→『Ｃ／Ｃ＋＋』→『全般』を選びます。

	⑥　次に右側に表示されている『追加のインクルードディレクトリ』の項目にＤＸライブラリのパッケージ内に
	　　入っている『プロジェクトに追加すべきファイル/HandlerWaltamForDxLib』と、
   	　 『プロジェクトに追加すべきファイル/プロジェクトに追加すべきファイル_VC用』フォルダのパスを入力してから、
	　　再度ダイアログ右下にある『適用(A)』ボタンを押します。

	⑦　次に左側のリストから『構成プロパティ』→『リンカー』→『全般』を選びます。
	
	⑧　次に右側に表示されている『追加のライブラリディレクトリ』の項目に⑥と全く同じＤＸライブラリの
	　　パッケージ内に入っている『プロジェクトに追加すべきファイル/HandlerWaltamForDxLib』と
           『プロジェクトに追加すべきファイル/プロジェクトに追加すべきファイル_VC用』フォルダのパスを
	　　入力してから、再度ダイアログ右下にある『適用(A)』ボタンを押します。

   	⑨ 　次に左側のリストから『リンカー』→『入力』を選びます。
      　　　パッケージ内に入っている『追加の依存ファイル』に『プロジェクトに追加すべきファイル/HandlerWaltamForDxLib』
	 　 フォルダのパスに『¥HandlerWaltanForDxLib.lib』を足したものを入力してください。

	⑩　次にダイアログの左上にある『構成(C):』と書かれている項目を『すべての構成』から
	　　『Release』に変更します。

	⑪　左側のリストから今度は『構成プロパティ』→『Ｃ／Ｃ＋＋』→『コード生成』を選びます。

	⑫　ダイアログ右側に表示されている『ランタイム ライブラリ』の項目を
	　　『マルチスレッド(/MT)』に変更したあと、ダイアログ右下にある『適用(A)』ボタンを押します。

	⑬　ダイアログの左上にある『構成(C):』と書かれている項目を『Release』から
	　　『Debug』に変更します。

	⑭　ダイアログ右側に表示されている『ランタイム ライブラリ』の項目を
	　　今度は『マルチスレッド デバッグ(/MTd)』に変更します。

	⑮　最後にダイアログの下の方にある『ＯＫ』を押してダイアログを閉じます。


</body>

    
<p align="right">(<a href="#top">トップへ</a>)</p>


## 使い方

<body>

 	// 当ライブラリで必須になるインクルードファイル
  	// "DxLib.h" もincludeされる
	#include "HandlerWaltanForDxLib.h"

	// プログラムは WinMain から始まります
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		// DXライブラリの初期化処理も兼ねている
		if (HandlerWaltan::Instance().Init() == -1)
		{
			return 0;
		}


  		SetUseZBuffer3D(TRUE);     // デプスバッファ（Zバッファ）を有効にする
		SetWriteZBuffer3D(TRUE);   // Zバッファへの書き込みを有効にする
	
		//! ハンドラーやライフサイクルに基づいたタイミングでメソッドを自動的に呼び出すオブジェクト
		//! シングルトンで設計されているため、以下の方法以外でインスタンスを取得することはできない
		HandlerWaltan& HW = HandlerWaltan::Instance();
	
		//! オブジェクトの生成(unityでいうところのGameObjectの生成)
		HWGameObject* obj = new HWGameObject();
	
		//! コンストラクタの引数で名前やプライオリティの初期設定も可能(指定しなかった場合は名前は"hwObj",
		//! プライオリティは 0 になる)
		// HWGameObject* obj = new HWGameObject("obj");
		// HWGameObject* obj = new HWGameObject(20);
		// HWGameObject* obj = new HWGameObject("obj", 20);
	
	
		// メインループ
		while (ProcessMessage() == 0)
		{
			//裏画面消す
			ClearDrawScreen();
			//描画先を裏画面に
			SetDrawScreen(DX_SCREEN_BACK);
	
			// ESCAPEキーの入力で終了
			if (CheckHitKey(KEY_INPUT_ESCAPE))
				break;
	
	
			// 全てのUpdateメソッドを全て呼び出す
			HW.Update();
	
		
			//裏画面を表画面にコピー
			ScreenFlip();
		}
		
		// ソフトの終了 
		HandlerWaltan::End();
	
		return 0;				
	}
 
</body>

<!-- プロジェクトの概要を記載 -->


<p align="right">(<a href="#top">トップへ</a>)</p>



<!-- ここから自作ライブラリのリファレンス -->

## HWGameObject

<b> <説明> </b>

アタッチされているコンポーネントの管理
オブジェクトの設定

<br />
<br />

<b> <コンポーネント付与、取得の関数> </b>

<body>

	@brief		コンポーネントを追加する
 	@detail		テンプレートにコンポーネントを指定
  	@param[in]	引数が存在するコンポーネントの場合は指定
	@return		アタッチされたコンポーネントのインスタンス
 	template<class T>
	T* AddComponent()

 	@brief		指定のコンポーネントを返す
	@return		アタッチされていた場合はインスタンスを返し、それ以外ならnullPtrを返す
	template<typename T>
	T* GetComponent()

</body>

<b> <オブジェクトの設定> </b>

<body>

	@brief		オブジェクトの名前
	std::string name

	@brief		ハンドラーやUpdateメソッドの優先順位(降順)
	int priority
	
	@brief		Transformコンポーネント
	HWTransform* transform

</body>

<b> <コンストラクタ> </b>

<body>

	@brief		コンストラクタ
	HWGameObject()
	@brief		コンストラクタ(名前の初期化宣言)
	@param[in]	std::string オブジェクト名	
	HWGameObject(const std::string&)

	@brief		コンストラクタ(プライオリティの初期化宣言)
	@param[in]	int プライオリティ
	HWGameObject(const int)

	@brief		コンストラクタ(名前とプライオリティの初期化宣言)
	@param[in]	std::string オブジェクト名
	@param[in]	int	プライオリティ
	HWGameObject(const std::string&, const int)

	@brief		コピーコンストラクタ
	@param[in]	HWGameObject& コピー元のHWGameObject
	HWGameObject(const HWGameObject&)

</body>

<p align="right">(<a href="#top">トップへ</a>)</p>





<!------------------------------------------------------------------------------------------------------------------>





## HWComponent

<b> <説明> </b>

すべてのコンポーネントの基底クラス


<br />
<br />

<b> <オーバーライド関数> </b>

<body>

	@brief		HWGameObjectにアタッチされた瞬間に働く
 	@detail		コンポーネントの初期化処理はなるべくコンストラクタではなくこちらで行う
	virtual void Awake()

 	@brief		毎フレーム呼ばれるメソッド
	virtual void Update()


 <b> <非トリガーコリジョン接触時のコールバック関数> </b>


 	@brief		コライダー衝突時に働くメソッド
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnCollisionEnter(HWCollider&)

 	@brief		コライダー衝突中に働くメソッド
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnCollisionStay(HWCollider&)

	@brief		コライダー衝突が解除時に働くメソッド (コライダーがトリガーの場合)
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnCollisionExit(HWCollider&)


 <b> <トリガーコリジョン接触時のコールバック関数> </b>


  	@brief		コライダー衝突時に働くメソッド (コライダーがトリガーの場合)
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnTriggerEnter(HWCollider&)

 	@brief		コライダー衝突中に働くメソッド (コライダーがトリガーの場合)
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnTriggerStay(HWCollider&)

	@brief		コライダー衝突が解除時に働くメソッド (コライダーがトリガーの場合)
  	@param[out]	HWCollider& 衝突した相手のコライダー情報
	virtual void OnTriggerExit(HWCollider&)


  <b> <継承されるメンバ変数> </b>


	@brief		このコンポーネントがアタッチされているHWGameObject
	HWGameObject* gameObject

	@brief		HWGameObjectにアタッチされているHWTransform
	HWTransform* transform

	@brief		複数アタッチ可能なコンポーネントか
	bool isMultiplePossession

	@brief		コンポーネントのアクティブ
	bool active

	@brief		ハンドラーやUpdateメソッドの優先順位(降順)
	int priority

</body>

<p align="right">(<a href="#top">トップへ</a>)</p>





<!------------------------------------------------------------------------------------------------------------------>





## HWTransform

<b> <説明> </b>

座標、回転などを管理するコンポーネント

オブジェクトの正面ベクトルや、移動ベクトルの設定

<br />
<br />

  <b> <平行移動、回転、拡縮> </b>


	@brief		グローバル座標
	VECTOR position

	@brief		グローバル回転
	VECTOR rotate

	@brief		グローバル拡縮
	VECTOR scale


  <b> <メンバ変数> </b>


	@brief		移動ベクトル
	VECTOR velocity


   <b> <メンバ関数> </b>


	@brief		オブジェクトの正面ベクトルを取得
	const VECTOR& Forward()


</body>
<p align="right">(<a href="#top">トップへ</a>)</p>





<!------------------------------------------------------------------------------------------------------------------>





## HWCapsuleCollider

<b> <説明> </b>

カプセル型の当たり判定コンポーネント

自身で始点と終点を定めない場合は、自動でHWGameObjectの座標を原点に height 分の高さを持つコライダーを構築する

<br />
<br />

  <b> <コライダーの設定> </b>


	@brief		コライダーの高さ (自身で始点と終点を設定した場合、無効化される)
	float height

	@brief		コライダーの半径
	float radius

	@brief		コライダーの始点
	VECTOR UsStartPos

	@brief		コライダーの終点
	VECTOR UsEndPos


</body>
<p align="right">(<a href="#top">トップへ</a>)</p>





<!------------------------------------------------------------------------------------------------------------------>




## HWAnimator

<b> <説明> </b>

モデルのアニメーション制御用コンポーネント

先にHWRendererをアタッチするようにしてください

<br />
<br />

  <b> <> </b>





</body>

<p align="right">(<a href="#top">トップへ</a>)</p>



<!------------------------------------------------------------------------------------------------------------------>




## InputSystem

<b> <説明> </b>

キー入力を検知し、入力時に設定したコールバック関数を呼び出すクラス


<br />
<br />

<b> <メソッド> </b>

<body>
	
	/**
	 * @brief			マップにキーを登録する
	 * @detail			{} で複数入力可能
	 * @param[in]	std::string	登録するキー
	 * @param[in]	int		キーコード
	 * @author			Suzuki N
	 * @date			24/09/07
	 */
	void AddKeyCode(const std::string _key, int _inputKey)

 	/**
	 * @brief			InputActionにコールバック関数を登録する
	 * @param[in]			std::function<void(InputAction::CallBackContext&)> 登録するコールバック関数
	 * @author			Suzuki N
	 * @date			24/09/08
	 */
	void AddCallBack(const std::string _key, std::function<void(InputAction::CallBackContext&)> _callBack)
 
</body>

<b> <テストプロジェクト> </b>

<body>

	#include "HandlerWaltanForDxLib.h"

 	// プログラムは WinMain から始まります
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		// DXライブラリの初期化処理も兼ねている
		if (HandlerWaltan::Instance().Init() == -1)
		{
			return 0;
		}

		// Windowモードで起動
		SetGraphMode(840, 480, 16);
		ChangeWindowMode(true);

		//! ハンドラーやライフサイクルに基づいたタイミングでメソッドを自動的に呼び出すオブジェクト
		//! シングルトンで設計されているため、以下の方法以外でインスタンスを取得することはできない
		HandlerWaltan& HW = HandlerWaltan::Instance();


		//! InputSystem
		InputSystem* input = new InputSystem();

  		// アクション名と登録するキーを指定
		input->AddKeyCode("map1", KEY_INPUT_RETURN);
		// アクション時に呼ばれるコールバック関数を登録
		input->AddCallBack("map1", [](InputAction::CallBackContext& _context)
		{
   		}

		// ソフトの終了 
		HandlerWaltan::End();
	}

</body>

<p align="right">(<a href="#top">トップへ</a>)</p>




