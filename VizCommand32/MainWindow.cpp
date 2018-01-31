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

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CWindow::RegisterClassで登録.(背景はLTGRAY_BRUSH.)

}

// ウィンドウクラス登録関数RegisterClass.(メニュー名指定, 背景ブラシ指定バージョン.)
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// 背景はhbrBackground.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), NULL, hbrBackground);	// CWindow::RegisterClassで登録.

}


// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CMainWindow::Destroy(){

	// ウィンドウリストコントロールの削除.
	if (m_pWindowListControl != NULL){	// m_pWindowListControlがNULLでなければ.
		m_pWindowListControl->Destroy();	// m_pWindowListControl->Destroyでm_pWindowListControlの終了処理を実行.
		delete m_pWindowListControl;	// deleteでm_pWindowListControlを解放.
		m_pWindowListControl = NULL;	// m_pWindowListControlにNULLをセット.
	}

	// 親ウィンドウのDestroyを呼ぶ.
	CWindow::Destroy();	// CWindow::Destroyを呼ぶ.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// ウィンドウリストコントロールオブジェクトの作成.
	m_pWindowListControl = new CWindowListControl();	// CWindowListControlオブジェクトの作成.

	// ウィンドウリストコントロールのウィンドウ作成.
	m_pWindowListControl->Create(_T(""), 0, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pWindowListControl->Createで作成.

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy(){

	// メンバの終了処理
	//Destroy();	// Destroyでこのウィンドウの終了処理をする.

	// 親ウィンドウのOnDestroyを呼ぶ.
	CWindow::OnDestroy();	// CWindow::OnDestroyを呼ぶ.

	// 終了メッセージの送信.
	PostQuitMessage(0);	// PostQuitMessageで終了コードを0としてWM_QUITメッセージを送信.

}

// ウィンドウの描画を要求された時のハンドラOnPaint.
void CMainWindow::OnPaint(){

	// 変数の初期化.
	HDC hDC = NULL;	// hDCをNULLで初期化.
	PAINTSTRUCT ps = {0};	// psを{0}で初期化.
	HPEN hPen = NULL;	// hPenをNULLで初期化.
	HBRUSH hBrush = NULL;	// hBrushをNULLで初期化.

	// 描画開始.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaintで描画開始.

	// ペンとブラシの生成.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0xff, 0));	// CreatePenで緑(淡)のペンを作成.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0x7f, 0));		// CreateSolidBrushで緑(濃)のブラシを作成.

	// ペンとブラシの選択.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// 緑のペンを選択.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// 緑のブラシを選択.

	// 矩形描画.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangleで矩形を描画.
	
	// ペンとブラシの復元
	SelectObject(hDC, hOldBrush);		// 古いブラシを選択.
	SelectObject(hDC, hOldPen);		// 古いペンを選択.

	// ペンとブラシの破棄.
	DeleteObject(hBrush);	// ブラシの破棄.
	DeleteObject(hPen);	// ペンの破棄.

	// 描画終了.
	EndPaint(m_hWnd, &ps);	// EndPaintで描画終了.

}

// ウィンドウを閉じた時.
int CMainWindow::OnClose(){

	// ウィンドウの終了処理.
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

	// 0を返す.
	return 0;	// 0を返してウィンドウを閉じる.

}