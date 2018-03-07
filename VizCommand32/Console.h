// 二重インクルード防止
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "ScalableEditPanel.h"	// CScalableEditPanel
#include "ConsoleCore.h"	// CConsoleCore

// コンソールクラスCConsole
class CConsole : public CScalableEditPanel{

	// publicメンバ
	public:

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CConsole();	// コンストラクタCCConsole
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		void ShowInputForm();	// 入力フォームの出力.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.

};

#endif