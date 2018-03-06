// 二重インクルード防止
#ifndef __STREAM_CONSOLE_H__
#define __STREAM_CONSOLE_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "UserControl.h"	// CUserControl
#include "WindowListControl.h"	// CWindowListControl

// ストリームコンソールクラスCStreamConsole
class CStreamConsole : public CWindowListControl{

	// publicメンバ
	public:

		// publicメンバ変数
		HMENU m_nId;	// HMENU型メニューID.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CStreamConsole();	// コンストラクタCStreamConsole
		virtual ~CStreamConsole();	// デストラクタ~CStreamConsole
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウ作成時のハンドラOnCreate.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual void OnTimer(UINT_PTR nIDEvent);	// タイマーイベントが発生した時.

};

#endif