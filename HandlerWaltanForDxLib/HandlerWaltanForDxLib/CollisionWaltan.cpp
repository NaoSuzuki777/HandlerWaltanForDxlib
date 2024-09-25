#include "h/CollisionWaltan.h"


/**
* @author   Suzuki N
* @date     24/08/09
* @note		ColliderWaltanの実装ファイル
*/


#pragma region publucメソッド



#pragma endregion

#pragma region privateメソッド


CollisionWaltan::CollisionWaltan()
{

}


CollisionWaltan::~CollisionWaltan()
{

}

void CollisionWaltan::Update()
{
	//! 登録されているColliderの数が一個以下ならそのまま終了
	if (ColVec.size() < 2)return;

	// 当たり判定をチェックする
	for (auto it1 = ColVec.begin(); it1 != ColVec.end() - 1; ++it1)
	{
		// すでにチェックした組み合わせを省く
		for (auto it2 = it1 + 1; it2 != ColVec.end(); ++it2)
		{
			// triggerと非triggerの場合はその組み合わせは無視
			if ((*it1)->isTrigger != (*it2)->isTrigger)
				continue;

			// 衝突中のコライダーのリストに登録されているか調べる
			auto collisionIt = std::find((*it1)->CollidersInCollision.begin(),
				(*it1)->CollidersInCollision.end(), *it2);

			// it1 のコライダータイプによって処理を変える
			switch ((*it1)->GetColliderType())
			{
				// 立方体型コライダーの場合
			case ColliderType::Box:
				if (CollCheck_Box(dynamic_cast<HWBoxCollider*>(*it1), *it2))
				{
					// 衝突を検知した
					// コライダーがtriggerかどうかで呼ぶメソッドを変える
					if ((*it1)->isTrigger)
					{
						if (collisionIt == (*it1)->CollidersInCollision.end())
						{

							// 衝突時のコールバック関数の呼び出し
							(*it1)->gameObject->CallAllOnTriggerEnters(*it2);
							(*it2)->gameObject->CallAllOnTriggerEnters(*it1);
						}
						else
						{
							// すでに登録されている場合は衝突中のコールバック関数を呼び出す
							(*it1)->gameObject->CallAllOnTriggerStays(*it2);
							(*it2)->gameObject->CallAllOnTriggerStays(*it1);
						}
					}
					else
					{
						// 非triggerの場合
						if (collisionIt == (*it1)->CollidersInCollision.end())
						{

							// 衝突時のコールバック関数の呼び出し
							(*it1)->gameObject->CallAllOnCollisionEnters(*it2);
							(*it2)->gameObject->CallAllOnCollisionEnters(*it1);
						}
						else
						{
							// すでに登録されている場合は衝突中のコールバック関数を呼び出す
							(*it1)->gameObject->CallAllOnCollisionStays(*it2);
							(*it2)->gameObject->CallAllOnCollisionStays(*it1);
						}
					}
					// 衝突中のコライダーのリストにない場合は新たに登録
					if (collisionIt == (*it1)->CollidersInCollision.end())
					{
						(*it1)->CollidersInCollision.push_back(*it2);
						(*it2)->CollidersInCollision.push_back(*it1);
					}
				}
				else
				{
					// 衝突を検知しなかった
					// 登録しているコライダーの場合(前フレームまで衝突していた)
					if (collisionIt != (*it1)->CollidersInCollision.end())
					{
						// コライダーがtriggerかどうかで呼ぶメソッドを変える
						if ((*it1)->isTrigger)
						{
							// 衝突終了時のコールバック関数の呼び出し
							(*it1)->gameObject->CallAllOnTriggerExits(*it2);
							(*it2)->gameObject->CallAllOnTriggerExits(*it1);
						}
						else
						{
							// 非triggerの場合
							// 衝突終了時のコールバック関数の呼び出し
							(*it1)->gameObject->CallAllOnCollisionExits(*it2);
							(*it2)->gameObject->CallAllOnCollisionExits(*it1);
						}
						// 登録情報を削除する
						(*it1)->CollidersInCollision.erase(collisionIt);
						auto collisionIt2 = std::find((*it2)->CollidersInCollision.begin(),
							(*it2)->CollidersInCollision.end(), *it1);
						if(collisionIt2 != (*it2)->CollidersInCollision.end())
							(*it2)->CollidersInCollision.erase(collisionIt2);
					}
				}
				break;
				// カプセル型コライダーの場合
			case ColliderType::Capsule:
				if (CollCheck_Capsule(dynamic_cast<HWCapsuleCollider*>(*it1), *it2))
				{
						// 衝突を検知した
						// コライダーがtriggerかどうかで呼ぶメソッドを変える
						if ((*it1)->isTrigger)
						{
							if (collisionIt == (*it1)->CollidersInCollision.end())
							{

								// 衝突時のコールバック関数の呼び出し
								(*it1)->gameObject->CallAllOnTriggerEnters(*it2);
								(*it2)->gameObject->CallAllOnTriggerEnters(*it1);
							}
							else
							{
								// すでに登録されている場合は衝突中のコールバック関数を呼び出す
								(*it1)->gameObject->CallAllOnTriggerStays(*it2);
								(*it2)->gameObject->CallAllOnTriggerStays(*it1);
							}
						}
						else
						{
							// 非triggerの場合
							if (collisionIt == (*it1)->CollidersInCollision.end())
							{

								// 衝突時のコールバック関数の呼び出し
								(*it1)->gameObject->CallAllOnCollisionEnters(*it2);
								(*it2)->gameObject->CallAllOnCollisionEnters(*it1);
							}
							else
							{
								// すでに登録されている場合は衝突中のコールバック関数を呼び出す
								(*it1)->gameObject->CallAllOnCollisionStays(*it2);
								(*it2)->gameObject->CallAllOnCollisionStays(*it1);
							}
						}
						// 衝突中のコライダーのリストにない場合は新たに登録
						if (collisionIt == (*it1)->CollidersInCollision.end())
						{
							(*it1)->CollidersInCollision.push_back(*it2);
							(*it2)->CollidersInCollision.push_back(*it1);
						}
					}
				else
				{
					// 衝突を検知しなかった
					// 登録しているコライダーの場合(前フレームまで衝突していた)
					if (collisionIt != (*it1)->CollidersInCollision.end())
					{
						// コライダーがtriggerかどうかで呼ぶメソッドを変える
						if ((*it1)->isTrigger)
						{
							// 衝突終了時のコールバック関数の呼び出し
							(*it1)->gameObject->CallAllOnTriggerExits(*it2);
							(*it2)->gameObject->CallAllOnTriggerExits(*it1);
						}
						else
						{
							// 非triggerの場合
							// 衝突終了時のコールバック関数の呼び出し
							(*it1)->gameObject->CallAllOnCollisionExits(*it2);
							(*it2)->gameObject->CallAllOnCollisionExits(*it1);
						}
						// 登録情報を削除する
						(*it1)->CollidersInCollision.erase(collisionIt);
						auto collisionIt2 = std::find((*it2)->CollidersInCollision.begin(),
							(*it2)->CollidersInCollision.end(), *it1);
						if (collisionIt2 != (*it2)->CollidersInCollision.end())
							(*it2)->CollidersInCollision.erase(collisionIt2);
					}
				}
				break;
				// 球体型コライダーの場合
			case ColliderType::Sphere:
				CollCheck_Sphere(dynamic_cast<HWSphereCollider*>(*it1), *it2);
				break;
			}
		}
	}
}

