// 二重インクルード防止
#ifndef __WINDOW_H__
#define __WINDOW_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI
#include <string>	// std::string
#include <map>	// std::map
// 独自のヘッダ
#include "HandlerConditions.h"	// 構造体HandlerConditions

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// 独自ウィンドウメッセージ
#define UM_SIZECHILD				(WM_APP + 1000)	// 32768 + 1000( = 33768)
#define UM_CONSOLECORECOMMAND		(WM_APP + 1001)	// 32768 + 1001( = 33769)
#define UM_RESPONSEMESSAGE			(WM_APP + 1002)	// 32768 + 1002( = 33770)
#define UM_FINISHRESPONSE			(WM_APP + 1003)	// 32768 + 1003( = 33771)
#define UM_REQUESTSCROLLBOTTOM		(WM_APP + 1004)	// 32768 + 1004( = 33772)
#define UM_STREAMCOMMAND			(WM_APP + 1005)	// 32768 + 1005( = 33773)

// ウィンドウクラスCWindow
class CWindow{

	// publicメンバ
	public:

		// publicメンバ変数
		HWND m_hWnd;	// HWND型ウィンドウハンドルm_hWnd.
		int m_x;	// ウィンドウの位置X座標m_x.
		int m_y;	// ウィンドウの位置Y座標m_y.
		int m_iWidth;	// ウィンドウの幅m_iWidth.
		int m_iHeight;	// ウィンドウの高さm_iHeight.
		int m_iClientAreaWidth;		// クライアント領域幅
		int m_iClientAreaHeight;	// クライアント領域高さ
		// staticメンバ変数
		static std::map<HWND, CWindow *>m_mapWindowMap;	// ウィンドウハンドルをキー, CWindowオブジェクトポインタを値とするマップm_mapWindowMap.
		static std::map<DWORD, HandlerConditions *>m_mapHandlerMap;	// DWORD値をキー, HandlerConditions構造体ポインタを値とするマップm_mapHandlerMap.

		// publicメンバ関数
		// コンストラクタ
		CWindow();	// コンストラクタCWindow()
		~CWindow();	// デストラクタ~CWindow()

		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.(ウィンドウクラス名省略バージョン.)
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName, WNDPROC lpfnWndProc);	// ウィンドウクラス登録関数RegisterClass.(ウィンドウプロシージャ指定バージョン.)
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName, LPCTSTR lpszMenuName);	// ウィンドウクラス登録関数RegisterClass.(ウィンドウプロシージャ省略, メニュー名指定バージョン.)
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName, LPCTSTR lpszMenuName, HBRUSH hbrBackground);	// ウィンドウクラス登録関数RegisterClass.(ウィンドウプロシージャ省略, メニュー名指定バージョン, 背景ブラシ指定バージョン.)
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName, WNDPROC lpfnWndProc, LPCTSTR lpszMenuName, HBRUSH hbrBackground);	// ウィンドウクラス登録関数RegisterClass.(メニュー名指定バージョン.)
		static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// スタティックウィンドウプロシージャStaticWindowProc.
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		virtual BOOL Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		virtual void Destroy();	// ウィンドウの破棄と終了処理関数Destroy.
		virtual BOOL ShowWindow(int nCmdShow);	// ウィンドウ表示関数ShowWindow.
		virtual void SetText(LPCTSTR lpctszText);	// テキストセット関数SetText.
		virtual int GetTextLength();	// テキストの長さ取得関数GetTextLength.
		virtual tstring GetText();	// テキスト取得関数GetText.
		virtual void AddCommandHandler(UINT nID, UINT nCode, int(CWindow:: * handler)(WPARAM wParam, LPARAM lParam));	// コマンドハンドラの追加.
		virtual void DeleteCommandHandler(UINT nID, UINT nCode);	// コマンドハンドラの削除.
		virtual LRESULT DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ダイナミックウィンドウプロシージャDynamicWindowProc.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnMove(int x, int y);	// ウィンドウが移動した時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual void OnPaint();	// ウィンドウの描画を要求された時のハンドラOnPaint.
		virtual int OnClose();	// ウィンドウを閉じた時.
		virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);	// コマンドが発生した時.
		virtual void OnTimer(UINT_PTR nIDEvent);	// タイマーイベントが発生した時.
		virtual void OnHScroll(UINT nSBCode, UINT nPos);	// 水平方向スクロールバーイベント時.
		virtual void OnVScroll(UINT nSBCode, UINT nPos);	// 垂直方向スクロールバーイベント時.
		virtual HBRUSH OnCtlColorEdit(HDC hDC, HWND hEdit);	// 子エディットコントロールの描画時.
		virtual void OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	// ユーザ定義メッセージが発生した時.
		virtual void OnSizeChild(WPARAM wParam, LPARAM lParam);	// 子から親へウィンドウサイズ変更の要求が発生した時.

};

#endif