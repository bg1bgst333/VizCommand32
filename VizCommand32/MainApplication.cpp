// ヘッダのインクルード
// 独自のヘッダ
#include "MainApplication.h"	// CMainApplication
#include "MainWindow.h"	// CMainWindow

// インスタンス初期化関数InitInstance.
BOOL CMainApplication::InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd){

	// ウィンドウクラスの登録.
	CMainWindow::RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CMainWindow::RegisterClassでウィンドウクラス"CMainWindow"を登録.
	CWindowListControl::RegisterClass(hInstance, (HBRUSH)GetStockObject(GRAY_BRUSH));	// CWindowListControl::RegisterClassでウィンドウクラス"CWindowListControl"を登録.
	CWindowListItemsPanel::RegisterClass(hInstance, (HBRUSH)GetStockObject(BLACK_BRUSH));	// CWindowListItemsPanel::RegisterClassでウィンドウクラス"CWindowListItemsPanel"を登録.
	CWindowListItem::RegisterClass(hInstance, (HBRUSH)GetStockObject(GRAY_BRUSH));	// CWindowListItem::RegisterClassでウィンドウクラス"CWindowListItem"を登録.
	CEditPanel::RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CEditPanel::RegisterClassでウィンドウクラス"CEditPanel"を登録.

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