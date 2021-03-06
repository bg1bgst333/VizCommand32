// ヘッダのインクルード
// 独自のヘッダ
#include "MainApplication.h"	// CMainApplication
#include "MainWindow.h"	// CMainWindow
// 既定のヘッダ
#include <commctrl.h>	// コモンコントロール

// インスタンス初期化関数InitInstance.
BOOL CMainApplication::InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd){

	// コモンコントロールの初期化.
	InitCommonControls();	// InitCommonControlsで初期化.

	// ウィンドウクラスの登録.
	CMainWindow::RegisterClass(hInstance, (HBRUSH)GetStockObject(BLACK_BRUSH));	// CMainWindow::RegisterClassでウィンドウクラス"CMainWindow"を登録.
	CStreamConsole::RegisterClass(hInstance, (HBRUSH)GetStockObject(BLACK_BRUSH));	// CStreamConsole::RegisterClassでウィンドウクラス"CStreamConsole"を登録.
	CWindowListItemsPanel::RegisterClass(hInstance, (HBRUSH)GetStockObject(BLACK_BRUSH));	// CWindowListItemsPanel::RegisterClassでウィンドウクラス"CWindowListItemsPanel"を登録.
	CWindowListItem::RegisterClass(hInstance, (HBRUSH)GetStockObject(BLACK_BRUSH));	// CWindowListItem::RegisterClassでウィンドウクラス"CWindowListItem"を登録.
	CConsole::RegisterClass(hInstance, (HBRUSH)GetStockObject(BLACK_BRUSH));	// CConsole::RegisterClassでウィンドウクラス"CConsole"を登録.
	CStaticPanel::RegisterClass(hInstance, (HBRUSH)GetStockObject(BLACK_BRUSH));	// CStaticPanel::RegisterClassでウィンドウクラス"CStaticPanel"を登録.
	CFileListControlPanel::RegisterClass(hInstance, (HBRUSH)GetStockObject(BLACK_BRUSH));	// CListControlPanel::RegisterClassでウィンドウクラス"CListControlPanel"を登録.
	CPicturePanel::RegisterClass(hInstance, (HBRUSH)GetStockObject(BLACK_BRUSH));	// CPicturePanel::RegisterClassでウィンドウクラス"CPicturePanel"を登録.

	// CMainWindowオブジェクトの作成.
	m_pMainWnd = new CMainWindow();	// CMainWindowオブジェクトを作成し, m_pMainWndに格納.

	// ウィンドウの作成.
	if (!m_pMainWnd->Create(_T("VizCommand"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance)){	// m_pMainWnd->Createでウィンドウ作成し, 失敗した場合.

		// エラー処理
		return FALSE;	// returnでFALSEを返して異常終了.

	}

	// ウィンドウの表示.
	m_pMainWnd->ShowWindow(SW_SHOW);	// m_pMainWnd->ShowWindowで表示.

	// TRUEを返す.
	return TRUE;	// returnでTRUEを返す.

}