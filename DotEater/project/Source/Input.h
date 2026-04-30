#pragma once
#include "../Library/GameObject.h"

class Input : public GameObject {
private:
	Input();
public:
	/// <summary>
	/// Inputクラスのインスタンスを作ります。
	/// すでに存在している時は、作りません。
	/// これでインスタンスを作るため、コンストラクターはprivateにしました。
	/// </summary>
	/// <returns>インスタンスのポインター</returns>
	static Input* Create();
	~Input();
	void Update() override;
	void Draw() override;

	//// キーボード
	
	/// <summary>
	/// キーを押しているか調べる
	/// </summary>
	/// <param name="key">調べるキーのコード（DxLibのKEY_INPUT_*を使う）</param>
	/// <returns>押されていればtrue</returns>
	static bool IsKeyPress(int key);

	/// <summary>
	/// キーを押したトリガーを調べる
	/// </summary>
	/// <param name="key">調べるキーのコード（DxLibのKEY_INPUT_*を使う）</param>
	/// <returns>押した瞬間にtrue</returns>
	static bool IsKeyOnTrig(int key);

	//// マウス

	/// <summary>
	/// マウスのボタンを押しているか調べる
	/// </summary>
	/// <param name="button">調べるマウスボタンのコード（DxLibのMOUSE_INPUT_*を使う）</param>
	/// <returns>押していればtrue</returns>
	static bool IsMousePress(int button);

	/// <summary>
	/// マウスのボタンを押したトリガーを調べる
	/// </summary>
	/// <param name="button">調べるマウスボタンのコード（DxLibのMOUSE_INPUT_*を使う）</param>
	/// <returns>押した瞬間にtrue</returns>
	static bool IsMouseOnTrig(int button);

	/// <summary>
	/// マウスのボタンを離したトリガーを調べる
	/// </summary>
	/// <param name="button">調べるマウスボタンのコード（DxLibのMOUSE_INPUT_*を使う）</param>
	/// <returns>離した瞬間にtrue</returns>
	static bool IsMouseOffTrig(int button);

	/// <summary>
	/// マウス座標を取得する
	/// </summary>
	/// <returns>マウス座標</returns>
	static const POINT& MousePosition();
};