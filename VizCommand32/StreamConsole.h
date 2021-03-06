// 二重インクルード防止
#ifndef __STREAM_CONSOLE_H__
#define __STREAM_CONSOLE_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "UserControl.h"	// CUserControl
#include "WindowListControl.h"	// CWindowListControl
#include "Console.h"	// CConsole
#include "StaticPanel.h"	// CStaticPanel
#include "FileListControlPanel.h"	// CFileListControlPanel
#include "PicturePanel.h"	// CPicturePanel

// ストリームコンソールクラスCStreamConsole
class CStreamConsole : public CWindowListControl{

	// publicメンバ
	public:

		// publicメンバ変数
		HMENU m_nId;	// HMENU型メニューID.
		int m_iNext;	// int型m_iNext.

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
		virtual void OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	// ユーザ定義メッセージが発生した時.
		virtual void OnRequestScrollBottom(WPARAM wParam, LPARAM lParam);	// 下へのスクロールが要求された時.
		virtual int OnStreamCommand(WPARAM wParam, LPARAM lParam);	// コンソールからストリームコンソールへのメッセージが送られた時.
		virtual void OnHello(HWND hSrc, CCommand *pCommand);	// "Hello, world!"の出力を要求された時.
		virtual void OnList(HWND hSrc, CCommand *pCommand);	// ファイルリストの出力を要求された時.
		virtual void OnView(HWND hSrc, CCommand *pCommand);	// ファイルの表示を要求された時.

};

#endif