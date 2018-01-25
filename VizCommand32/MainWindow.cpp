// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "resource.h"		// リソース

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() : CWindow(){

	// メンバの初期化.
	m_pWindowListControl = NULL;	// m_pWindowListControlをNULLで初期化.

}

// デストラクタ~CMainWindow()
CMainWindow::~CMainWindow(){

	// メンバの終了処理.
	if (m_pWindowListControl != NULL){	// m_pWindowListControlがNULLでなければ.
		DestroyWindow(m_pWindowListControl->m_hWnd);	// DestroyWindowでm_pWindowListControl->m_hWndを破棄.
		delete m_pWindowListControl;	// deleteでm_pWindowListControlを解放.
		m_pWindowListControl = NULL;	// m_pWindowListControlにNULLをセット.
	}

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューはなし(NULL)とする.((LPCTSTR)でキャストしないとオーバーロードが曖昧になる.)
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), (LPCTSTR)NULL);	// CWindow::RegisterClassで登録.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// ウィンドウリストコントロールオブジェクトの作成.
	m_pWindowListControl = new CWindowListControl();	// CWindowListControlオブジェクトの作成.

	// ウィンドウリストコントロールのウィンドウ作成.
	m_pWindowListControl->Create(_T(""), WS_BORDER, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pWindowListControl->Createで作成.

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy(){

	// 子ウィンドウオブジェクトの破棄.
	if (m_pWindowListControl != NULL){	// m_pWindowListControlがNULLでなければ.
		DestroyWindow(m_pWindowListControl->m_hWnd);	// DestroyWindowでm_pWindowListControl->m_hWndを破棄.
		delete m_pWindowListControl;	// deleteでm_pWindowListControlを解放.
		m_pWindowListControl = NULL;	// m_pWindowListControlにNULLをセット.
	}

	// 親ウィンドウのOnDestroyを呼ぶ.
	CWindow::OnDestroy();	// CWindow::OnDestroyを呼ぶ.

}