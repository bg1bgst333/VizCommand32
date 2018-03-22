// 二重インクルード防止
#ifndef __CUSTOM_CONTROL_H__
#define __CUSTOM_CONTROL_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "Window.h"	// CWindow

// カスタムコントロールクラスCCustomControl
class CCustomControl : public CWindow{

	// publicメンバ
	public:

		// publicメンバ変数
		// staticメンバ変数
		static std::map<tstring, WNDPROC> m_mapBaseWindowProcMap;	// 既定のウィンドウクラス名をキー, 既定のウィンドウプロシージャを値とするマップm_mapBaseWindowProcMap.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CCustomControl();	// コンストラクタCCustomControl
		virtual ~CCustomControl();	// デストラクタ~CUserControl
		// staticメンバ関数
		static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// スタティックウィンドウプロシージャStaticWindowProc.
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		virtual LRESULT DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ダイナミックウィンドウプロシージャDynamicWindowProc.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnMove(int x, int y);	// ウィンドウが移動した時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual void OnPaint();	// ウィンドウの描画を要求された時のハンドラOnPaint.
		virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	// キーが押された時.
		virtual int OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		// 文字キーが押された時.
		virtual void OnHScroll(UINT nSBCode, UINT nPos);	// 水平方向スクロールバーイベント時.
		virtual void OnVScroll(UINT nSBCode, UINT nPos);	// 垂直方向スクロールバーイベント時.
		virtual void OnMouseMove(UINT nFlags, POINT pt);	// マウスが移動している時.
		virtual int OnLButtonDown(UINT nFlags, POINT pt);	// マウス左ボタンが押された時.
		virtual int OnLButtonUp(UINT nFlags, POINT pt);	// マウス左ボタンが離された時.
		virtual void OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	// ユーザ定義メッセージが発生した時.

};

#endif