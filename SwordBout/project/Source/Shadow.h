#pragma once
//Shadow.h
class Shadow {
public:
	Shadow();
	~Shadow();
	void Make(); // シャドウマップを作る
	void Use(); // シャドウマップを使う
	void End(); // 描画終了
private:
	int map; // シャドウマップのハンドラ
};