void CollisionWaltan::UnRegister(HWCollider* _collider)
{
	// 要素を削除する
	auto it = std::find(ColVec.begin(), ColVec.end(), _collider);
	// 見つかった場合は削除
	if (it != ColVec.end())
		ColVec.erase(it);
}

bool CollisionWaltan::CollCheck_Box(HWBoxCollider* boxCol1, HWCollider* _col2)
{
	// _col2のコライダータイプによって処理を変える
	switch (_col2->GetColliderType())
	{
		// 立方体型コライダーの場合
	case ColliderType::Box:
	{
		//! BoxColliderにキャスト
		HWBoxCollider* boxCol2 = dynamic_cast<HWBoxCollider*>(_col2);

		//-----------------------------------------------------------
		// あたり判定を見る　*未実装
		//-----------------------------------------------------------

		OBB obb1;
		OBB obb2;

		obb1.c = boxCol1->worldPosition;
		// 回転行列の作成（X -> Y -> Z の順）
		MATRIX rotX1 = MGetRotX((float)Deg2Rad(boxCol1->transform->rotate.x));
		MATRIX rotY1 = MGetRotY((float)Deg2Rad(boxCol1->transform->rotate.y));
		MATRIX rotZ1 = MGetRotZ((float)Deg2Rad(boxCol1->transform->rotate.z));
		MATRIX mRotate1 = MMult(rotZ1, MMult(rotY1, rotX1));

		obb1.u[0] = VGet(mRotate1.m[0][0], mRotate1.m[1][0], mRotate1.m[2][0]); // X軸
		obb1.u[1] = VGet(mRotate1.m[0][1], mRotate1.m[1][1], mRotate1.m[2][1]); // Y軸
		obb1.u[2] = VGet(mRotate1.m[0][2], mRotate1.m[1][2], mRotate1.m[2][2]); // Z軸
		obb1.e = VGet(boxCol1->size.x / 2, boxCol1->size.y / 2, boxCol1->size.z / 2);

		obb2.c = boxCol2->worldPosition;
		// 回転行列の作成（X -> Y -> Z の順）
		MATRIX rotX2 = MGetRotX((float)Deg2Rad(boxCol2->transform->rotate.x));
		MATRIX rotY2 = MGetRotY((float)Deg2Rad(boxCol2->transform->rotate.y));
		MATRIX rotZ2 = MGetRotZ((float)Deg2Rad(boxCol2->transform->rotate.z));
		MATRIX mRotate2 = MMult(rotZ2, MMult(rotY2, rotX2));
		obb2.u[0] = VGet(mRotate2.m[0][0], mRotate2.m[1][0], mRotate2.m[2][0]); // X軸
		obb2.u[1] = VGet(mRotate2.m[0][1], mRotate2.m[1][1], mRotate2.m[2][1]); // Y軸
		obb2.u[2] = VGet(mRotate2.m[0][2], mRotate2.m[1][2], mRotate2.m[2][2]); // Z軸
		obb2.e = VGet(boxCol2->size.x / 2, boxCol2->size.y / 2, boxCol2->size.z / 2);

		if (!TestOBBOBB(&obb1, &obb2))
			return false;


		// コライダーがトリガーでないなら、コライダー同士がめり込まないようにする
		if (!boxCol1->isTrigger)
		{

		}

		return true;
		break;
	}
	// カプセル型コライダーの場合
	case ColliderType::Capsule:
	{
		HWCapsuleCollider* capsuleCol = dynamic_cast<HWCapsuleCollider*>(_col2);
		break;
	}
	// 球体型コライダーの場合
	case ColliderType::Sphere:
	{
		HWSphereCollider* sphereCol = dynamic_cast<HWSphereCollider*>(_col2);
		break;
	}
	}

	return false;
}

bool CollisionWaltan::CollCheck_Sphere(HWSphereCollider* _col1, HWCollider* _col2)
{
	// _col2のコライダータイプによって処理を変える
	switch (_col2->GetColliderType())
	{
		// 立方体型コライダーの場合
	case ColliderType::Box:
		break;
		// カプセル型コライダーの場合
	case ColliderType::Capsule:
		break;
		// 球体型コライダーの場合
	case ColliderType::Sphere:
		break;
	}

	return false;
}

bool CollisionWaltan::CollCheck_Capsule(HWCapsuleCollider* _col1, HWCollider* _col2)
{
	// _col2のコライダータイプによって処理を変える
	switch (_col2->GetColliderType())
	{
		// 立方体型コライダーの場合
	case ColliderType::Box:
		break;
		// カプセル型コライダーの場合
	case ColliderType::Capsule:
		break;
		// 球体型コライダーの場合
	case ColliderType::Sphere:
		break;
	}

	return false;
}

#pragma endregion

