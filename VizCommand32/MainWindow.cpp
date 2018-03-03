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

		// ウィンドウリストアイテムの削除.
		m_pWindowListControl->RemoveAll();	// m_pWindowListControl->RemoveAllでアイテムを全て削除.

		// ウィンドウリストコントロールの破棄.
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
	m_pWindowListControl->Create(_T(""), 0, 0, 0, 480, 0, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pWindowListControl->Createで作成.

#if 0
	// ウィンドウリストアイテムの追加.
	m_pWindowListControl->Add(_T("Item0"), 320, 32, 64, 64, lpCreateStruct->hInstance);	// m_pWindowListControl->Addで"Item0"を追加.
	m_pWindowListControl->Add(_T("Item1"), 32, 320, 64, 64, lpCreateStruct->hInstance);	// m_pWindowListControl->Addで"Item1"を追加.

	// ウィンドウリストアイテムの取得.
	CWindowListItem *pItem0 = m_pWindowListControl->Get(0);	// 0番目を取得.
	CWindowListItem *pItem1 = m_pWindowListControl->Get(1);	// 1番目を取得.
#endif

	// ウィンドウリストアイテムの追加.
	//m_pWindowListControl->Add(_T("Item0"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Addで"Item0"を追加.
	//m_pWindowListControl->Add(_T("Item1"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Addで"Item1"を追加.
	//m_pWindowListControl->Add(_T("Item2"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Addで"Item2"を追加.
	//m_pWindowListControl->Insert(0, _T("Item-1"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insertで0番目に"Item-1"を挿入.
	//m_pWindowListControl->Insert(1, _T("Item-0.5"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insertで1番目に"Item-0.5"を挿入.
	//m_pWindowListControl->Insert(5, _T("Item3"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insertで2番目に"Item3"を挿入.
	//m_pWindowListControl->Insert(0, _T("Item0"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insertで"Item0"を追加.
	//m_pWindowListControl->Insert(-5, _T("Item-5"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insertで"Item-5"を追加.
	//m_pWindowListControl->Insert(5, _T("Item5"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insertで"Item5"を追加.
	//m_pWindowListControl->Insert(1, _T("Item-1"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insertで"Item-1"を追加.
	//m_pWindowListControl->Insert(3, _T("Item3"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insertで"Item3"を追加.

	// ウィンドウリストアイテムの削除.
	//m_pWindowListControl->Delete(3);	// m_pWindowListControl->Deleteで3番目削除.
	//m_pWindowListControl->Delete(1);	// m_pWindowListControl->Deleteで1番目削除.
	//m_pWindowListControl->Delete(10);	// m_pWindowListControl->Deleteで10番目削除.
	//m_pWindowListControl->Delete(3);	// m_pWindowListControl->Deleteで3番目削除.
	//m_pWindowListControl->Delete(-4);	// m_pWindowListControl->Deleteで-4番目削除.

	// 順次更新タイマーをセット.
	SetTimer(hwnd, 2, 1000, NULL);	// SetTimerで更新タイマーをセット.(1000ミリ秒==1秒)

#if 0
	// エディットコントロールの生成.
	// エディット0.
	CEdit *pEdit0 = new CEdit();	// CEditオブジェクトを生成.
	pEdit0->Create(_T("Edit0"), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 480, 100, pItem0->m_hWnd, (HMENU)WM_APP + 200, lpCreateStruct->hInstance);	// m_pEdit0->CreateでpItem0->m_hWndを親としてウィンドウ作成.
	pItem0->m_mapChildMap.insert(std::make_pair(_T("Edit0"), pEdit0));	// "Edit0"をキー, pEdit0を値として, pItem0->m_mapChildMapに登録.

	// エディット1.
	CEdit *pEdit1 = new CEdit();	//CEditオブジェクトを生成.
	pEdit1->Create(_T("Edit1"), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 100, 480, pItem1->m_hWnd, (HMENU)WM_APP + 201, lpCreateStruct->hInstance);	// m_pEdit1->CreateでpItem1->m_hWndを親としてウィンドウ作成.
	pItem1->m_mapChildMap.insert(std::make_pair(_T("Edit1"), pEdit1));	// "Edit1"をキー, pEdit1を値として, pItem1->m_mapChildMapに登録.
#endif

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

// ウィンドウのサイズが変更された時.
void CMainWindow::OnSize(UINT nType, int cx, int cy){

	// 親ウィンドウのOnSize.
	CWindow::OnSize(nType, cx, cy);	// CWindowのOnSize.

	// ウィンドウリストコントロールのサイズはウィンドウにぴったり合わせる.
	if (m_pWindowListControl != NULL){	// NULLでなければ.
		MoveWindow(m_pWindowListControl->m_hWnd, m_pWindowListControl->m_x, m_pWindowListControl->m_y, cx, cy, TRUE);	// MoveWindowでm_pWindowListControl->m_hWndのサイズを変更.
	}

	// 画面更新.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで更新.

}

// タイマーイベントが発生した時.
void CMainWindow::OnTimer(UINT_PTR nIDEvent){

	// スタティック変数の宣言.
	static int iCount;	// static intの変数iCount.

	// 初回更新タイマーの時.
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);
	if (nIDEvent == 2){	// 2の時.
		if (iCount == 0){
			m_pWindowListControl->Insert(0, _T("Item0"), 80, hInstance);
		}
		else if (iCount == 1){
			m_pWindowListControl->Insert(1, _T("Item1"), 80, hInstance);
		}
		else if (iCount == 2){
			m_pWindowListControl->Insert(2, _T("Item2"), 80, hInstance);
		}
		else if (iCount == 3){
			m_pWindowListControl->Insert(3, _T("Item3"), 80, hInstance);
		}
		else if (iCount == 4){
			m_pWindowListControl->Insert(4, _T("Item4"), 80, hInstance);
		}
		else if (iCount == 5){
			//m_pWindowListControl->Delete(2);
			CWindowListItem *pItem = m_pWindowListControl->Get(1);
			MoveWindow(pItem->m_hWnd, pItem->m_x, pItem->m_y, pItem->m_iWidth, pItem->m_iHeight * 2.5, TRUE);
			CWindowListItem *pItem2 = m_pWindowListControl->Get(3);
			MoveWindow(pItem2->m_hWnd, pItem2->m_x, pItem2->m_y, pItem2->m_iWidth, pItem2->m_iHeight * 2.5, TRUE);
			//InvalidateRect(this->m_pWindowListControl->m_hWnd, NULL, TRUE);
		}
		/*
		else if (iCount == 6){
			//m_pWindowListControl->Delete(20);
		}
		else if (iCount == 7){
			//m_pWindowListControl->Delete(-10);
		}
		else if (iCount == 8){
			//m_pWindowListControl->Delete(0);
		}
		else if (iCount == 9){
			//m_pWindowListControl->Delete(0);
		}
		?*/
		else{

			// タイマーを終了.
			KillTimer(m_hWnd, 2);	// 順次更新タイマーを終了.

		}
		iCount++;	// iCountをインクリメント.
	}

	// 無効領域を作成して画面の更新.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで無効領域作成.

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